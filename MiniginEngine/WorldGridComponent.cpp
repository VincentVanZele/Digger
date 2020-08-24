#include "MiniginPCH.h"
#include "WorldGridComponent.h"

#include "ServiceLocator.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include "WorldGrid.h"
#include "TransformComponent.h"
#include "AITrajectory.h"

engine::WorldGridComponent::WorldGridComponent(int rows, int cols, const Float2& gridDimension, const Float2& gridOffset)
	: BaseComponent()
	, m_Rows{rows}
	, m_Cols{cols}
	, m_GridDimension{gridDimension}
	, m_Offset{gridOffset}
{
}

void engine::WorldGridComponent::Initialize()
{
	// grid
	float newDimX = m_GridDimension._x / m_Cols;
	float newDimY = m_GridDimension._y / m_Rows;

	m_TileDimension = Float2(newDimX, newDimY);

	// tile
	int numberOfTiles = m_Rows * m_Cols;

	for (int i{}; i < numberOfTiles; ++i)
	{
		// dispatch tiles on the grid depending on dimension
		float tileCenterX{ m_TileDimension._x * (i % m_Cols) };
		float tileCenterY{ m_TileDimension._y * (i % m_Rows) };

		// add tiles to vector
		m_vTiles.push_back(WorldGridTile(this, Float2(tileCenterX + m_Offset._x, tileCenterY + m_Offset._y)));
	}
}

void engine::WorldGridComponent::Draw()
{
	for (size_t i{}; i < m_vTiles.size(); ++i)
	{
		m_vTiles[i].Draw();
	}
}

void engine::WorldGridComponent::SetRows(int rows)
{
	m_Rows = rows;
}

int engine::WorldGridComponent::GetRows() const
{
	return m_Rows;
}

void engine::WorldGridComponent::SetCols(int cols)
{
	m_Cols = cols;
}

int engine::WorldGridComponent::GetCols() const
{
	return m_Cols;
}

void engine::WorldGridComponent::SetGridDimension(const Float2& gridDim)
{
	m_GridDimension = gridDim;
}

engine::Float2 engine::WorldGridComponent::GetGridDimension() const
{
	return m_GridDimension;
}

void engine::WorldGridComponent::SetOffset(const Float2& offset)
{
	m_Offset = offset;
}

engine::Float2 engine::WorldGridComponent::GetOffset() const
{
	return m_Offset;
}

void engine::WorldGridComponent::SetTileDimension(const Float2& tileDim)
{
	m_TileDimension = tileDim;
}

engine::Float2 engine::WorldGridComponent::GetTileDimension() const
{
	return m_TileDimension;
}

std::vector<engine::WorldGridTile> engine::WorldGridComponent::GetTiles() const
{
	return m_vTiles;
}

int engine::WorldGridComponent::GetTileFromPosition(const Float2& position)
{
	for (size_t i{}; i < m_vTiles.size(); ++i)
	{
		if (m_vTiles[i].ComparePosition(position))
		{
			return i;
		}
	}
	return 0;
}

engine::Float2 engine::WorldGridComponent::GetPositionFromTile(int tileIndex)
{
	if ((size_t)tileIndex >= m_vTiles.size() || tileIndex < 0)
	{
		std::cout << "Invalid index\n";
		return m_vTiles[0].GetPosition();
	}

	return m_vTiles[tileIndex].GetPosition();
}

engine::Float4 engine::WorldGridComponent::GetShapeFromTile(int tileIndex)
{
	Float4 shape{ m_vTiles[tileIndex].GetPosition()._x,m_vTiles[tileIndex].GetPosition()._y,m_TileDimension._x,m_TileDimension._y };

	shape._x -= m_TileDimension._x / 2;
	shape._y -= m_TileDimension._y / 2;

	return shape;
}

int engine::WorldGridComponent::GetLayerFromTile(int tileIndex)
{
	if (!m_usingLayers)
	{
		return 0;
	}

	return (tileIndex / m_Cols) / m_numberLayers;
}

bool engine::WorldGridComponent::GetBlankFromTile(int tileIndex)
{
	return m_vTiles[tileIndex].GetIsBlank();
}

void engine::WorldGridComponent::SetBlockTile(int tileIndex, bool block)
{
	m_vTiles[tileIndex].SetIsBlocked(block);
}

