#pragma once
#include "BaseComponent.h"
#include "Structs.h"
#include <deque>

namespace engine
{
	struct Trajectory;
	class Texture2D;
	class WorldGridTile;

	class WorldGridComponent final : public BaseComponent
	{
	public:
		//WorldGridComponent() = default;
		//~WorldGridComponent() = default; managed by base component

		WorldGridComponent(int rows, int cols, const Float2& gridDimension, const Float2& gridOffset);
	
		virtual void Initialize() override;
		virtual void Draw() override;

		// -------- Grid Set Up --------
		// -----------------------------

		void SetRows(int rows);
		int GetRows() const;
		
		void SetCols(int cols);
		int GetCols() const;

		void SetGridDimension(const Float2& gridDim);
		Float2 GetGridDimension() const;

		void SetOffset(const Float2& offset);
		Float2 GetOffset() const;

		// -------- Tiles --------
		// -----------------------
		void SetTileDimension(const Float2& tileDim);
		Float2 GetTileDimension() const;

		std::vector<WorldGridTile> GetTiles() const;

		int GetTileFromPosition(const Float2& position);

		Float2 GetPositionFromTile(int tileIndex);

		Float4 GetShapeFromTile(int tileIndex);

		int GetLayerFromTile(int tileIndex);

		bool GetBlankFromTile(int tileIndex);

		void SetBlockTile(int tileIndex, bool block);

		void SetTileBlank(int tileIndex, bool blank);

		TileSurroundingState GetStateFromTile(int tileIndex);

		// -------- Path Finding --------
		// ------------------------------
		void SetTrajectoryDeque(std::deque<std::shared_ptr<Trajectory>> deque);
		std::deque<std::shared_ptr<Trajectory>> GetTrajectoryDeque() const;

		std::deque<std::shared_ptr<Trajectory>> GeneratePossibleNodeTrajectory(std::shared_ptr<Trajectory> trajectory);
		
		bool CanFollowPath(int position, WorldDirection direction);
		bool GeneratePath(std::deque<engine::WorldDirection>& pathDir, int start, int end);

		TileMovement Move(WorldDirection wDirection, const std::vector<int>& ghostTiles, int start, bool canBreak, bool canGhost);

		// -------- Layers --------
		// ------------------------
		void SetNumberOfLayers(int layers);
		int GetNumberOfLayers() const;

		void SetUsingLayers(bool useLayers);
		bool GetUsingLayers() const;

	protected:
	private:
		int m_Rows = {},
			m_Cols = {};

		Float2 m_GridDimension,
			m_Offset,
			m_TileDimension;

		std::vector<WorldGridTile> m_vTiles = {};

		// "Expansion of a std::deque is cheaper than the expansion of a std::vector
		// because it doesn't involve copying the existing elements to new memory."
		std::deque<std::shared_ptr<Trajectory>> m_dspPossibleNodesTrajectory;
	
		int m_numberLayers = {};
		bool m_usingLayers = false;
	};

	// --------- Obstacle ---------
	class WorldObstacleComponent final : public BaseComponent
	{
	public:
		//WorldComponent() = default;
		//~WorldComponent() = default; 

		// block certain tiles definitely
		WorldObstacleComponent(std::shared_ptr<WorldGridComponent>& spWorld, int tileIndex);

		virtual void Initialize() override;
		// virtual void Update() override;

	protected:
	private:
		std::shared_ptr<WorldGridComponent> m_spWorldComponent;

		int m_tileIndex;
	};
}