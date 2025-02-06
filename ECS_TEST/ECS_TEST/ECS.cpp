#include "ecs.h"

namespace ECS {

    EntityID EntityManager::createEntity() {
        EntityID id = nextID++;
        entities.push_back(id);
        return id;
    }

	EntityID EntityManager::createPNJEntity()
	{
		EntityID newId = PNJs::nextID;
		archetypePosVel.entityIDs.push_back(newId);
		archetypePosVel.positions.push_back({/* valeurs initiales */ });
		archetypePosVel.velocities.push_back({/* valeurs initiales */ });

		return EntityID();
	}

    void EntityManager::destroyEntity(EntityID id) {
        // Suppression simple (à améliorer avec une vraie gestion)
        entities.erase(std::remove(entities.begin(), entities.end(), id), entities.end());
    }

    void MovementSystem::update(std::vector<Components::Position>& positions,
        std::vector<Components::Velocity>& velocities,
        float deltaTime) {
        for (size_t i = 0; i < positions.size(); ++i) {
            positions[i].x += velocities[i].vx * deltaTime;
            positions[i].y += velocities[i].vy * deltaTime;
        }
    }
	//void MovementSystem::Update(std::vector<Components::Transformable>& transformables, float deltaTime)
	void MovementSystem::Update(Components::Transformable& transformable)
	{
		DirectX::XMVECTOR scale = DirectX::XMLoadFloat3(&transformable.vScale);
		DirectX::XMVECTOR rotation = DirectX::XMLoadFloat4(&transformable.qRotation);
		DirectX::XMVECTOR position = DirectX::XMLoadFloat3(&transformable.vPosition);

		DirectX::XMMATRIX mRot = DirectX::XMMatrixRotationQuaternion(rotation);

		DirectX::XMStoreFloat4x4(&transformable.mRotation, mRot);

		DirectX::XMMATRIX mScale = DirectX::XMMatrixScalingFromVector(scale);
		DirectX::XMMATRIX mTrans = DirectX::XMMatrixTranslationFromVector(position);

		DirectX::XMMATRIX mFinal = mScale * mRot * mTrans;
		DirectX::XMStoreFloat4x4(&transformable.matrix, mFinal);

	}

	void MovementSystem::Rotate(Components::Transformable& transformable, float pitch, float yaw, float roll)
	{
		auto& vDirection = transformable.vDirection;
		auto& vRight = transformable.vRight;
		auto& vUp = transformable.vUp;
		auto& qRotation = transformable.qRotation;
		auto& mRotation = transformable.mRotation;


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

		Update(transformable);
	}

	void MovementSystem::Move(Components::Transformable& transformable, float frontDir, float rightDir, float upDir)
	{
		auto& vDirection = transformable.vDirection;
		auto& vRight = transformable.vRight;
		auto& vUp = transformable.vUp;
		auto& vPosition = transformable.vPosition;

		vPosition.z += frontDir * vDirection.z;
		vPosition.x += frontDir * vDirection.x;
		vPosition.y += frontDir * vDirection.y;

		// Déplacement selon le vecteur vRight (droite/gauche)
		vPosition.z += rightDir * vRight.z;
		vPosition.x += rightDir * vRight.x;
		vPosition.y += rightDir * vRight.y;

		// Déplacement selon le vecteur vUp (haut/bas)
		vPosition.z += upDir * vUp.z;
		vPosition.x += upDir * vUp.x;
		vPosition.y += upDir * vUp.y;

		Update();
	}

}
