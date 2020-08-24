#include "pch.h"
#include "EnemyState.h"

#include "ServiceLocator.h"
#include "GameTime.h"
#include "EnemyCharacter.h"
#include "GameScenes.h"
#include "GameObject.h"

#include "Listener.h"
#include "Event.h"

#include "WorldGridComponent.h"
#include "WorldMovementComponent.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"

// ------------
engine::BaseEnemyState::BaseEnemyState(EnemyState enemyState)
	:_enemyState{enemyState}
{
}

// ------------
engine::MovingEnemyState::MovingEnemyState()
	: BaseEnemyState{ EnemyState::Moving }
{
}

void engine::MovingEnemyState::Update()
{
	// chase down closest enemy (player) 
	auto worldComp = _pEnemy->GetWorldMovementComp();
	auto spriteComp = _pEnemy->GetSpriteComp();

	worldComp->GeneratePath(
		_pEnemy->GetScene()->GetClosestPlayerByTile(
			worldComp->GetCurrentTileIndex()));

	// modify sprite
	switch (worldComp->GetDirection())
	{
	case WorldDirection::Left:
		spriteComp->SetActiveAnimation("Left");
		break;
	case WorldDirection::Right:
		spriteComp->SetActiveAnimation("Right");
		break;
	case WorldDirection::Up:
		spriteComp->SetActiveAnimation("Up");
		break;
	case WorldDirection::Down:
		spriteComp->SetActiveAnimation("Down");
		break;
	case WorldDirection::Default:
		// just in case, have a backup
		spriteComp->SetActiveAnimation("Left");
		break;
	}
}

// ------------
engine::DyingToGoldBagEnemyState::DyingToGoldBagEnemyState()
	: BaseEnemyState{ EnemyState::DyingToGoldBag }
{
}

void engine::DyingToGoldBagEnemyState::Update()
{
	auto goldBag = _pEnemy->GetGoldBag();

	// goldbag destroyed meaning hit the ground meaning enemy dead
	if (goldBag.expired())
	{
		_pEnemy->DestroyGameObject();
	}
	// goldbag still falling meaning enemy falling too
	else
	{
		Float2 tempPos = goldBag.lock()->GetTransform()->GetPosition();
		tempPos._y += 5;

		// falling
		_pEnemy->GetTransform()->SetPosition(tempPos);
	}
}

// ------------
engine::DyingToBombEnemyState::DyingToBombEnemyState(std::shared_ptr<Event> event)
	:BaseEnemyState{EnemyState::DyingToBomb}
{
	m_spListener = std::make_shared<engine::Listener>();
	m_spListener->SetNotifyFunction([this]() {this->DeadCheck(); });
	
	event->AddListener(m_spListener);
}

void engine::DyingToBombEnemyState::Update()
{
}

void engine::DyingToBombEnemyState::DeadCheck()
{
	// sprite dead
	// stop collision

	_pEnemy->SetState(std::make_shared<DyingEnemyState>());
}

// ------------
engine::DyingEnemyState::DyingEnemyState()
	: BaseEnemyState{ EnemyState::Dying }
{
}

void engine::DyingEnemyState::Update()
{
	_deltaT += ServiceLocator::GetGameTime()->GetInstance().GetDeltaTime();

	// i-frames and death timer
	if (_deltaT >= _maxDeltaT)
	{
		_pEnemy->DestroyGameObject();
	}
}