#pragma once

#include <DirectXMath.h>

namespace Components 
{
	struct Position {
		float x, y;
	};

	struct Velocity {
		float vx, vy;
	};


	struct Transformable
	{
		DirectX::XMFLOAT3 vScale;

		DirectX::XMFLOAT3 vDirection;
		DirectX::XMFLOAT3 vRight;
		DirectX::XMFLOAT3 vUp;
		DirectX::XMFLOAT4 qRotation;
		DirectX::XMFLOAT4X4 mRotation;

		DirectX::XMFLOAT3 vPosition;

		DirectX::XMFLOAT4X4 matrix;

		// Velocite pas cens�e etre geree ici ? est-ce que c'est pcq la gestion des mouvements se ferait dans un update exterieur
		// => gestion de la velocit� avec fonction move ? Definition : position = vitesse * vecteur direction

		// Faut il garder �a dans la struct pour pouvoir l'initialiser � la construction ?

	/*public:
		TRANSFORM() { Identity(); };

		void Identity();*/
	};
}

