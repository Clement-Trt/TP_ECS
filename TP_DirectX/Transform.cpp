#include "Transform.h"
#include <DirectXMath.h>


void TRANSFORM::Identity()
{
	vScale = { 1.0f, 1.0f, 1.0f };

	vDirection = { 0.f, 0.f, 1.0f };
	vRight = { 1.0f, 0.f, 0.f };
	vUp = { 0.f, 1.0f, 0.f };

	qRotation = { 0.f, 0.f, 0.f, 1.0f };
	mRotation =
	{
		1.0f, 0.f,  0.f,  0.f,
		0.f, 1.0f,  0.f,  0.f,
		0.f,  0.f, 1.0f,  0.f,
		0.f,  0.f,  0.f, 1.0f
	};

	vPosition = { 0.f, 0.f, 0.f };

	matrix =
	{
		1.0f, 0.f,  0.f,  0.f,
		0.f, 1.0f,  0.f,  0.f,
		0.f,  0.f, 1.0f,  0.f,
		0.f,  0.f,  0.f, 1.0f
	};

}

void TRANSFORM::Update()
{
	DirectX::XMVECTOR scale = DirectX::XMLoadFloat3(&vScale);
	DirectX::XMVECTOR rotation = DirectX::XMLoadFloat4(&qRotation);
	DirectX::XMVECTOR position = DirectX::XMLoadFloat3(&vPosition);

	DirectX::XMMATRIX mRot = DirectX::XMMatrixRotationQuaternion(rotation);

	DirectX::XMStoreFloat4x4(&mRotation, mRot);

	DirectX::XMMATRIX mScale = DirectX::XMMatrixScalingFromVector(scale);
	DirectX::XMMATRIX mTrans = DirectX::XMMatrixTranslationFromVector(position);

	DirectX::XMMATRIX mFinal = mScale * mRot * mTrans;
	DirectX::XMStoreFloat4x4(&matrix, mFinal);

}

void TRANSFORM::Rotate(float pitch, float yaw, float roll)

{
	DirectX::XMVECTOR qRotYPR = DirectX::XMQuaternionIdentity(); // quaternion contenant les 3 rotations

	//Identity(&qRotYPR); // ==> Pour rotation a partir des axes du monde

	DirectX::XMVECTOR qRotTemp; // quaternion contenant qu’une seule rotation

	DirectX::XMVECTOR frontDir = DirectX::XMLoadFloat3(&vDirection);
	DirectX::XMVECTOR rightDir = DirectX::XMLoadFloat3(&vRight);
	DirectX::XMVECTOR upDir = DirectX::XMLoadFloat3(&vUp);
	DirectX::XMVECTOR qRot = DirectX::XMLoadFloat4(&qRotation);

	qRotTemp = DirectX::XMQuaternionRotationAxis(frontDir, roll);
	qRotYPR = DirectX::XMQuaternionMultiply(qRotYPR, qRotTemp);


	qRotTemp = DirectX::XMQuaternionRotationAxis(rightDir, pitch);
	qRotYPR = DirectX::XMQuaternionMultiply(qRotYPR, qRotTemp);


	qRotTemp = DirectX::XMQuaternionRotationAxis(upDir, yaw);
	qRotYPR = DirectX::XMQuaternionMultiply(qRotYPR, qRotTemp);

	qRot = DirectX::XMQuaternionMultiply(qRot, qRotYPR);
	qRot = DirectX::XMQuaternionNormalize(qRot);

	DirectX::XMMATRIX mRot = DirectX::XMMatrixRotationQuaternion(qRot);

	DirectX::XMStoreFloat4(&qRotation, qRot);
	DirectX::XMStoreFloat4x4(&mRotation, mRot);

	vRight = { mRotation._11, mRotation._12, mRotation._13 };
	vUp = { mRotation._21, mRotation._22, mRotation._23 };
	vDirection = { mRotation._31, mRotation._32, mRotation._33 };

	Update();
}

void TRANSFORM::Move(float frontDir, float rightDir, float upDir)
{
	vPosition.z = frontDir;
	vPosition.x = rightDir;
	vPosition.y = upDir;
}

float TRANSFORM::GetPositionX()
{
	return vPosition.x;
}

float TRANSFORM::GetPositionY()
{
	return vPosition.y;
}

float TRANSFORM::GetPositionZ()
{
	return vPosition.z;
}

