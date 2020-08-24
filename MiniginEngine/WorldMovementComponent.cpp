#include "MiniginPCH.h"
#include "WorldMovementComponent.h"

#include "ServiceLocator.h"
#include "GameTime.h"

#include "BaseComponent.h"
#include "WorldGridComponent.h"
#include "TransformComponent.h"

engine::WorldMovementComponent::WorldMovementComponent(const std::shared_ptr<WorldGridComponent>& world, int tilePos, float speed, bool canBreak, float breakSpeed, bool canGhost, float ghostSpeed)
	: BaseComponent()
	, m_spWorldGridComp{world}
	, m_CurrentTile{tilePos}
	, m_Speed{speed}
	, m_CanBreak{canBreak}
	, m_BreakingSpeed{breakSpeed}
	, m_CanGhost{canGhost}
	, m_GhostSpeed{ghostSpeed}
{
}

void engine::WorldMovementComponent::Initialize()
{
	m_Position = m_spWorldGridComp->GetPositionFromTile(m_CurrentTile);
	GetTransform()->SetPosition(m_Position);
}

void engine::WorldMovementComponent::Update()
{
	// edge cases
	if (m_IsActive)
	{
		return;
	}

	if (m_TileState == TileState::Default)
	{
		return;
	}

	// Pre-Update Movement 
	if (m_IsGhosting)
	{
		UpdateGhosting();
		return;
	}

	// check trajectory path
	if (m_FollowingTrajectory == true)
	{
		// then go straight ahead
		m_Direction = m_dTrajectory.front();

		// 2nd edge case
		if (m_dTrajectory.empty())
		{
			m_FollowingTrajectory = false;
		}

		// add direction to path vector
		if (GenerateDirection(m_Direction) == TileMovement::Closed)
		{
			m_dTrajectory.pop_front();
			m_Direction = m_dTrajectory.front();
		}
	}

	// Post-Update Movement 
	if (m_CanBreak == true)
	{
		UpdateBreaking();
	}
	else
	{
		UpdateNoBreaking();
	}

	// position update 
	GetTransform()->SetPosition(m_Position);
}

void engine::WorldMovementComponent::Respawn(int startTile)
{
	m_TileState = TileState::Default;
	m_Direction = WorldDirection::Default;
	
	m_CurrentTile = startTile;
	m_dTrajectory = {};
	
	m_Position = m_spWorldGridComp->GetPositionFromTile(m_CurrentTile);
	GetTransform()->SetObjectPosition(m_Position);

	m_FollowingTrajectory = false;
	m_IsActive = false;
}

void engine::WorldMovementComponent::UpdateBreaking()
{
	int tempTile{};

	float absoluteValue{};
	float elapsedTime{};
	float deltaT = ServiceLocator::GetGameTime()->GetDeltaTime();

	Float2 tempPos{ m_Position };
	
	bool verticalAxis{ false };
	
	bool checkpoint{};
	// This function works the same as an update

	// determine which speed
	if (m_TileState == TileState::Moving)
	{
		elapsedTime = deltaT * m_Speed;
	}
	else
	{
		elapsedTime = deltaT * m_BreakingSpeed;
	}

	// determine the direction
	switch (m_Direction)
	{
	case WorldDirection::Left:

		tempPos._x -= elapsedTime;
		tempTile = m_CurrentTile - 1;
		break;

	case WorldDirection::Right:

		tempPos._x += elapsedTime;
		tempTile = m_CurrentTile + 1;
		break;

	case WorldDirection::Up:

		tempPos._y -= elapsedTime;
		tempTile = m_CurrentTile - m_spWorldGridComp->GetCols();
		verticalAxis = true;
		break;

	case WorldDirection::Down:

		tempPos._y += elapsedTime;
		tempTile = m_CurrentTile + m_spWorldGridComp->GetCols();
		verticalAxis = true;
		break;
	}

	// Checkpoint 
	if (verticalAxis)
	{
		absoluteValue = abs(tempPos._y - m_spWorldGridComp->GetPositionFromTile(tempTile)._y);
		checkpoint = absoluteValue < (m_spWorldGridComp->GetTileDimension()._y / 2);
	}
	else
	{
		absoluteValue = abs(tempPos._x - m_spWorldGridComp->GetPositionFromTile(tempTile)._x);
		checkpoint = absoluteValue < (m_spWorldGridComp->GetTileDimension()._x / 2);
	}


	if (abs(absoluteValue) < 1.0f) // arrived at destination
	{
		m_TileState = TileState::Default;
		m_CurrentTile = tempTile;
		m_Position = m_spWorldGridComp->GetPositionFromTile(m_CurrentTile);
		m_Direction = WorldDirection::Default;
	}
	else if (checkpoint) // almost there
	{
		m_TileState = TileState::Moving;
		m_IsAlmostBroken = true;
		m_Position = tempPos;
	}
	else
	{
		m_Position = tempPos;
	}
}

