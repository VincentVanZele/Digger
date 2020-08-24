#include "pch.h"
#include "GameScenes.h"

#include "Structs.h"
#include "GameObject.h"

#include "WorldGrid.h"
#include "WorldGridComponent.h"
#include "TextComponent.h"

#include "ServiceLocator.h"
#include "Renderer.h"
#include "ResourceManager.h"

engine::GameScenes::GameScenes(GameMode mode)
	: Scene("GameScene")
	, m_GameMode{mode}
	, m_player1Score{100}, m_player2Score{25}
{
	Initialize();
}

void engine::GameScenes::Initialize()
{
	if (m_IsInitialized)
	{
		return;
	}

	SetUpWorld();

	// score
	auto windowWidth = ServiceLocator::GetWindowInfo()->GetWindowWidth();


	auto go = std::make_shared<GameObject>();

	std::shared_ptr<Font> font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 30);
	m_spScoreText = std::make_shared<TextComponent>("score", font);
	
	go->AddComponent(m_spScoreText);
	m_spScoreText->Texture();
	go->GetTransform()->SetPosition(Float2{ windowWidth/2.5f, 5 });
	Add(go);

	// lives
	m_spLife = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("Digger/life.png");
	m_spLife2 = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("Digger/life2.png");
}

void engine::GameScenes::Update()
{
	m_spScoreText->SetText(std::to_string(m_player1Score + m_player2Score));
	m_spScoreText->Texture();

	Scene::Update();
}

void engine::GameScenes::Draw() const
{
	// left lives
	auto windowWidth = ServiceLocator::GetWindowInfo()->GetWindowWidth();

	float spaceBtwLives{ 35.0f },
		spacePlayerHeight{ 5.0f },
		player1LivesPos{ 20.0f / m_Scale }, playe2LivesPos{ (windowWidth - spaceBtwLives) },
		temp{ player1LivesPos };

	for (int i{}; i < m_Player1Lives; ++i)
	{
		ServiceLocator::GetRenderer()->GetInstance().RenderTexture(*m_spLife, temp, spacePlayerHeight);
		temp += spaceBtwLives;
	}

	temp = playe2LivesPos;
	for (int i{}; i < m_Player2Lives; ++i)
	{
		ServiceLocator::GetRenderer()->GetInstance().RenderTexture(*m_spLife2, temp, spacePlayerHeight);
		temp -= spaceBtwLives;
	}

	Scene::Draw();
}

void engine::GameScenes::SetUpWorld()
{
	// world settings 
	int rows{ 16 }, cols{ 16 },	
		sizeOfTile{ 20 }; // number of pixel x pixel

	sizeOfTile;

	// setup
	auto go = std::make_shared<GameObject>();
	m_spWorld = std::make_shared<WorldGridComponent>(rows, cols, Float2{ 10250,7700 }, Float2{ 0,50 });

	go->AddComponent(m_spWorld);
	Add(go);

	m_spWorld->SetUsingLayers(true);
	m_spWorld->SetNumberOfLayers(4);

	// player
	//go = std::make_shared<GameObject>();
	//m_spPlayer1 = std::make_shared<PlayerCharacter>()

	Renderer::GetInstance().SetScale(3);
}

void engine::GameScenes::SetGameMode(GameMode gMode)
{
	m_GameMode = gMode;
}

engine::GameMode engine::GameScenes::GetGameMode() const
{
	return m_GameMode;
}

int engine::GameScenes::GetClosestPlayerByTile(int index)
{
	index;
	if (m_GameMode == GameMode::Soloplayer)
	{
		return index;
		//return m_spPlayer1->GetCurrGridIdx();
	}
	return index;

	// case player 2
}

void engine::GameScenes::RespawnPlayer()
{
	if (m_respawnPlayer1)
	{
		return;
	}

	if (m_Player1Lives == 0)
	{
		m_player1RespawnDeltaT = m_lifeDeltaT;
		m_respawnPlayer1 = true;
	}
	else
	{
		m_Player1Lives--;
		// respawn world comp 
	}
}

void engine::GameScenes::RespawnPlayer(int player)
{
	switch (player)
	{
	case 1:
		if (m_respawnPlayer1)
		{
			return;
		}

		if (m_Player1Lives == 0)
		{
			m_player1RespawnDeltaT = m_lifeDeltaT;
			m_respawnPlayer1 = true;
		}
		else
		{
			m_Player1Lives--;
			// respawn world comp 
		}
		break;
	case 2:
		if (m_respawnPlayer2)
		{
			return;
		}

		if (m_Player2Lives == 0)
		{
			m_player2RespawnDeltaT = m_lifeDeltaT;
			m_respawnPlayer2 = true;
		}
		else
		{
			m_Player2Lives--;
			// respawn world comp 
		}
		break;
	}

}

void engine::GameScenes::AddScore(float score)
{
	m_player1Score += score;
}

void engine::GameScenes::AddScore(float score, int player)
{
	switch (player)
	{
	case 1:
		m_player1Score += score;
		break;
	case 2:
		m_player2Score += score;
		break;
	}
}
