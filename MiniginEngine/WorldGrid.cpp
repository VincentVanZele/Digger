#include "MiniginPCH.h"
#include "WorldGrid.h"

#include "ServiceLocator.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include "WorldGridComponent.h"

std::shared_ptr<engine::Texture2D> engine::WorldGridTile::m_Tile{};
std::shared_ptr<engine::Texture2D> engine::WorldGridTile::m_TileLeft{};
std::shared_ptr<engine::Texture2D> engine::WorldGridTile::m_TileRight{};
std::shared_ptr<engine::Texture2D> engine::WorldGridTile::m_TileUp{};
std::shared_ptr<engine::Texture2D> engine::WorldGridTile::m_TileDown{};

bool engine::WorldGridTile::m_hasBeenInitialized{ false };

engine::WorldGridTile::WorldGridTile(WorldGridComponent* worldGrid, const Float2& position, TileSurroundingState surrState, bool isBlocked, bool isBlank)
	:m_pWorldGrid{worldGrid}
	,m_Position{position}
	,m_TileSurrState{surrState}
	,m_isBlocked{isBlocked}
	,m_isBlank{ isBlank }
{
	if (!m_hasBeenInitialized)
	{
		Initialize();
	}
}

void engine::WorldGridTile::Initialize()
{
	auto resourceManager = ServiceLocator::GetResourceManager();
	
	// initialize all the tile textures
	m_Tile = resourceManager->GetInstance().LoadTexture("Ground/baseGround.png");
	m_TileLeft = resourceManager->GetInstance().LoadTexture("Ground/left.png");
	m_TileRight = resourceManager->GetInstance().LoadTexture("Ground/right.png");
	m_TileUp = resourceManager->GetInstance().LoadTexture("Ground/top.png");
	m_TileDown = resourceManager->GetInstance().LoadTexture("Ground/bottom.png");

	m_hasBeenInitialized = true;
}

void engine::WorldGridTile::Draw()
{
	if (m_isBlank)
	{
		return; // nothing to render
	}

	auto renderer = ServiceLocator::GetRenderer();

	if (m_TileSurrState._DefaultState)
	{
		renderer->GetInstance().RenderTexture(*m_Tile, m_Position._x, m_Position._y,20, 20);
	}
	if (m_TileSurrState._LeftState)
	{
		renderer->GetInstance().RenderTexture(*m_TileLeft, m_Position._x, m_Position._y, 20, 20);
	}
	if (m_TileSurrState._RightState)
	{
		renderer->GetInstance().RenderTexture(*m_TileRight, m_Position._x, m_Position._y, 20, 20);
	}
	if (m_TileSurrState._UpState)
	{
		renderer->GetInstance().RenderTexture(*m_TileUp, m_Position._x, m_Position._y, 20, 20);
	}
	if (m_TileSurrState._DownState)
	{
		renderer->GetInstance().RenderTexture(*m_TileDown, m_Position._x, m_Position._y, 20, 20);
	}
}

void engine::WorldGridTile::SetGridComponent(WorldGridComponent* gridComp)
{
	m_pWorldGrid = gridComp;
}

const engine::WorldGridComponent* engine::WorldGridTile::GetGridComponent() const
{
	return m_pWorldGrid;
}

void engine::WorldGridTile::SetPosition(const Float2& pos)
{
	m_Position = pos;
}

const engine::Float2& engine::WorldGridTile::GetPosition() const
{
	return m_Position;
}

bool engine::WorldGridTile::ComparePosition(const Float2& position)
{
	auto plusX = m_Position._x + m_pWorldGrid->GetTileDimension()._x / 2;
	auto minusX = m_Position._x - m_pWorldGrid->GetTileDimension()._x / 2;
	
	auto plusY = m_Position._y + m_pWorldGrid->GetTileDimension()._y / 2;
	auto minusY = m_Position._y - m_pWorldGrid->GetTileDimension()._y / 2;

	if (position._x > minusX)
	{
		if (position._x < plusX)
		{
			if (position._y > minusY)
			{
				if (position._y < plusY)
				{
					return true;
				}
			}
		}
	}
	return false;
}

void engine::WorldGridTile::SetSurrState(TileSurrounding tile, bool state)
{
	switch (tile)
	{
	case TileSurrounding::Default:
		m_TileSurrState._DefaultState = state;
		break;

	case TileSurrounding::Left:
		m_TileSurrState._LeftState = state;
		break;

	case TileSurrounding::Right:
		m_TileSurrState._RightState = state;
		break;

	case TileSurrounding::Up:
		m_TileSurrState._UpState = state;
		break;

	case TileSurrounding::Down:
		m_TileSurrState._DownState = state;
		break;
	}
}

const engine::TileSurroundingState& engine::WorldGridTile::GetSurrState() const
{
	return m_TileSurrState;
}

void engine::WorldGridTile::SetIsBlocked(bool blocked)
{
	m_isBlocked = blocked;
}

bool engine::WorldGridTile::GetIsBlocked() const
{
	return m_isBlocked;
}

void engine::WorldGridTile::SetIsBlank(bool blank)
{
	m_isBlank = blank;
}

bool engine::WorldGridTile::GetIsBlank() const
{
	return m_isBlank;
}
