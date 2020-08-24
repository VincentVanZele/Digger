#include "pch.h"
#include "GoldBag.h"
#include "GoldBagState.h"

#include "ServiceLocator.h"
#include "GameTime.h"
#include "GameObject.h"
#include "GameScenes.h"
// char

#include "ColliderComponent.h"
#include "SpriteComponent.h"
#include "WorldGridComponent.h"
#include "WorldMovementComponent.h"

#include "ResourceManager.h"
#include "CollisionManager.h"


engine::GoldBag::GoldBag(std::shared_ptr<WorldGridComponent> spWorld, GameScenes* pScene, int tileIdx)
	: BaseComponent()
	, m_Index{ tileIdx }
	, m_spWorldComp{spWorld}
	, m_pScene{ pScene }
{
}

void engine::GoldBag::Initialize()
{
	if (m_IsInitialized)
	{
		return;
	}

	// make it an obstacle 
	m_spObstacleComp = std::make_shared<WorldObstacleComponent>(m_spWorldComp, m_Index);
	AddComponent(m_spObstacleComp);
	
}

void engine::GoldBag::Update()
{
	auto pos = GetTransform()->GetObjectPosition();
	m_spColliderComp->SetCollisionRect(Float4(pos._x, pos._y, 20, 20));
	m_CurrState->Update();
}

void engine::GoldBag::Destroy()
{
	// score
}

int engine::GoldBag::GetIndex() const
{
	return m_Index;
}

engine::GameScenes* engine::GoldBag::GetScene() const
{
	return m_pScene;
}

std::shared_ptr<engine::GoldBagState> engine::GoldBag::GetGoldBagState() const
{
	return m_CurrState;
}

void engine::GoldBag::SetState(std::shared_ptr<GoldBagState> state)
{
	m_CurrState = state;
}

void engine::GoldBag::SetColliderComp(std::shared_ptr<ColliderComponent> sp)
{
	m_spColliderComp = sp;
}

void engine::GoldBag::SetSpriteComp(std::shared_ptr<SpriteComponent> sp)
{
	m_spSpriteComp = sp;
}

void engine::GoldBag::SetWorldGridComp(std::shared_ptr<WorldGridComponent> sp)
{
	m_spWorldComp = sp;
}

void engine::GoldBag::SetWorldMovementComp(std::shared_ptr<WorldMovementComponent> sp)
{
	m_spMovementComp = sp;
}

void engine::GoldBag::SetWorldObstacleComp(std::shared_ptr<WorldObstacleComponent> sp)
{
	m_spObstacleComp = sp;
}

std::shared_ptr<engine::ColliderComponent> engine::GoldBag::GetColliderComp() const
{
	return m_spColliderComp;
}

std::shared_ptr<engine::SpriteComponent> engine::GoldBag::GetSpriteComp() const
{
	return m_spSpriteComp;
}

std::shared_ptr<engine::WorldGridComponent> engine::GoldBag::GetWorldGridComp() const
{
	return m_spWorldComp;
}

std::shared_ptr<engine::WorldMovementComponent> engine::GoldBag::GetWorldMovementComp() const
{
	return m_spMovementComp;
}

std::shared_ptr<engine::WorldObstacleComponent> engine::GoldBag::GetWorldObstacleComp() const
{
	return m_spObstacleComp;
}
