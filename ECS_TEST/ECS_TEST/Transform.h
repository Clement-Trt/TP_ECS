#pragma once

#include <DirectXMath.h>

struct TRANSFORM
{
private:

	// /!\/!\/!\ ___ DANS LES VARIABLES MEMBRES, QUE DES XMFLOAT ___ /!\/!\/!\ 

	DirectX::XMFLOAT3 vScale;

	DirectX::XMFLOAT3 vDirection;
	DirectX::XMFLOAT3 vRight;
	DirectX::XMFLOAT3 vUp;
	DirectX::XMFLOAT4 qRotation;
	DirectX::XMFLOAT4X4 mRotation;

	DirectX::XMFLOAT3 vPosition;

	DirectX::XMFLOAT4X4 matrix;

public:

	TRANSFORM() { Identity(); };

	void Identity();
	void Update();

	void Rotate(float pitch, float yaw, float roll);
	void Move(float frontDir, float rightDir, float upDir);

	float GetPositionX();
	float GetPositionY();
	float GetPositionZ();

};