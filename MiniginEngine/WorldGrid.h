#pragma once
#include "Structs.h"
#include <memory>

namespace engine
{
	class Texture2D;
	class WorldGridComponent;

	// all classes and enums needed for the World Grid components 
	class WorldGridTile
	{
	public:
		WorldGridTile() = default;
		~WorldGridTile() = default;

		WorldGridTile(WorldGridComponent* pWorld, const Float2& position, TileSurroundingState surrState = TileSurroundingState(), bool isBlocked = false, bool isBroken = false);
	
		static void Initialize();
		void Draw();

		void SetGridComponent(WorldGridComponent* gridComp);
		const WorldGridComponent* GetGridComponent() const;

		void SetPosition(const Float2& pos);
		const Float2& GetPosition() const;
		bool ComparePosition(const Float2& pos);

		void SetSurrState(TileSurrounding tile, bool state);
		const TileSurroundingState& GetSurrState() const;

		void SetIsBlocked(bool blocked);
		bool GetIsBlocked() const;

		void SetIsBlank(bool blank);
		bool GetIsBlank() const;
	
	protected:
	private:
		WorldGridComponent* m_pWorldGrid;

		Float2 m_Position = {};
		TileSurroundingState m_TileSurrState = {};
		bool m_isBlocked = false;
		bool m_isBlank = false; // blank world free of any tile

		static std::shared_ptr<Texture2D> m_Tile; // the tile itself
		static std::shared_ptr<Texture2D> m_TileLeft;
		static std::shared_ptr<Texture2D> m_TileRight;
		static std::shared_ptr<Texture2D> m_TileUp;
		static std::shared_ptr<Texture2D> m_TileDown;

		static bool m_hasBeenInitialized;
	};

}

