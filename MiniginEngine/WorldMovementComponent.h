#pragma once
#include <vector>
#include <memory>
#include <deque>

#include "BaseComponent.h"
#include "Structs.h"

namespace engine
{
	class WorldGridComponent;
	enum class WorldDirection;
	enum class TileMovement;

	// works in tandem with WorldGridComponent (not always ofc)
	// mainly for enemy behavior around the world
	class WorldMovementComponent final : public BaseComponent
	{
	public:
		//WorldMovementComponent() = default;
		//~WorldMovementComponent() = default;

		WorldMovementComponent(const std::shared_ptr<WorldGridComponent>& spTerrain, int initPos, float speed,
			bool canCarve = false, float carveSpeed = 0.0f, bool canGhost = false, float ghostSpeed = 0.0f);
	
		virtual void Initialize() override;
		virtual void Update() override;
		// virtual void Draw() override; not needed

		void Respawn(int startTile);

		void UpdateBreaking();
		void UpdateNoBreaking();
		void UpdateGhosting();

		// -------- Behavior --------
		void SetCanBreak(bool canBreak);
		bool GetCanBreak() const;

		void SetIsAlmostBroken(bool almostBroken);
		bool GetIsAlmostBroken() const;

		void SetCanGhost(bool canGhost);
		bool GetCanGhost() const;

		void SetIsGhosting(bool isGhosting);
		bool GetIsGhosting() const;

		void SetIsFollowingTraj(bool followTrajectory);
		bool GetIsFollowingTraj() const;

		void SetIsFrozen(bool isFrozen);
		bool GetIsFrozen() const;

		// -------- Movement --------
		void SetSpeed(float speed);
		float GetSpeed() const;

		void SetGhostingSpeed(float ghostSpeed);
		float GetGhostingSpeed() const;

		void SetBreakingSpeed(float bSpeed);
		float GetBreakingSpeed() const;

		TileMovement GenerateDirection(WorldDirection newDirection);
		
		void SetDirection(WorldDirection direction);
		WorldDirection GetDirection() const;

		std::vector<WorldDirection> GeneratePossibleDirections() const;
	
		// --------- Tile ----------
		bool GeneratePath(int tileIndex);

		void SetCurrentTileIndex(int idx);
		int GetCurrentTileIndex() const;

		//void SetCurrentTilePosition(Float2 pos); not needed
		Float2 GetCurrentTilePosition() const;

		void AddTileToGhostVect(int idx);
		void RemoveTileFromGhostvect(int idx);

	protected:
	private:
		int m_CurrentTile{};
		int m_TempTile{};
		int m_GhostTarget{};
	
		bool m_CanBreak = false;
		bool m_IsAlmostBroken = false;
		bool m_IsActive = false;
		bool m_CanGhost = false;
		bool m_IsGhosting = false;
		bool m_FollowingTrajectory = false;
		
		float m_Speed{};
		float m_GhostSpeed{};
		float m_BreakingSpeed{};
		
		Float2 m_Position;

		std::shared_ptr<WorldGridComponent> m_spWorldGridComp;

		WorldDirection m_Direction = WorldDirection::Default;

		TileState m_TileState = TileState::Default;

		std::vector<int> m_vGhostTiles = {};
		std::deque<WorldDirection> m_dTrajectory = {};
	};

}