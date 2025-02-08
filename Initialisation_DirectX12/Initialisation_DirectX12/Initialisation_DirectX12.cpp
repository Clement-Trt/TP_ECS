// Initialisation_DirectX12.cpp : Ce fichier contient la fonction 'main'. L'execution du programme commence et se termine a cet endroit.
//

#include <iostream>
#include <windows.h>
#include <tchar.h> // Pour _T()

#include <d3d12.h>
#include "d3dx12.h"
#include <dxgi1_4.h>
#include <wrl.h>

#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")
//#pragma comment(lib,"d3dcompiler.lib") - PAS UTILE POUR LE MOMENT


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

	// ______________________________________________Description et Creation swap chain ____________________________________________________________________________________________________________________________________________________

	// 2. Decrire la swap chain
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
	swapChainDesc.BufferCount = 2; // On utilise le double buffering
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


	// ______________________________________________Descriptor Heap : Render Target View ____________________________________________________________________________________________________________________________________________________

	const UINT FrameCount = 2;  // Par exemple, 2 pour un double buffering

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap;

	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
	rtvHeapDesc.NumDescriptors = FrameCount;                           // Un descripteur par buffer
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;                   // Type pour les render target views
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;                 // Pas de flags particuliers

	hr = device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));
	if (FAILED(hr))
	{
		// Gérer l'erreur
		return -1;
	}

	// ______________________________________________Creation Render Target View pour chaque buffer de la swap chain ____________________________________________________________________________________________________________________________________________________

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
	}

	std::cout << "oups\n";
}