void engine::WorldMovementComponent::UpdateNoBreaking()
{
	// same principle as UpdateBreaking
	int tempTile{};

	float absoluteValue{};
	float elapsedTime{};
	// This function works the same as an update
	float deltaT = ServiceLocator::GetGameTime()->GetDeltaTime();

	Float2 tempPos{ m_Position };

	bool verticalAxis{ false };
	bool checkpoint{};

	// determine which speed
	if (m_TileState == TileState::Moving)
	{
		elapsedTime = deltaT * m_Speed;
	}
	else
	{
		elapsedTime = deltaT * m_BreakingSpeed;
	}

	// determine the direction
	switch (m_Direction)
	{
	case WorldDirection::Left:

		tempPos._x -= elapsedTime;
		tempTile = m_CurrentTile - 1;
		break;

	case WorldDirection::Right:

		tempPos._x += elapsedTime;
		tempTile = m_CurrentTile + 1;
		break;

	case WorldDirection::Up:

		tempPos._y -= elapsedTime;
		tempTile = m_CurrentTile - m_spWorldGridComp->GetCols();
		verticalAxis = true;
		break;

	case WorldDirection::Down:

		tempPos._y += elapsedTime;
		tempTile = m_CurrentTile + m_spWorldGridComp->GetCols();
		verticalAxis = true;
		break;
	}

	// Checkpoint 
	if (verticalAxis)
	{
		absoluteValue = abs(tempPos._y - m_spWorldGridComp->GetPositionFromTile(tempTile)._y);
		checkpoint = absoluteValue < (m_spWorldGridComp->GetTileDimension()._y / 2);
	}
	else
	{
		absoluteValue = abs(tempPos._x - m_spWorldGridComp->GetPositionFromTile(tempTile)._x);
		checkpoint = absoluteValue < (m_spWorldGridComp->GetTileDimension()._x / 2);
	}


	if (abs(absoluteValue) < 1.0f) // arrived at destination
	{
		m_TileState = TileState::Default;
		m_CurrentTile = tempTile;
		m_Position = m_spWorldGridComp->GetPositionFromTile(m_CurrentTile);
		m_Direction = WorldDirection::Default;
	}
	else
	{
		m_Position = tempPos;
	}
}

void engine::WorldMovementComponent::UpdateGhosting()
{
	int cols{ m_spWorldGridComp->GetCols() };
	
	m_CurrentTile = m_spWorldGridComp->GetTileFromPosition(m_Position);
	
	int rowInterval{ int(m_GhostTarget / cols) - int(m_CurrentTile / cols) };
	int colInterval{ int(m_GhostTarget % cols) - int(m_CurrentTile % cols) };

	if (rowInterval == 0 && colInterval == 0) // arrived at destination ?
	{
		Float2 velocityDir( m_spWorldGridComp->GetPositionFromTile(m_GhostTarget)._x - m_Position._x,
			m_spWorldGridComp->GetPositionFromTile(m_GhostTarget)._y - m_Position._y);
		velocityDir.Normalize();

		// vector as in math displacement vectors
		Float2 movementVector = Float2(velocityDir._x * m_GhostSpeed * ServiceLocator::GetGameTime()->GetDeltaTime(),
			velocityDir._y* m_GhostSpeed* ServiceLocator::GetGameTime()->GetDeltaTime() );
		
		m_Position._x += movementVector._x;
		m_Position._y += movementVector._y;
		
		// update position
		GetTransform()->SetPosition(m_Position);

		// position interval length
		float interval = Float2(m_Position._x - m_spWorldGridComp->GetPositionFromTile(m_GhostTarget)._x,
			m_Position._y - m_spWorldGridComp->GetPositionFromTile(m_GhostTarget)._y).Length();
		
		if (interval < 0.5f) // stop ghosting
		{
			m_IsGhosting = false;
		}

		return;
	}

	// Calculate direction
	Float2 normalDir{ 0, 0 };

	if (rowInterval > 0)
	{
		normalDir._y = 1;
	}
	else if (rowInterval < 0)
	{
		normalDir._y = -1;
	}

	if (colInterval > 0)
	{
		normalDir._x = 1;
	}
	else if (colInterval < 0)
	{
		normalDir._x = -1;
	}

	normalDir.Normalize();

	// direction
	Float2 displacement = Float2(normalDir._x * m_GhostSpeed * ServiceLocator::GetGameTime()->GetDeltaTime(),
		normalDir._y * m_GhostSpeed * ServiceLocator::GetGameTime()->GetDeltaTime());

	m_Position._x += displacement._x;
	m_Position._y += displacement._y;
	
	GetTransform()->SetPosition(m_Position);
}

void engine::WorldMovementComponent::SetCanBreak(bool canBreak)
{
	m_CanBreak = canBreak;
}

bool engine::WorldMovementComponent::GetCanBreak() const
{
	return m_CanBreak;
}

