#include "MiniginPCH.h"
#include "ColliderComponent.h"

#include "CollisionManager.h"
#include "ServiceLocator.h"

engine::ColliderComponent::ColliderComponent(std::string tag)
	:BaseComponent()
	, m_tag(tag)
{
}

void engine::ColliderComponent::Initialize()
{
	if (m_IsInitialized)
	{
		return;
	}
	m_IsInitialized = true;

	ServiceLocator::GetCollisionManager()->GetInstance().AddObject(this);
}

void engine::ColliderComponent::Destroy()
{
	ServiceLocator::GetCollisionManager()->GetInstance().RemoveObject(this);
}

std::string engine::ColliderComponent::GetTag()
{
	return m_tag;
}

void engine::ColliderComponent::SetTag(std::string tag)
{
	m_tag = tag;
}

std::string engine::ColliderComponent::GetCollidedTag()
{
	return m_pColliderComp->m_tag;
}

void engine::ColliderComponent::SetCollidedTag(std::string tag)
{
	m_pColliderComp->m_tag = tag;
}

size_t engine::ColliderComponent::GetId()
{
	return m_id;
}

void engine::ColliderComponent::SetId(size_t id)
{
	m_id = id;
}

bool engine::ColliderComponent::CompareId(size_t id)
{
	return m_id == id;
}

engine::Float4 engine::ColliderComponent::GetCollisionRect() const
{
	return m_collisionRect;
}

void engine::ColliderComponent::SetCollisionRect(const Float4& rect)
{
	m_collisionRect = rect;
}

engine::ColliderComponent* engine::ColliderComponent::GetColliderComp()
{
	return m_pColliderComp;
}

void engine::ColliderComponent::AddTarget(std::string target)
{
	if(std::find(m_vTargets.begin(), m_vTargets.end(), target) == m_vTargets.end())
	// if already exists
	{
		m_vTargets.push_back(target);
	}
}

void engine::ColliderComponent::RemoveTarget(std::string target)
{
	m_vTargets.erase
	(
		std::remove(m_vTargets.begin(), m_vTargets.end(), target), m_vTargets.end()
	);
}

std::vector<std::string> engine::ColliderComponent::GetTargetVector()
{
	return m_vTargets;
}

void engine::ColliderComponent::SetTargetVector(std::vector<std::string> targetVect)
{
	m_vTargets = targetVect;
}

engine::Event engine::ColliderComponent::GetEvent() const
{
	return m_HasCollided;
}

void engine::ColliderComponent::SetEvent(Event event)
{
	m_HasCollided = event;
}
