#include "MiniginPCH.h"
#include "CollisionManager.h"
#include "ColliderComponent.h"

#include "Utils.h"

void engine::CollisionManager::CalculateCollision()
{
	for (size_t i{}; i < m_vCollisionObjects.size(); ++i)
	{
		auto& colliding = m_vCollisionObjects[i];

		for (size_t j{}; j < m_vCollisionObjects.size(); ++j)
		{
			auto& collider = m_vCollisionObjects[j];

			if (colliding->GetTag() == collider->GetTag())
			{
				continue;
			}

			if (std::find
			(colliding->GetTargetVector().begin(), colliding->GetTargetVector().end(), collider->GetTag())
				== colliding->GetTargetVector().end())
			{
				continue; 
			}

			// if collide
			if (engine::DoRectsOverlap(colliding->GetCollisionRect(), collider->GetCollisionRect()))
			{
				colliding->m_pColliderComp = collider; 
				colliding->m_HasCollided.CallNotify();
			}
		}
	}
}

void engine::CollisionManager::AddObject(ColliderComponent* obj)
{
	m_vCollisionObjects.push_back(obj);
	
	// id
	m_CurrMaxId++;
	obj->SetId(m_CurrMaxId);
}
void engine::CollisionManager::RemoveObject(ColliderComponent* obj)
{
	if (!m_vCollisionObjects.empty())
	{
		m_vCollisionObjects.erase(
			std::remove
			(m_vCollisionObjects.begin(), m_vCollisionObjects.end(), obj)
			, m_vCollisionObjects.end());
	}
}