void engine::WorldGridComponent::SetTileBlank(int tileIndex, bool blank)
{
	m_vTiles[tileIndex].SetIsBlank(blank);
}

engine::TileSurroundingState engine::WorldGridComponent::GetStateFromTile(int tileIndex)
{
	return m_vTiles[tileIndex].GetSurrState();
}

void engine::WorldGridComponent::SetTrajectoryDeque(std::deque<std::shared_ptr<Trajectory>> deque)
{
	m_dspPossibleNodesTrajectory = deque;
}

std::deque<std::shared_ptr<engine::Trajectory>> engine::WorldGridComponent::GetTrajectoryDeque() const
{
	return m_dspPossibleNodesTrajectory;
}

std::deque<std::shared_ptr<engine::Trajectory>> engine::WorldGridComponent::GeneratePossibleNodeTrajectory(std::shared_ptr<Trajectory> trajectory)
{
	std::deque<std::shared_ptr<engine::Trajectory>> deque{};

	if (CanFollowPath(int(trajectory->GetIndex()), WorldDirection::Left))
	{
		deque.push_back(std::make_shared<Trajectory>(trajectory,trajectory->GetIndex() - 1, WorldDirection::Left));
	}
	if (CanFollowPath(int(trajectory->GetIndex()), WorldDirection::Right))
	{
		deque.push_back(std::make_shared<Trajectory>(trajectory, trajectory->GetIndex() - 1, WorldDirection::Right));
	}
	if (CanFollowPath(int(trajectory->GetIndex()), WorldDirection::Up))
	{
		deque.push_back(std::make_shared<Trajectory>(trajectory, trajectory->GetIndex() - m_Cols, WorldDirection::Up));
	}
	if (CanFollowPath(int(trajectory->GetIndex()), WorldDirection::Down))
	{
		deque.push_back(std::make_shared<Trajectory>(trajectory, trajectory->GetIndex() + m_Cols, WorldDirection::Down));
	}
	
	return deque;
}

bool engine::WorldGridComponent::CanFollowPath(int position, WorldDirection direction)
{
	int dest{};
	bool outOfBounds{ false }, condition1{ false }, condition2{ false };

	switch (direction)
	{
	case WorldDirection::Up:

		// check wether path is out of bounds
		outOfBounds = (position / m_Cols) > 0;
		if (!outOfBounds) 
		{
			return false;
		}

		dest = position - m_Cols;
		condition1 = m_vTiles[position].GetSurrState()._UpState;
		condition2 = m_vTiles[dest].GetSurrState()._DownState;
		break;

	case WorldDirection::Down:

		// check wether path is out of bounds
		outOfBounds = (position / m_Cols) < (m_Rows - 1);
		if (!outOfBounds)
		{
			return false;
		}

		dest = position + m_Cols;
		condition1 = m_vTiles[position].GetSurrState()._DownState;
		condition2 = m_vTiles[dest].GetSurrState()._UpState;
		break;

	case WorldDirection::Left:

		// check wether path is out of bounds
		outOfBounds = (position % m_Cols) > 0;
		if (!outOfBounds)
		{
			return false;
		}

		dest = position - 1;
		condition1 = m_vTiles[position].GetSurrState()._LeftState;
		condition2 = m_vTiles[dest].GetSurrState()._RightState;
		break;

	case WorldDirection::Right:

		// check wether path is out of bounds
		outOfBounds = (position % m_Cols) < (m_Cols - 1);
		if (!outOfBounds)
		{
			return false;
		}

		dest = position + 1;
		condition1 = m_vTiles[position].GetSurrState()._RightState;
		condition2 = m_vTiles[dest].GetSurrState()._LeftState;
		break;
	}

	if (outOfBounds)
	{
		if (condition1 || m_vTiles[position].GetIsBlank())
		{
			if (!m_vTiles[dest].GetIsBlocked())
			{
				if (m_vTiles[dest].GetIsBlank())
					return true;
				else if (condition2 && m_vTiles[dest].GetSurrState()._DefaultState)
					return true;
			}
		}
	}

	return false;
}

