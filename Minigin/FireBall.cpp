#include "pch.h"
#include "FireBall.h"

#include "ServiceLocator.h"
#include "ResourceManager.h"
#include "GameTime.h"

#include "GameObject.h"
#include "Texture2D.h"
#include "Event.h"
#include "Listener.h"

#include "WorldGridComponent.h"
#include "WorldMovementComponent.h"
#include "TextureComponent.h"
#include "ColliderComponent.h"

bool engine::FireBall::m_IsInitialized{ false };
std::shared_ptr<engine::Texture2D> engine::FireBall::m_spFireBallTex{};

engine::FireBall::FireBall(int playerIndex, std::shared_ptr<WorldGridComponent> spWorld, int tileIndex, Float2& offset, WorldDirection direction)
	: m_playerIndex{ playerIndex }
	, m_spWorldComp{ spWorld }
	, m_startPos{ tileIndex }
	, m_startOffset{ offset }
	, m_Direction{ direction }
{
}

void engine::FireBall::Initialize()
{
	// components
	m_spMovementComp = std::make_shared<WorldMovementComponent>(m_spWorldComp, m_startPos, m_Speed, false, 0.0f, true);
	m_spColliderComp = std::make_shared<ColliderComponent>("fireBall");
	
	AddComponent(m_spMovementComp);
	AddComponent(m_spColliderComp);

	// collision
	std::vector<std::string> collisionTags{ "player", "enemy", "goldBag", "wall" };
	for (auto targets : collisionTags)
	{
		m_spColliderComp->AddTarget(targets);  // add collision targets for upadte purposes
	}

	// event
	m_spHitOther = std::make_shared<Event>();
	m_spHitWorld = std::make_shared<Event>();

	auto listener = std::make_shared<Listener>();
	listener->SetNotifyFunction([this]() {this->UpdateCollision(); });
	m_spColliderComp->GetEvent().AddListener(listener);

	// texture
	auto texture = std::make_shared<TextureComponent>();
	texture->SetTexture(m_spFireBallTex);

	// game object
	m_spFireBallObject = std::make_shared<GameObject>();
	m_spFireBallObject->AddComponent(texture);

	AddChild(m_spFireBallObject);
}

void engine::FireBall::InitializeTexture()
{
	// should be sprite !
	m_spFireBallTex = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("Digger/Fire1.png");
	m_IsInitialized = true;
}

void engine::FireBall::Update()
{
	auto go = m_spFireBallObject->GetTransform()->GetObjectPosition();
	m_spColliderComp->SetCollisionRect(Float4(go._x, go._y, 10, 10));
	
	if (m_spMovementComp->GenerateDirection(m_Direction) == TileMovement::Closed)
	{
		m_spHitWorld->CallNotify();
		Destroy();
	}
}

void engine::FireBall::UpdateCollision()
{
	m_spHitWorld->CallNotify();
	Destroy();
}

void engine::FireBall::SetFireBallGameObject(std::shared_ptr<GameObject> go)
{
	m_spFireBallObject = go;
}

std::shared_ptr<engine::GameObject> engine::FireBall::GetFireBallGameObject() const
{
	return m_spFireBallObject;
}

void engine::FireBall::SetWorldComponent(std::shared_ptr<WorldGridComponent> comp)
{
	m_spWorldComp = comp;
}

std::shared_ptr<engine::WorldGridComponent> engine::FireBall::GetWorldComponent() const
{
	return m_spWorldComp;
}

void engine::FireBall::SetMovementComponent(std::shared_ptr<WorldMovementComponent> comp)
{
	m_spMovementComp = comp;
}

std::shared_ptr<engine::WorldMovementComponent> engine::FireBall::GetMovementComponent() const
{
	return m_spMovementComp;
}

void engine::FireBall::SetColliderComponent(std::shared_ptr<ColliderComponent> comp)
{
	m_spColliderComp = comp;
}

std::shared_ptr<engine::ColliderComponent> engine::FireBall::GetColliderComponent() const
{
	return m_spColliderComp;
}

void engine::FireBall::SetSpeed(float speed)
{
	m_Speed = speed;
}

float engine::FireBall::GetSpeed() const
{
	return m_Speed;
}
