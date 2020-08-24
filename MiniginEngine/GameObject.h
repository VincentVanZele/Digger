#pragma once
#include <memory>
#include "TransformComponent.h"
#include "Texture2D.h"
#include "SceneObject.h"
#include "Scene.h"

namespace engine
{
	// derived from SceneObjcet but i needed enable shared
	class GameObject final : public std::enable_shared_from_this<GameObject>
	{
		friend class BaseComponent;
	public:

		GameObject(const Float2& pos = { 0.f, 0.f }, float rot = 0.0f, const Float2& sca = { 1.f, 1.f });
		virtual ~GameObject();
		
		void Initialize();
		void Update() ;
		void Draw() const ;
		void Destroy() ;

		void DestroyObject();

		static std::shared_ptr<GameObject> NewGameObject();

		std::shared_ptr<TransformComponent> GetTransform() const { return m_pTransform; }

		void AddComponent(std::shared_ptr<BaseComponent> pComp);
		void RemoveComponent(std::shared_ptr<BaseComponent> pComp);
		std::vector<std::shared_ptr<BaseComponent>> GetComponents() const;
		// Template
		template<class T>
		T* GetComponent(bool searchChildren = false)
		{
			const std::type_info& templateInfo = typeid(T);
			for (BaseComponent* const pComp : m_pComponents)
			{
				if (pComp && typeid(*pComp) == templateInfo)
				{
					return dynamic_cast<T*>(pComp);
				}
			}

			if (searchChildren)
			{
				for (auto* child : m_pChildren)
				{
					if (child->GetComponent<T>(searchChildren) != nullptr)
					{
						return child->GetComponent<T>(searchChildren);
					}
				}
			}

			return nullptr;
		}

		template <class T>
		bool HasComponent(bool searchChildren = false)
		{
			return GetComponent<T>(searchChildren) != nullptr;
		}

		void AddChild(std::shared_ptr<GameObject> child);

		void SetParent(GameObject* parent);
		GameObject* GetParent();

		void SetActive(bool active);
		bool GetActive() const;

	protected:
	private:
		bool m_IsInitialized = false;
		bool m_IsActive = true;

		std::shared_ptr<TransformComponent> m_pTransform;
		std::vector<std::shared_ptr<BaseComponent>> m_pComponents;

		GameObject* m_pParentObject;
		Scene* m_pScene = nullptr;

		std::vector<std::shared_ptr<GameObject>> m_pChildren;
	};

}
