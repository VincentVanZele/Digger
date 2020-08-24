#pragma once
#include "BaseComponent.h"
#include <memory>

namespace engine
{
	// --- class forward decl
	// Components
	class ColliderComponent;
	class SpriteComponent;
	class WorldGridComponent;
	class WorldMovementComponent;
	class WorldObstacleComponent; // can block

	// scene
	class GameScenes;

	// struct
	class GoldBagState;

	class GoldBag final : public BaseComponent
	{
		friend class GoldBagState;
	public:
		//GoldBag() = default;
		//~GoldBag() = default;

		GoldBag(std::shared_ptr<WorldGridComponent> spWorld, GameScenes* pScene, int tileIdx);

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Destroy() override;

		int GetIndex() const;

		int GetNumberOfKills() const;

		GameScenes* GetScene() const;

		std::shared_ptr<GoldBagState> GetGoldBagState() const;
		void SetState(std::shared_ptr<GoldBagState> state);
		
		// pointer to char
		void SetColliderComp(std::shared_ptr<ColliderComponent> sp);
		void SetSpriteComp(std::shared_ptr<SpriteComponent> sp);
			 
		void SetWorldGridComp(std::shared_ptr<WorldGridComponent> sp);
		void SetWorldMovementComp(std::shared_ptr<WorldMovementComponent> sp);
		void SetWorldObstacleComp(std::shared_ptr<WorldObstacleComponent> sp);

		std::shared_ptr<ColliderComponent> GetColliderComp() const;
		std::shared_ptr<SpriteComponent> GetSpriteComp() const;

		std::shared_ptr<WorldGridComponent> GetWorldGridComp() const;
		std::shared_ptr<WorldMovementComponent> GetWorldMovementComp() const;
		std::shared_ptr<WorldObstacleComponent> GetWorldObstacleComp() const;


	protected:
	private:
		int m_Index;
		int m_Kills = 0;

		GameScenes* m_pScene;

		std::shared_ptr<GoldBagState> m_CurrState;
		
		std::shared_ptr<ColliderComponent> m_spColliderComp;
		std::shared_ptr<SpriteComponent> m_spSpriteComp;

		std::shared_ptr<WorldGridComponent> m_spWorldComp;
		std::shared_ptr<WorldMovementComponent> m_spMovementComp;
		std::shared_ptr<WorldObstacleComponent> m_spObstacleComp;
		
		// char pointer
	};
}
