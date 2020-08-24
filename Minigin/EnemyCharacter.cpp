#include "pch.h"
#include "EnemyCharacter.h"

#include "WorldGridComponent.h"
#include "WorldMovementComponent.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"

#include "ResourceManager.h"
#include "Animation.h"
#include "EnemyState.h"

#include "ServiceLocator.h"
#include "GameScenes.h"
#include "GameObject.h"
#include "Event.h"

engine::EnemyCharacter::EnemyCharacter(GameScenes* pScene, std::shared_ptr<WorldGridComponent> spWorld, int tileIndex)
	:BaseComponent()
	, m_pScene{pScene}
	, m_spWorldComp{spWorld}
	, m_currTileIndex{tileIndex}
{
	// event HasDied
	m_spDied = std::make_shared<Event>();
}

void engine::EnemyCharacter::Initialize()
{
	if (m_IsInitialized)
	{
		return;
	}
	
	// sprite
	InitializeSprite();
	
	GetTransform()->SetPosition(m_spWorldComp->GetPositionFromTile(m_currTileIndex));

	// collider
}

void engine::EnemyCharacter::Update()
{
	m_spState->Update();

}

void engine::EnemyCharacter::Die()
{
	if (m_spState->_enemyState == EnemyState::Dying)
	{
		m_spDied->CallNotify();
	}
	else
	{
		EnemyDie();
	}
}

void engine::EnemyCharacter::InitializeSprite()
{
	float frameDeltaT = 0.2f;

	// sprite
	m_spSpriteComp = std::make_shared<SpriteComponent>();

	auto go = std::make_shared<GameObject>();
	go->AddComponent(m_spSpriteComp);

	AddChild(go);
	go->GetTransform()->SetPosition(Float2{ 5, 5 });

	// LEFT
	auto texture = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("Digger/enemy1Walk.png");
	auto animation = std::make_shared<Animation>(texture, "walk", 2);

	animation->SetFrameDeltatime(frameDeltaT);
	m_spSpriteComp->AddAnimation(animation);

	texture = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("Digger/enemy1Hit.png");
	animation = std::make_shared<Animation>(texture, "hit", 2);

	animation->SetFrameDeltatime(frameDeltaT);
	m_spSpriteComp->AddAnimation(animation);

	// ETC...

	m_spSpriteComp->SetActiveAnimation("walk");
}

void engine::EnemyCharacter::UpdateCollision()
{
	bool dying = m_spState->_enemyState == EnemyState::Dying || m_spState->_enemyState == EnemyState::Dying;

	if (!(dying))
	{
		switch (TagToState(m_spColliderComp->GetCollidedTag()))
		{
		case ColliderTag::GoldBags:
			m_spSpriteComp->SetActiveAnimation("hit");
			m_wpGoldBag = GetColliderComp()->GetGameObject();
			m_Direction = WorldDirection::Default;
			
			SetState(std::make_shared<DyingToGoldBagEnemyState>());
			m_spListener->StopListening();
			// Die();
			break;

		case ColliderTag::FireBall:
			// Die();
			break;
		}
	}
}

engine::ColliderTag engine::EnemyCharacter::TagToState(std::string string)
{
	if (string == "fire") return ColliderTag::FireBall;
	else if (string == "goldBag") return ColliderTag::GoldBags;
	else return ColliderTag::Default;
}

void engine::EnemyCharacter::SetScene(GameScenes* scene)
{
	m_pScene = scene;
}

void engine::EnemyCharacter::SetDirection(WorldDirection dir)
{
	m_Direction = dir;
}

void engine::EnemyCharacter::SetColliderComp(std::shared_ptr<ColliderComponent> sp)
{
	m_spColliderComp = sp;
}

void engine::EnemyCharacter::SetSpriteComp(std::shared_ptr<SpriteComponent> sp)
{
	m_spSpriteComp = sp;
}

void engine::EnemyCharacter::SetWorldGridComp(std::shared_ptr<WorldGridComponent> sp)
{
	m_spWorldComp = sp;
}

void engine::EnemyCharacter::SetWorldMovementComp(std::shared_ptr<WorldMovementComponent> sp)
{
	m_spMovementComp = sp;
}

void engine::EnemyCharacter::SetListener(std::shared_ptr<Listener> sp)
{
	m_spListener = sp;
}

void engine::EnemyCharacter::SetState(std::shared_ptr<BaseEnemyState> state)
{
	m_spState = state;
}

engine::GameScenes* engine::EnemyCharacter::GetScene() const
{
	return m_pScene;
}

engine::WorldDirection engine::EnemyCharacter::GetDirection() const
{
	return m_Direction;
}

std::weak_ptr<engine::GameObject> engine::EnemyCharacter::GetGoldBag() const
{
	return m_wpGoldBag;
}

std::shared_ptr<engine::ColliderComponent> engine::EnemyCharacter::GetColliderComp() const
{
	return m_spColliderComp;
}

std::shared_ptr<engine::SpriteComponent> engine::EnemyCharacter::GetSpriteComp() const
{
	return m_spSpriteComp;
}

std::shared_ptr<engine::WorldGridComponent> engine::EnemyCharacter::GetWorldGridComp() const
{
	return m_spWorldComp;
}

std::shared_ptr<engine::WorldMovementComponent> engine::EnemyCharacter::GetWorldMovementComp() const
{
	return m_spMovementComp;
}

std::shared_ptr<engine::Listener> engine::EnemyCharacter::GetListener() const
{
	return m_spListener;
}

std::shared_ptr<engine::Event> engine::EnemyCharacter::GetEvent() const
{
	return m_spDied;
}

std::shared_ptr<engine::BaseEnemyState> engine::EnemyCharacter::GetState() const
{
	return m_spState;
}
