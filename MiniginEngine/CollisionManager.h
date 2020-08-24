#pragma once
#include "Singleton.h"
#include "Structs.h"

namespace engine
{
	class ColliderComponent;

	class CollisionManager final : public Singleton<CollisionManager>
	{
	public:

		void AddObject(ColliderComponent* object);
		void RemoveObject(ColliderComponent* object);

		void CalculateCollision();

	private:
		std::vector<ColliderComponent*> m_vCollisionObjects = {};
		size_t m_CurrMaxId = 0;
	};
}

