#include <iostream>
#include <windows.h>
#include <tchar.h> // Pour _T()

#include <d3d12.h>
#include "d3dx12.h"
#include <dxgi1_4.h>
#include <wrl.h>

#include <d3dcompiler.h> // Compil shaders
#pragma comment(lib, "d3dcompiler.lib") // Compil shaders

#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")
//#pragma comment(lib,"d3dcompiler.lib") - PAS UTILE POUR LE MOMENT





	// ______________________________________________Compilation des shaders ___________________________________________________________________________________________________________________________________________
#include <d3dcompiler.h>  // Nécessaire pour compiler les shaders
#pragma comment(lib, "d3dcompiler.lib")

Microsoft::WRL::ComPtr<ID3DBlob> CompileShader(const std::wstring& filename, const std::string& entryPoint, const std::string& target)
{
	Microsoft::WRL::ComPtr<ID3DBlob> shaderBlob;
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;

	HRESULT hr = D3DCompileFromFile(
		filename.c_str(),
		nullptr, nullptr,
		entryPoint.c_str(),
		target.c_str(),
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
		0,
		&shaderBlob,
		&errorBlob
	);

	if (FAILED(hr))
	{
		if (errorBlob)
		{
			OutputDebugStringA((char*)errorBlob->GetBufferPointer()); // Afficher l'erreur dans la console
		}
		return nullptr;
	}

	return shaderBlob;
}








LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}


int main()
{
	// ______________________________________________Creation fenetre windows ___________________________________________________________________________________________________________________________________________
	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = GetModuleHandle(nullptr);
	wc.lpszClassName = _T("DirectX12Window");

	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(
		0,                          // Styles supplementaires
		_T("DirectX12Window"),      // Nom de la classe de fenetre
		_T("Ma Fenetre DirectX 12"),// Titre de la fenetre
		WS_OVERLAPPEDWINDOW,        // Style de fenetre
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, // Position et taille
		nullptr, nullptr, GetModuleHandle(nullptr), nullptr);

	if (!hwnd) return 0; // Verifier si la creation a echoue

	ShowWindow(hwnd, SW_SHOW); // Afficher la fenetre


	// ______________________________________________Activation DEBUG DirectX ___________________________________________________________________________________________________________________________________________
#ifdef _DEBUG
	{
		Microsoft::WRL::ComPtr<ID3D12Debug> debugController;
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
		{
			debugController->EnableDebugLayer();
		}
	}
#endif

	// ______________________________________________Creation device ____________________________________________________________________________________________________________________________________________________

	Microsoft::WRL::ComPtr<ID3D12Device> device;
	HRESULT hr = D3D12CreateDevice(
		nullptr,                    // nullptr indique qu'on utilise l'adaptateur par defaut (la carte graphique principale)
		D3D_FEATURE_LEVEL_11_0,     // Niveau de fonctionnalites minimum requis
		IID_PPV_ARGS(&device)
	);
	if (FAILED(hr))
	{
		// Gerer l'erreur ici, par exemple en affichant un message
		return -1;
	}

	// ______________________________________________Creation Command Queue ____________________________________________________________________________________________________________________________________________________

	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;  // Pour des commandes de rendu direct

	hr = device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&commandQueue));
	if (FAILED(hr))
	{
		// Gerer l'erreur ici
		return -1;
	}


	// ______________________________________________Creation factory ____________________________________________________________________________________________________________________________________________________

	// 1. Creer une factory DXGI
	Microsoft::WRL::ComPtr<IDXGIFactory4> factory;
	UINT dxgiFactoryFlags = 0;
#ifdef _DEBUG
	dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
