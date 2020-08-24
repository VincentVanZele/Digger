#include "pch.h"
#include "PlayerCharacter.h"

#include "ServiceLocator.h"
#include "Listener.h"
#include "GameScenes.h"
#include "GameTime.h"
#include "Animation.h"

#include "ResourceManager.h"
#include "InputManager.h"

#include "SpriteComponent.h"
#include "ColliderComponent.h"

engine::PlayerCharacter::PlayerCharacter(std::shared_ptr<WorldGridComponent> spWorld, GameScenes* scene, int startTileIndex, int index)
	: BaseComponent()
	, m_spWorldComp{ spWorld }
	, m_pGameScene{ scene }
	, m_startTile{ startTileIndex }
	, m_playerIndex{ index }
	//
	, m_speed{ 50.f }
	, m_DieDeltaT{ 0.0f }
	, m_MaxDieDeltaT{ 1.2f }
{
}

void engine::PlayerCharacter::Initialize()
{
	if (m_IsInitialized)
	{
		return;
	}

	SetupSprite();

	// Listener [...
	auto listener = std::make_shared<Listener>();

	listener->SetNotifyFunction([this]() {this->UpdateCollision(); });

	// Movement
	m_spMovementComp = std::make_shared<WorldMovementComponent>(m_spWorldComp, m_startTile, 60.0f, true, 40.f);
	AddComponent(m_spMovementComp);

	m_spColliderComp = std::make_shared<ColliderComponent>("Player");
	m_spColliderComp->AddTarget("GoldBag");
	m_spColliderComp->AddTarget("Enemy");

	m_spColliderComp->m_HasCollided.AddListener(listener);
	AddComponent(m_spColliderComp);
}

void engine::PlayerCharacter::SetupSprite()
{
	// Left
	m_spSpriteComp = std::make_shared<SpriteComponent>();
	auto tex = ServiceLocator::GetResourceManager()->LoadTexture("Digger/player1WalkLeft.png");
	auto sequence = std::make_shared<Animation>(tex, "Left", 2);
	m_spSpriteComp->AddAnimation(sequence);

	// Right
	tex = ServiceLocator::GetResourceManager()->LoadTexture("Digger/player1WalkRight.png");
	sequence = std::make_shared<Animation>(tex, "Right", 2);
	m_spSpriteComp->AddAnimation(sequence);

	// Up
	tex = ServiceLocator::GetResourceManager()->LoadTexture("Digger/player1WalkUp.png");
	sequence = std::make_shared<Animation>(tex, "Up", 2);
	m_spSpriteComp->AddAnimation(sequence);

	// Down
	tex = ServiceLocator::GetResourceManager()->LoadTexture("Digger/player1WalkDown.png");
	sequence = std::make_shared<Animation>(tex, "Down", 2);
	m_spSpriteComp->AddAnimation(sequence);

	// Death
	tex = ServiceLocator::GetResourceManager()->LoadTexture("Digger/player1Die.png");
	sequence = std::make_shared<Animation>(tex, "Death", 4);
	m_spSpriteComp->AddAnimation(sequence);

	m_spSpriteComp->SetActiveAnimation("Right");

	m_spGameObject = std::make_shared<GameObject>();
	m_spGameObject->AddComponent(m_spSpriteComp);
	AddChild(m_spGameObject);

	m_spGameObject->GetTransform()->Translate(Float2{ 50, 50 });
}

void engine::PlayerCharacter::UpdateCollision()
{
	// safety check
	if (!m_Died)
	{
		switch (TagToState(m_spColliderComp->GetCollidedTag()))
		{
		case ColliderTag::FireBall:
			m_spSpriteComp->SetActiveAnimation("Death");
			m_spSpriteComp->SetFrame(0);
			m_Died = true;
			break;
		}
	}
}

engine::ColliderTag engine::PlayerCharacter::TagToState(std::string string)
{
	if (string == "fire") return ColliderTag::FireBall;
	else if (string == "goldBag") return ColliderTag::GoldBags;
	else return ColliderTag::Default;
}