bool engine::WorldGridComponent::GeneratePath(std::deque<engine::WorldDirection>& pathDir, int start, int end)
{
	// Find out if targetnode is enterable
	if (m_vTiles[end].GetIsBlocked())
		return false;
	if (!m_vTiles[end].GetSurrState()._DefaultState && !m_vTiles[end].GetIsBlank())
		return false;


	// SETUP
	// Find all possible connections from source to start with
	std::deque<std::shared_ptr<Trajectory>> openList{};
	std::deque<std::shared_ptr<Trajectory>> closedList{};

	// We came from nowhere -> detect in set up new path to stop there
	std::shared_ptr<Trajectory> startNode{ std::make_shared<Trajectory>(nullptr,start, WorldDirection::Default) };

	openList.push_back(startNode);

	// Keep going as long as we have nodes to explore
	while (!openList.empty())
	{
		// Get next node from openlist and put it in closedlist
		std::shared_ptr<Trajectory> thisNode{ openList.front() };
		openList.pop_front();
		closedList.push_back(thisNode);

		// Get all possible connections
		auto conns = GeneratePossibleNodeTrajectory(thisNode);
		for (size_t i{}; i < conns.size(); ++i)
		{
			if (std::find_if(closedList.begin(), closedList.end(), [conns, i](std::shared_ptr<Trajectory> node) {return conns[i]->GetIndex() == node->GetIndex(); }) == closedList.end())
			{
				if (std::find_if(openList.begin(), openList.end(), [conns, i](std::shared_ptr<Trajectory> node) {return conns[i]->GetIndex() == node->GetIndex(); }) == openList.end())
				{
					// Check if we reached target node
					if (conns[i]->GetIndex() == end)
					{
						// Setup new path
						pathDir.clear(); // Clear previous path
						std::shared_ptr<Trajectory> currNode{ conns[i] };
						while (currNode->GetTrajectory()) // We don't want to add the first node's "None" direction
						{
							pathDir.push_front(currNode->GetWordDirection());
							currNode = currNode->GetTrajectory();
						}

						return true;
					}

					openList.push_back(conns[i]);
				}
			}
		}
	}
	
	return false;
}

