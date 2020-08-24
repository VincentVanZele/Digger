#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "BaseComponent.h"
#include "Renderer.h"
#include "SceneObject.h"
#include <memory>
#include <algorithm>

engine::GameObject::GameObject(const Float2& pos, float rot, const Float2& sca)
	: m_pParentObject(nullptr)
	, m_pTransform(nullptr)
{
	auto trans = std::make_shared<TransformComponent>();
	
	trans->SetPosition(pos);
	trans->SetRotation(rot);
	trans->SetScale(sca);

	m_pTransform = trans;
}

engine::GameObject::~GameObject()
{
	DestroyObject();

	delete m_pParentObject;
	m_pTransform.reset();

	for (auto comps : m_pComponents)
	{
		comps.reset();
	}
}

std::shared_ptr<engine::GameObject> engine::GameObject::NewGameObject()
{
	auto go = std::make_shared<GameObject>();
	return go;
}

void engine::GameObject::AddComponent(std::shared_ptr<BaseComponent> pComp)
{
	for (auto component : m_pComponents)
	{
		if (component == pComp)
		{
			std::cout<<"GameObject::AddComponent > GameObject already contains this component!";
			return;
		}
	}

	m_pComponents.push_back(pComp);
	pComp->m_pGameObject = shared_from_this();
}

void engine::GameObject::RemoveComponent(std::shared_ptr<BaseComponent> pComp)
{
	auto comp = find(m_pComponents.begin(), m_pComponents.end(), pComp);

	if (comp == m_pComponents.end())
	{
		std::cout<<"GameObject::RemoveComponent > Component is not attached to this GameObject!";
		return;
	}

	m_pComponents.erase(comp);
	pComp->m_pGameObject.reset();
}

std::vector<std::shared_ptr<engine::BaseComponent>> engine::GameObject::GetComponents() const
{
	return m_pComponents;
}

void engine::GameObject::AddChild(std::shared_ptr<GameObject> child)
{
	m_pChildren.push_back(child);

	child->SetParent(this);
	child->m_pScene = m_pScene;

	if (m_IsInitialized)
	{
		child->Initialize();
	}
}

void engine::GameObject::SetParent(GameObject* parent)
{
	m_pParentObject = parent;
}

engine::GameObject* engine::GameObject::GetParent()
{
	return m_pParentObject;
}

void engine::GameObject::SetActive(bool active)
{
	if (m_IsActive != active)
	{
		m_IsActive = active;

		for (auto pComp : m_pComponents)
		{
			pComp->SetActive(active);
		}
	}
}

bool engine::GameObject::GetActive() const
{
	return m_IsActive;
}

void engine::GameObject::Initialize()
{
	if (m_IsInitialized)
	{
		return;
	}

	for (auto pComp : m_pComponents)
	{
		pComp->Initialize();
	}

	for (auto pChild : m_pChildren)
	{
		for (auto pChildComp : pChild->GetComponents())
		{
			if (pChildComp->GetActive())
			{
				pChildComp->Initialize();
			}
		}
	}

	m_IsInitialized = true;
}

void engine::GameObject::Update()
{
	for (auto pComp : m_pComponents)
	{
		if (pComp->GetActive())
		{
			if (!pComp->m_IsInitialized)
			{
				pComp->Initialize();
				pComp->m_IsInitialized = true;
			}

			pComp->Update();
		}
	}

	for (auto pChild : m_pChildren)
	{
		for (auto pChildComp : pChild->GetComponents())
		{
			if (pChildComp->GetActive())
			{
				if (!pChildComp->m_IsInitialized)
				{
					pChildComp->Initialize();
					pChildComp->m_IsInitialized = true;
				}

				pChildComp->Update();
			}
		}
	}
}

void engine::GameObject::Draw() const
{
	for (auto pComp : m_pComponents)
	{
		pComp->Draw();
	}

	for (auto pChild : m_pChildren)
	{
		for (auto pChildComp : pChild->GetComponents())
		{
			pChildComp->Draw();
		}
	}

}

void engine::GameObject::Destroy()
{
	for (auto pComp : m_pComponents)
	{
		pComp->Destroy();
	}
}

void engine::GameObject::DestroyObject()
{
	delete m_pParentObject;
	m_pTransform.reset();

	for (auto comps : m_pComponents)
	{
		comps.reset();
	}
}



