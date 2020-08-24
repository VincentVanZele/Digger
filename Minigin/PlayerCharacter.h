#pragma once
#include "BaseComponent.h"
#include "Structs.h"
#include <memory>

#include "GameObject.h"

#include "SpriteComponent.h"
#include "WorldGridComponent.h"
#include "WorldMovementComponent.h"
#include "ColliderComponent.h"

namespace engine
{
	class WorldGridComponent;
	class GameScenes;
	class FireBall;

	class PlayerCharacter final : public BaseComponent
	{
	public:
		PlayerCharacter(std::shared_ptr<WorldGridComponent> spWorld, GameScenes* scene, int startTileIndex, int index);

		void Initialize();
		void SetupSprite();
		void UpdateCollision();

		//virtual void Initialize() override;
		virtual void Update() override;
		//virtual void Destroy() override;

		ColliderTag TagToState(std::string string);

		void HandleMovement();

		Float2 GetMovementFromKeyboard();
		Float2 GetMovementFromController();

		void HandleShooting();

		void FireBallHit();
		void FireBallMiss();

		void Respawn(int tileIndex);

		int GetCurrPosByTile() const;
		int GetPlayerIndex() const;

	protected:
	private:
		bool m_IsInitialized = false;

		int m_startTile,
			m_playerIndex;

		GameScenes* m_pGameScene;

		float m_speed,
			m_DieDeltaT, m_MaxDieDeltaT;

		bool m_Shooting = false,
			m_Died = false;

		std::shared_ptr<GameObject> m_spGameObject;
		std::shared_ptr<ColliderComponent> m_spColliderComp;

		std::shared_ptr<SpriteComponent> m_spSpriteComp;
		WorldDirection m_Direction = WorldDirection::Default;
		std::string m_Animation = "Left"; // default

		std::shared_ptr<WorldGridComponent> m_spWorldComp;
		std::shared_ptr<WorldMovementComponent> m_spMovementComp;

		TileState m_CurrTileState = TileState::Default;
	};
}