void engine::WorldMovementComponent::SetIsAlmostBroken(bool almostBroken)
{
	m_IsAlmostBroken = almostBroken;
}

bool engine::WorldMovementComponent::GetIsAlmostBroken() const
{
	return m_IsAlmostBroken;
}

void engine::WorldMovementComponent::SetCanGhost(bool canGhost)
{
	m_CanGhost = canGhost;
}

bool engine::WorldMovementComponent::GetCanGhost() const
{
	return m_CanGhost;
}

void engine::WorldMovementComponent::SetIsGhosting(bool isGhosting)
{
	m_IsGhosting = isGhosting;
}

bool engine::WorldMovementComponent::GetIsGhosting() const
{
	return m_IsGhosting;
}

void engine::WorldMovementComponent::SetIsFollowingTraj(bool followTrajectory)
{
	m_FollowingTrajectory = followTrajectory;
}

bool engine::WorldMovementComponent::GetIsFollowingTraj() const
{
	return m_FollowingTrajectory;
}

void engine::WorldMovementComponent::SetIsFrozen(bool isFrozen)
{
	m_IsActive = isFrozen;
}

bool engine::WorldMovementComponent::GetIsFrozen() const
{
	return m_IsActive;
}

void engine::WorldMovementComponent::SetSpeed(float speed)
{
	m_Speed = speed;
}

float engine::WorldMovementComponent::GetSpeed() const
{
	return m_Speed;
}

void engine::WorldMovementComponent::SetGhostingSpeed(float ghostSpeed)
{
	m_GhostSpeed = ghostSpeed;
}

float engine::WorldMovementComponent::GetGhostingSpeed() const
{
	return m_GhostSpeed;
}

void engine::WorldMovementComponent::SetBreakingSpeed(float bSpeed)
{
	m_BreakingSpeed = bSpeed;
}

float engine::WorldMovementComponent::GetBreakingSpeed() const
{
	return m_BreakingSpeed;
}

engine::TileMovement engine::WorldMovementComponent::GenerateDirection(WorldDirection newDirection)
{
	if (m_IsActive)
	{
		return TileMovement::Closed;
	}

	if (m_TileState != TileState::Default)
	{
		switch (m_TileState)
		{
		case TileState::Moving:
			return TileMovement::Open;

		case TileState::Breaking:
			return TileMovement::Breaking;
		}
		return TileMovement::Closed;
	}

	if (newDirection == WorldDirection::Default)
	{
		return TileMovement::Closed;
	}

	auto move = m_spWorldGridComp->Move(newDirection, m_vGhostTiles, m_CurrentTile, m_CanBreak, m_CanGhost );

	switch (move)
	{
	case TileMovement::Closed:
		break;

	case TileMovement::Breaking:
		m_Direction = newDirection;
		m_TileState = TileState::Breaking;
		break;

	case TileMovement::Open:
		m_Direction = newDirection;
		m_TileState = TileState::Moving;
		break;
	}

	return move;
}

void engine::WorldMovementComponent::SetDirection(WorldDirection direction)
{
	m_Direction = direction;
}

engine::WorldDirection engine::WorldMovementComponent::GetDirection() const
{
	return m_Direction;
}

std::vector<engine::WorldDirection> engine::WorldMovementComponent::GeneratePossibleDirections() const
{
	std::vector<WorldDirection> result{};

	if (m_spWorldGridComp->CanFollowPath(m_CurrentTile, WorldDirection::Up))
	{
		result.push_back(WorldDirection::Up);
	}
	if (m_spWorldGridComp->CanFollowPath(m_CurrentTile, WorldDirection::Down))
	{
		result.push_back(WorldDirection::Down);
	}
	if (m_spWorldGridComp->CanFollowPath(m_CurrentTile, WorldDirection::Left))
	{
		result.push_back(WorldDirection::Left);
	}
	if (m_spWorldGridComp->CanFollowPath(m_CurrentTile, WorldDirection::Right))
	{
		result.push_back(WorldDirection::Right);
	}

	return result;
}

bool engine::WorldMovementComponent::GeneratePath(int tileIndex)
{
	return (m_FollowingTrajectory = m_spWorldGridComp->GeneratePath(m_dTrajectory, m_CurrentTile, tileIndex));
}

void engine::WorldMovementComponent::SetCurrentTileIndex(int idx)
{
	m_CurrentTile = idx;
}

int engine::WorldMovementComponent::GetCurrentTileIndex() const
{
	return m_CurrentTile;
}

engine::Float2 engine::WorldMovementComponent::GetCurrentTilePosition() const
{
	return m_Position;
}

void engine::WorldMovementComponent::AddTileToGhostVect(int idx)
{
	m_vGhostTiles.push_back(idx);
}

void engine::WorldMovementComponent::RemoveTileFromGhostvect(int idx)
{
	m_vGhostTiles.erase(std::remove(m_vGhostTiles.begin(), m_vGhostTiles.end(), idx), m_vGhostTiles.end());
}