#endif

	hr = CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&factory));
	if (FAILED(hr))
	{
		// Gerer l'erreur ici
		return -1;
	}

	// ______________________________________________Description et Creation swap chain avec Factory ____________________________________________________________________________________________________________________________________________________

	const UINT FrameCount = 2;  // Par exemple, 2 pour un double buffering

	// 2. Decrire la swap chain
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
	swapChainDesc.BufferCount = FrameCount; // On utilise le double buffering
	swapChainDesc.Width = 800;       // La largeur de la fenetre (a ajuster si necessaire)
	swapChainDesc.Height = 600;      // La hauteur de la fenetre
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // Format de couleur (8 bits par canal RGBA)
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; // Usage : affichage dans un render target
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; // Type d'effet de swap (recommande pour DX12)
	swapChainDesc.SampleDesc.Count = 1; // Pas d'antialiasing ici

	// 3. Creer la swap chain pour la fenetre
	Microsoft::WRL::ComPtr<IDXGISwapChain1> swapChain1;
	hr = factory->CreateSwapChainForHwnd(
		commandQueue.Get(), // La command queue creee precedemment
		hwnd,               // Le handle de la fenetre windows creee 
		&swapChainDesc,
		nullptr,            // Pas de parametres particuliers pour le mode plein ecran (mode fenetre)
		nullptr,            // Aucune restriction sur l'adaptateur a utiliser
		&swapChain1
	);
	if (FAILED(hr))
	{
		// Gerer l'erreur ici
		return -1;
	}

	// Optionnel : Convertir en interface IDXGISwapChain3 pour acceder a des fonctionnalites plus recentes
	Microsoft::WRL::ComPtr<IDXGISwapChain3> swapChain;
	swapChain1.As(&swapChain);


	// ______________________________________________Creation Descriptor Heap  (pour RTV) ____________________________________________________________________________________________________________________________________________________


	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap;

	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
	rtvHeapDesc.NumDescriptors = FrameCount;                           // Un descripteur par buffer (frame)
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;                   // Type pour les render target views
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;                 // Pas de flags particuliers

	hr = device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));
	if (FAILED(hr))
	{
		// Gérer l'erreur
		return -1;
	}

	// ______________________________________________Creation Render Target View (pour chaque buffer(=frame) de la swap chain) ____________________________________________________________________________________________________________________________________________________

	// Un tableau pour stocker les buffers de la swap chain
	Microsoft::WRL::ComPtr<ID3D12Resource> renderTargets[FrameCount];

	// Récupérer la taille d'un descripteur RTV pour pouvoir naviguer dans le heap
	UINT rtvDescriptorSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

	// Obtenir le handle de départ du descriptor heap
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(rtvHeap->GetCPUDescriptorHandleForHeapStart());

	for (UINT i = 0; i < FrameCount; i++)
	{
		// Récupérer le buffer i de la swap chain
		hr = swapChain->GetBuffer(i, IID_PPV_ARGS(&renderTargets[i]));
		if (FAILED(hr))
		{
			// Gérer l'erreur
			return -1;
		}

		// Créer le Render Target View pour ce buffer
		// Le deuxième paramètre est un pointeur vers une structure D3D12_RENDER_TARGET_VIEW_DESC,
		// ici passé à nullptr pour utiliser le format par défaut du buffer.
		device->CreateRenderTargetView(renderTargets[i].Get(), nullptr, rtvHandle);

		// Avancer le handle pour le prochain descripteur
		rtvHandle.Offset(1, rtvDescriptorSize);
	}

	// ______________________________________________Creation Command Allocator et de la Command List ____________________________________________________________________________________________________________________________________________________


	//									********************************* Command Allocator *********************************
	// Création du command allocator
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;
	hr = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator));
	if (FAILED(hr))
	{
		return -1;
	}

	// Création de la command list
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;
	hr = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator.Get(), nullptr, IID_PPV_ARGS(&commandList));
	if (FAILED(hr))
	{
		return -1;
	}
	// On ferme la command list pour le moment
	commandList->Close();

	//									********************************* Fence *********************************

	Microsoft::WRL::ComPtr<ID3D12Fence> fence;
	UINT64 fenceValue = 0;
	hr = device->CreateFence(fenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
	if (FAILED(hr))
	{
		return -1;
	}

	// Création d'un événement Windows pour la synchronisation
	HANDLE fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
	if (fenceEvent == nullptr)
	{
		return -1;
	}

	UINT frameIndex = swapChain->GetCurrentBackBufferIndex();
	FLOAT clearColor[] = { 1.0f, 0.2f, 0.4f, 1.0f };
	/*UINT*/ rtvDescriptorSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);


	// ______________________________________________Dessin ____________________________________________________________________________________________________________________________________________________

	struct Vertex
	{
		float x, y, z;
		float r, g, b; // Ajout des composantes de couleur
	};

	Vertex triangleVertices[] =
	{
		{  0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f }, // Rouge
		{  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f }, // Vert
		{ -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f }  // Bleu
	};

	// Création du Vertex Buffer
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexBuffer;
	D3D12_HEAP_PROPERTIES heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	D3D12_RESOURCE_DESC bufferDesc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(triangleVertices));

	hr = device->CreateCommittedResource(
		&heapProps, D3D12_HEAP_FLAG_NONE, &bufferDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&vertexBuffer));

	if (FAILED(hr))
	{
		return -1;
	}

	// Copier les données dans le buffer
	void* pVertexData;
	CD3DX12_RANGE readRange(0, 0); // Pas de lecture sur le CPU
	vertexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&pVertexData));
	memcpy(pVertexData, triangleVertices, sizeof(triangleVertices));
	vertexBuffer->Unmap(0, nullptr);

	// Définition du Vertex Buffer View
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView = {};
	vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
	vertexBufferView.SizeInBytes = sizeof(triangleVertices);
	vertexBufferView.StrideInBytes = sizeof(Vertex);


	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
	{
		D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
		rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

		Microsoft::WRL::ComPtr<ID3DBlob> signature;
		Microsoft::WRL::ComPtr<ID3DBlob> error;
		hr = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error);
		if (FAILED(hr)) return -1;

		hr = device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&rootSignature));
		if (FAILED(hr)) return -1;
	}




	/*Microsoft::WRL::ComPtr<ID3DBlob> vertexShaderBlob;
	Microsoft::WRL::ComPtr<ID3DBlob> pixelShaderBlob;
	{
		const char* vertexShaderCode =
			"struct VSInput { float3 pos : POSITION; float3 col : COLOR; };"
			"struct PSInput { float4 pos : SV_POSITION; float3 col : COLOR; };"
			"PSInput main(VSInput input) {"
			"   PSInput output;"
			"   output.pos = float4(input.pos, 1.0);"
			"   output.col = input.col;"
			"   return output;"
			"}";
		const char* pixelShaderCode =
			"float4 main(float3 col : COLOR) : SV_TARGET {"
			"   return float4(col, 1.0);"
			"}";
		hr = D3DCompile(vertexShaderCode, strlen(vertexShaderCode), nullptr, nullptr, nullptr, "main", "vs_5_0", 0, 0, &vertexShaderBlob, nullptr);
		if (FAILED(hr)) return -1;
		hr = D3DCompile(pixelShaderCode, strlen(pixelShaderCode), nullptr, nullptr, nullptr, "main", "ps_5_0", 0, 0, &pixelShaderBlob, nullptr);
		if (FAILED(hr)) return -1;
	}*/

	auto vertexShader = CompileShader(L"TriangleVS.hlsl", "main", "vs_5_0");
	auto pixelShader = CompileShader(L"TrianglePS.hlsl", "main", "ps_5_0");

	if (!vertexShader || !pixelShader) return -1;	D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	};

	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
	{
		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
		psoDesc.pRootSignature = rootSignature.Get(); // Assurez-vous que rootSignature est bien défini
		psoDesc.VS = { vertexShader->GetBufferPointer(), vertexShader->GetBufferSize() };
		psoDesc.PS = { pixelShader->GetBufferPointer(), pixelShader->GetBufferSize() };
		psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
		psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
		psoDesc.DepthStencilState.DepthEnable = FALSE;  // Pas de profondeur pour un simple triangle
		psoDesc.DepthStencilState.StencilEnable = FALSE;
		psoDesc.SampleMask = UINT_MAX;
		psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		psoDesc.NumRenderTargets = 1;
		psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
		psoDesc.SampleDesc.Count = 1;

		hr = device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&pipelineState));
		if (FAILED(hr))
		{
			return -1;
		}
	}



	D3D12_VIEWPORT viewport = {};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = 800;
	viewport.Height = 600;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	D3D12_RECT scissorRect = { 0, 0, 800, 600 };


	// ______________________________________________Boucle d'affichage ____________________________________________________________________________________________________________________________________________________


	MSG msg = {};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// Réinitialiser le command allocator
			commandAllocator->Reset();

			// Réinitialiser la command list pour enregistrer de nouvelles commandes
			commandList->Reset(commandAllocator.Get(), nullptr);

			// Transition du back buffer de PRESENT à RENDER_TARGET
			D3D12_RESOURCE_BARRIER barrier = {};
			barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
			barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
			barrier.Transition.pResource = renderTargets[frameIndex].Get();
			barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
			barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
			barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
			commandList->ResourceBarrier(1, &barrier);

			// Obtenir le handle du RTV pour le buffer courant
			D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtvHeap->GetCPUDescriptorHandleForHeapStart();
			rtvHandle.ptr += frameIndex * rtvDescriptorSize;

			// Effacer le render target avec la couleur définie
			commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

			// Définir le pipeline
			commandList->SetPipelineState(pipelineState.Get());
			commandList->SetGraphicsRootSignature(rootSignature.Get());

			// Définir la primitive topology
			commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			// Définir le vertex buffer
			commandList->IASetVertexBuffers(0, 1, &vertexBufferView);

			// Dessiner 3 sommets (1 triangle)
			commandList->DrawInstanced(3, 1, 0, 0);


			// Transition du back buffer de RENDER_TARGET à PRESENT
			barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
			barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
			commandList->ResourceBarrier(1, &barrier);

			// Fermer la command list
			commandList->Close();

			// Exécuter la command list
			ID3D12CommandList* ppCommandLists[] = { commandList.Get() };
			commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

			// Présenter le swap chain
			swapChain->Present(1, 0);

			// Synchronisation avec le GPU via la fence
			fenceValue++;  // Incrémentez la valeur de la fence
			commandQueue->Signal(fence.Get(), fenceValue);
			if (fence->GetCompletedValue() < fenceValue)
			{
				fence->SetEventOnCompletion(fenceValue, fenceEvent);
				WaitForSingleObject(fenceEvent, INFINITE);
			}

			// Mettre à jour l'index du back buffer pour le prochain cycle
			frameIndex = swapChain->GetCurrentBackBufferIndex();
		}
		std::cout << "\n\noups\n\n";
	}
}
