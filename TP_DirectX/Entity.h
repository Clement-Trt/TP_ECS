#pragma once
#include <vector>
#include <string>
#include <memory>

class Component;

class Entity
{
protected:
	int m_id;
	std::vector<Component*> m_components;

public:

	~Entity();

	int GetID() { return m_id; };
	void SetID(int id) { m_id = id; };

	bool AddComponent(Component* component);

	template <typename T>
	T* GetComponent();


};

template <typename T>
inline T* Entity::GetComponent() {
	for (auto& comp : m_components) {
		if (auto casted = dynamic_cast<T*>(comp)) {
			return casted;
		}
	}
	return nullptr;
}
