#pragma once
#include "BaseComponent.h"
#include "Structs.h"
#include <memory>

namespace engine
{
	class WorldGridComponent;
	class WorldMovementComponent;
	class ColliderComponent;

	class Texture2D;
	class Event;

	class FireBall final : public BaseComponent
	{
		friend class PlayerCharacter;

	public:
		FireBall(int playerIndex, std::shared_ptr<WorldGridComponent> spWorld, int tileIndex, Float2& offset, WorldDirection direction);
	
		virtual void Initialize() override;
		virtual void Update() override;

		static void InitializeTexture();

		void UpdateCollision();

		void SetFireBallGameObject(std::shared_ptr<GameObject> go);
		std::shared_ptr<GameObject> GetFireBallGameObject() const;

		void SetWorldComponent(std::shared_ptr<WorldGridComponent> comp);
		std::shared_ptr<WorldGridComponent> GetWorldComponent() const;

		void SetMovementComponent(std::shared_ptr<WorldMovementComponent> comp);
		std::shared_ptr<WorldMovementComponent> GetMovementComponent() const;

		void SetColliderComponent(std::shared_ptr<ColliderComponent> comp);
		std::shared_ptr<ColliderComponent> GetColliderComponent() const;

		void SetSpeed(float speed);
		float GetSpeed() const;

	protected:
		std::shared_ptr<Event> m_spHitOther;
		std::shared_ptr<Event> m_spHitWorld;

	private:

		static bool m_IsInitialized;
		
		std::shared_ptr<GameObject> m_spFireBallObject;
		static std::shared_ptr<Texture2D> m_spFireBallTex;

		std::shared_ptr<WorldGridComponent> m_spWorldComp;
		std::shared_ptr<WorldMovementComponent> m_spMovementComp;
		std::shared_ptr<ColliderComponent> m_spColliderComp;

		int m_startPos;
		
		Float2 m_startOffset;
		float m_currInterval{ 0.0f };
		
		int m_playerIndex = 0;
		WorldDirection m_Direction;

		float m_Speed{ 100.0f };
	};
}
