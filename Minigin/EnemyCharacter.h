#pragma once
#include "BaseComponent.h"
#include "Structs.h"

namespace engine
{
	class GameScenes;
	class Listener;
	class Event;
	class BaseEnemyState;

	class WorldGridComponent;
	class WorldMovementComponent;
	class ColliderComponent;
	class SpriteComponent;

	class EnemyCharacter : public BaseComponent
	{
	public:
		// link to the overall scene and world 
		EnemyCharacter(GameScenes* pScene, std::shared_ptr<WorldGridComponent> spWorld, int tileIndex);
	
		virtual void Initialize() override;
		virtual void Update() override;
		// virtual void Destroy() override;
		virtual void EnemyDie() = 0;

		void Die();

		void InitializeSprite();
	
		void UpdateCollision();

		ColliderTag TagToState(std::string string);

		void SetScene(GameScenes* scene);

		void SetDirection(WorldDirection dir);

		void SetColliderComp(std::shared_ptr<ColliderComponent> sp);
		void SetSpriteComp(std::shared_ptr<SpriteComponent> sp);

		void SetWorldGridComp(std::shared_ptr<WorldGridComponent> sp);
		void SetWorldMovementComp(std::shared_ptr<WorldMovementComponent> sp);

		void SetListener(std::shared_ptr<Listener> sp);

		void SetState(std::shared_ptr<BaseEnemyState> state);

		GameScenes* GetScene() const;

		WorldDirection GetDirection() const;

		std::weak_ptr<GameObject> GetGoldBag() const;

		std::shared_ptr<ColliderComponent> GetColliderComp() const;
		std::shared_ptr<SpriteComponent> GetSpriteComp() const;

		std::shared_ptr<WorldGridComponent> GetWorldGridComp() const;
		std::shared_ptr<WorldMovementComponent> GetWorldMovementComp() const;

		std::shared_ptr<Listener> GetListener() const;
		std::shared_ptr<Event> GetEvent() const;

		std::shared_ptr<BaseEnemyState> GetState() const;

	protected:
	private:
		GameScenes* m_pScene;

		int m_currTileIndex,
			m_goalTileIndex;

		WorldDirection m_Direction = WorldDirection::Default;

		std::weak_ptr<GameObject> m_wpGoldBag;

		std::shared_ptr<BaseEnemyState> m_spState;

		std::shared_ptr<ColliderComponent> m_spColliderComp;
		std::shared_ptr<SpriteComponent> m_spSpriteComp;
		std::shared_ptr<WorldGridComponent> m_spWorldComp;
		std::shared_ptr<WorldMovementComponent> m_spMovementComp;

		std::shared_ptr<Listener> m_spListener;
		std::shared_ptr<Event> m_spDied;
	};
}
