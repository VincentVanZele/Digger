#pragma once
#include "Transform.h"

namespace engine
{
	class GameObject; //CFD
	class TransformComponent;

	class BaseComponent
	{
		friend class GameObject;
	public:
		BaseComponent(); // no gamecontext
		virtual ~BaseComponent() = default;

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;

		virtual void Initialize() {};
		virtual void Destroy() {};

		virtual void Update() {};
		virtual void LateUpdate() {};

		virtual void Draw() {};

		// Functions
		std::shared_ptr<GameObject> GetGameObject() const 
		{
			auto go = m_pGameObject.lock();
			if (!go)
			{
				throw std::exception("Invalid pointer");
			}
			return go;
		}

		void SetGameObject(std::shared_ptr<GameObject> pGO);

		void SetActive(bool active);
		bool GetActive() const;

		std::shared_ptr<engine::TransformComponent> GetTransform() const;

		void AddComponent(std::shared_ptr<BaseComponent> pComp);
		void RemoveComponent(std::shared_ptr<BaseComponent> pComp);
		void DestroyGameObject();

		void AddChild(std::shared_ptr<GameObject> child);

	protected:
		std::weak_ptr<GameObject> m_pGameObject;

		bool m_IsActive = true;
		bool m_IsPaused = false;
		bool m_IsInitialized = false;
	};
}