#pragma warning( push )  
#pragma warning( disable : 26451 )
engine::TileMovement engine::WorldGridComponent::Move(WorldDirection wDirection, const std::vector<int>& ghostTiles, int tile, bool canBreak, bool canGhost )
{
	if ((size_t)tile >= m_vTiles.size() || tile < 0)
	{
		std::cout << "Invalid tile index\n";
		return TileMovement::Closed;
	}

	switch (wDirection) // get surrounding states
	{
		// left  
	case WorldDirection::Left:
		if ((tile % m_Cols) == 0)
		{
			return TileMovement::Closed;
		}
		break;

		// right 
	case WorldDirection::Right:
		if ((tile % m_Cols) == (m_Cols - 1))
		{
			return TileMovement::Closed;
		}
		break;

		// up 
	case WorldDirection::Up:
		if ((tile / m_Cols) == 0)
		{
			return TileMovement::Closed;
		}
		break;

		// down 
	case WorldDirection::Down:
		if ((tile / m_Cols) == (m_Rows - 1))
		{
			return TileMovement::Closed;
		}
		break;
	}

	// ghost tiles = invisible 
	if (std::find(ghostTiles.begin(), ghostTiles.end(), (tile)) != ghostTiles.end())
	{
		return TileMovement::Open;
	}

	// ghost tiles
	if (!canBreak)
	{
		// if open
		if (m_vTiles[tile].GetIsBlank())
		{
			// get surrounding state
			switch (wDirection)
			{
			case WorldDirection::Left: // ghost left

				if (std::find(ghostTiles.begin(), ghostTiles.end(), (tile - 1)) != ghostTiles.end())
				{
					return TileMovement::Open;
				}
				if (m_vTiles[tile - 1].GetIsBlank())
				{
					return TileMovement::Open;
				}
				if (m_vTiles[tile - 1].GetSurrState()._RightState)
				{
					return TileMovement::Open;
				}
				else if (canGhost)
				{
					return TileMovement::Open;
				}

				return TileMovement::Closed;

			case WorldDirection::Right: // ghost right

				if (std::find(ghostTiles.begin(), ghostTiles.end(), (tile + 1)) != ghostTiles.end())
				{
					return TileMovement::Open;
				}
				if (m_vTiles[tile + 1].GetIsBlank())
				{
					return TileMovement::Open;
				}

				if (m_vTiles[tile + 1].GetSurrState()._LeftState)
				{
					return TileMovement::Open;
				}
				else if (canGhost)
				{
					return TileMovement::Open;
				}

				return TileMovement::Closed;

			case WorldDirection::Up: // ghost up

				if (std::find(ghostTiles.begin(), ghostTiles.end(), (tile - m_Cols)) != ghostTiles.end())
				{
					return TileMovement::Open;
				}
				if (m_vTiles[tile - m_Cols].GetIsBlank())
				{
					return TileMovement::Open;
				}

				if (m_vTiles[tile - m_Cols].GetSurrState()._DownState)
				{
					return TileMovement::Open;
				}
				else if (canGhost)
				{
					return TileMovement::Open;
				}

				return TileMovement::Closed;

			case WorldDirection::Down: // ghost down

				if (std::find(ghostTiles.begin(), ghostTiles.end(), (tile + m_Cols)) != ghostTiles.end())
				{
					return TileMovement::Open;
				}
				if (m_vTiles[tile + m_Cols].GetIsBlank())
				{
					return TileMovement::Open;
				}

				if (m_vTiles[tile + m_Cols].GetSurrState()._UpState)
				{
					return TileMovement::Open;
				}
				else if (canGhost)
				{
					return TileMovement::Open;
				}

				return TileMovement::Closed;

			}
		}
		else // if not open
		{
			switch (wDirection)
			{
			case WorldDirection::Left: // go left

				if (m_vTiles[tile].GetSurrState()._LeftState)
				{
					if (std::find(ghostTiles.begin(), ghostTiles.end(), (tile - 1)) != ghostTiles.end())
					{
						return TileMovement::Open;
					}
					if (m_vTiles[tile - 1].GetSurrState()._RightState)
					{
						return TileMovement::Open;
					}
				}
				else if (canGhost && m_vTiles[tile - 1].GetSurrState()._DefaultState)
				{
					return TileMovement::Open;
				}
				return TileMovement::Closed;

			case WorldDirection::Right: // go right

				if (m_vTiles[tile].GetSurrState()._RightState) 
				{
					if (std::find(ghostTiles.begin(), ghostTiles.end(), (tile + 1)) != ghostTiles.end())
					{
						return TileMovement::Open;
					}
					if (m_vTiles[tile + 1].GetSurrState()._LeftState)
					{
						return TileMovement::Open;
					}
				}
				else if (canGhost && m_vTiles[tile + 1].GetSurrState()._DefaultState)
				{
					return TileMovement::Open;
				}

				return TileMovement::Closed;

			case WorldDirection::Up: // go up

				if (m_vTiles[tile].GetSurrState()._UpState) 
				{
					if (std::find(ghostTiles.begin(), ghostTiles.end(), (tile - m_Cols)) != ghostTiles.end())
					{
						return TileMovement::Open;
					}
					if (m_vTiles[tile - m_Cols].GetSurrState()._DownState)
					{
						return TileMovement::Open;
					}
				}
				else if (canGhost && m_vTiles[tile - m_Cols].GetSurrState()._DefaultState)
				{
					return TileMovement::Open;
				}

				return TileMovement::Closed;

			case WorldDirection::Down: // go down

				if (m_vTiles[tile].GetSurrState()._DownState) 
				{
					if (std::find(ghostTiles.begin(), ghostTiles.end(), (tile + m_Cols)) != ghostTiles.end())
					{
						return TileMovement::Open;
					}
					if (m_vTiles[tile + m_Cols].GetSurrState()._UpState)
					{
						return TileMovement::Open;
					}
				}
				else if (canGhost && m_vTiles[tile + m_Cols].GetSurrState()._DefaultState)
				{
					return TileMovement::Open;
				}

				return TileMovement::Closed;
			}
		}
	}
	else // surrounding states check
	{
		switch (wDirection)
		{
		case WorldDirection::Left:
		{
			// Blank - Open 
			if (m_vTiles[tile].GetIsBlank() && m_vTiles[tile - 1].GetIsBlank())
			{
				return TileMovement::Open;
			}

			// Blocked
			if (m_vTiles[tile - 1].GetIsBlocked())
			{
				return TileMovement::Closed;
			}

			// Partialy open
			if (m_vTiles[tile].GetSurrState()._LeftState && m_vTiles[size_t(tile - 1)].GetSurrState()._RightState && m_vTiles[tile - 1].GetSurrState()._DefaultState)
			{
				return TileMovement::Open;
			}

			// Else, break tile
			m_vTiles[tile].SetSurrState(TileSurrounding::Left, true);
			m_vTiles[tile - 1].SetSurrState(TileSurrounding::Right, true);

			return TileMovement::Breaking;
		}

		case WorldDirection::Right:
		{
			// Blank - Open
			if (m_vTiles[tile].GetIsBlank() && m_vTiles[tile + 1].GetIsBlank())
			{
				return TileMovement::Open;
			}

			// Blocked
			if (m_vTiles[tile + 1].GetIsBlocked())
			{
				return TileMovement::Closed;
			}

			// Partialy open
			if (m_vTiles[tile].GetSurrState()._RightState && m_vTiles[tile + 1].GetSurrState()._LeftState && m_vTiles[tile + 1].GetSurrState()._DefaultState)
			{
				return TileMovement::Open;
			}

			// Else, break tile
			m_vTiles[tile].SetSurrState(TileSurrounding::Right, true);
			m_vTiles[tile + 1].SetSurrState(TileSurrounding::Left, true);
			return TileMovement::Breaking;
		}
		case WorldDirection::Up:
		{
			// Blank - Open
			if (m_vTiles[tile].GetIsBlank() && m_vTiles[tile - m_Cols].GetIsBlank())
			{
				return TileMovement::Open;
			}

			// Blocked
			if (m_vTiles[tile - m_Cols].GetIsBlocked())
			{
				return TileMovement::Closed;
			}

			// Partialy open
			if (m_vTiles[tile].GetSurrState()._UpState && m_vTiles[tile - m_Cols].GetSurrState()._DownState && m_vTiles[tile - m_Cols].GetSurrState()._DefaultState)
			{
				return TileMovement::Open;
			}

			// Else, break tile
			m_vTiles[tile].SetSurrState(TileSurrounding::Up, true);
			m_vTiles[tile - m_Cols].SetSurrState(TileSurrounding::Down, true);
			return TileMovement::Breaking;
		}

		case WorldDirection::Down:
		{
			// Blank - Open
			if (m_vTiles[tile].GetIsBlank() && m_vTiles[tile + m_Cols].GetIsBlank())
			{
				return TileMovement::Open;
			}

			// Blocked
			if (m_vTiles[tile + m_Cols].GetIsBlocked())
			{
				return TileMovement::Closed;
			}

			// Partialy open
			if (m_vTiles[tile].GetSurrState()._DownState && m_vTiles[tile + m_Cols].GetSurrState()._UpState && m_vTiles[tile + m_Cols].GetSurrState()._DefaultState)
			{
				return TileMovement::Open;
			}

			// Else, break tile
			m_vTiles[tile].SetSurrState(TileSurrounding::Down, true);
			m_vTiles[tile + m_Cols].SetSurrState(TileSurrounding::Up, true);
			return TileMovement::Breaking;
		}
		}
	}

	return TileMovement::Closed;
}
#pragma warning (pop)

void engine::WorldGridComponent::SetNumberOfLayers(int layers)
{
	m_numberLayers = layers;
}

int engine::WorldGridComponent::GetNumberOfLayers() const
{
	return m_numberLayers;
}

void engine::WorldGridComponent::SetUsingLayers(bool useLayers)
{
	m_usingLayers = useLayers;
}

bool engine::WorldGridComponent::GetUsingLayers() const
{
	return m_usingLayers;
}

// --------- OBSTACLE ---------
engine::WorldObstacleComponent::WorldObstacleComponent(std::shared_ptr<WorldGridComponent>& spWorld, int tileIndex)
	: m_spWorldComponent{spWorld}
	, m_tileIndex{tileIndex}
{
}

void engine::WorldObstacleComponent::Initialize()
{
	// block defined tile 
	m_spWorldComponent->SetBlockTile(m_tileIndex, true);

	// update position of component 
	GetTransform()->SetPosition(m_spWorldComponent->GetPositionFromTile(m_tileIndex));
}
