#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "TransformComponent.h"

#include "GameObject.h"


engine::BaseComponent::BaseComponent()
	:m_pGameObject{}
{
}

void engine::BaseComponent::SetGameObject(std::shared_ptr<GameObject> pGO)
{
	m_pGameObject = pGO;
}

void engine::BaseComponent::SetActive(bool active)
{
	m_IsActive = active;

	if (!m_IsActive)
	{
		bool allInactive = true;

		for (auto pComp : GetGameObject()->m_pComponents)
		{
			if (pComp->GetActive())
			{
				allInactive = false;
				break;
			}
		}
		if (allInactive)
		{
			GetGameObject()->m_IsActive = false;
		}
	}
	else
	{
		GetGameObject()->m_IsActive = true;
	}
}

bool engine::BaseComponent::GetActive() const
{
	return m_IsActive;
}

std::shared_ptr<engine::TransformComponent> engine::BaseComponent::GetTransform() const
{
	// TODO: insert return statement here
#if _DEBUG
	if (GetGameObject() == nullptr)
	{
		std::cout << "BaseComponent::GetTransform() > Failed to retrieve the TransformComponent. GameObject is NULL." << '\n';
	}
#endif

	return GetGameObject()->GetTransform();
}

void engine::BaseComponent::AddComponent(std::shared_ptr<BaseComponent> pComp)
{
	GetGameObject()->AddComponent(pComp);
}

void engine::BaseComponent::RemoveComponent(std::shared_ptr<BaseComponent> pComp)
{
	GetGameObject()->RemoveComponent(pComp);
}

void engine::BaseComponent::DestroyGameObject()
{
	GetGameObject()->DestroyObject();
}

void engine::BaseComponent::AddChild(std::shared_ptr<GameObject> child)
{
	GetGameObject()->AddChild(child);
}