void engine::PlayerCharacter::Update()
{
	// update behavior
	if (!m_Shooting)
	{
		HandleMovement();
		HandleShooting();
	}
	else if (m_Died) // update dying
	{
		m_DieDeltaT += ServiceLocator::GetGameTime()->GetDeltaTime();

		if (m_DieDeltaT >= m_MaxDieDeltaT)
		{
			m_pGameScene->RespawnPlayer();
			m_DieDeltaT = 0.0f;
		}
	}

	// update collision
	Float2 pos = GetTransform()->GetObjectPosition();
	m_spColliderComp->SetCollisionRect(Float4(pos._x, pos._y, 14, 14));
}

void engine::PlayerCharacter::HandleMovement()
{
	// setup [...
	WorldDirection direction = WorldDirection::Default;
	Float2 input{};
	// ...]

	input = GetMovementFromKeyboard();
	
	// input check
	auto inputCheck = abs(input._x) + abs(input._y);

	if (inputCheck > 0.001f) // is there any input 
	{						// important for controller 
		if (input._x > 0.001f)
		{
			m_Animation = "Right";
			direction = WorldDirection::Right;
		}
		else if (input._x < -0.001f)
		{
			m_Animation = "Left";
			direction = WorldDirection::Left;
		}
		else if (input._y > 0.001f)
		{
			m_Animation = "Down";
			direction = WorldDirection::Down;
		}
		else if (input._y < 0.001f)
		{
			m_Animation = "Down";
			direction = WorldDirection::Down;
		}
		else // default
		{
			m_Animation = "Left";
			direction = WorldDirection::Left;
		}
	}

	// modify sprite
	auto currentDirection = m_spMovementComp->GetDirection();

	switch (m_spMovementComp->GenerateDirection(currentDirection))
	{
	case TileMovement::Open:
		if (currentDirection == direction)
		{
			m_spSpriteComp->SetActiveAnimation(m_Animation);
		}
		break;
	case TileMovement::Closed:
		m_spSpriteComp->SetActiveAnimation(m_Animation);
		break;
	}

	// reset direction
	if (direction != WorldDirection::Default)
	{
		m_Direction = direction;
	}
}

engine::Float2 engine::PlayerCharacter::GetMovementFromKeyboard()
{
	// setup
	auto input = ServiceLocator::GetInputManager();
	Float2 axis{};

	axis._x = input->GetAxis("HorizontalMovement");
	axis._y = input->GetAxis("VerticalMovement");

	return axis;
}

engine::Float2 engine::PlayerCharacter::GetMovementFromController()
{
	auto input = ServiceLocator::GetInputManager();
	Float2 result{};

	if (input->IsButton(m_playerIndex, ControllerButton::DPRight))
	{
		result._x += 1.0f;
	}
	if (input->IsButton(m_playerIndex, ControllerButton::DPLeft))
	{
		result._x -= 1.0f;
	}
	if (input->IsButton(m_playerIndex, ControllerButton::DPUp))
	{
		result._y -= 1.0f;
	}
	if (input->IsButton(m_playerIndex, ControllerButton::DPDown))
	{
		result._y += 1.0f;
	}

	return result;
}

void engine::PlayerCharacter::HandleShooting()
{
}

void engine::PlayerCharacter::FireBallHit()
{
}

void engine::PlayerCharacter::FireBallMiss()
{
}

void engine::PlayerCharacter::Respawn(int tileIndex)
{
	m_Died = false;
	m_spMovementComp->Respawn(tileIndex);
	m_Animation = "Right";
	m_spSpriteComp->SetActiveAnimation(m_Animation);

}

int engine::PlayerCharacter::GetCurrPosByTile() const
{
	return 0;
}

int engine::PlayerCharacter::GetPlayerIndex() const
{
	return 0;
}
