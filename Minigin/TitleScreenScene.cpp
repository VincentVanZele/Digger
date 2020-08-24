#include "pch.h"
#include "Game.h"

#include "TitleScreenScene.h"
#include "GameScenes.h"
#include "Scene.h"
#include "GameObject.h"

#include "ServiceLocator.h"
#include "GameTime.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "Event.h"
#include "Listener.h"
#include "Animation.h"

#include "TextureComponent.h"
#include "ButtonComponent.h"
#include "SpriteComponent.h"

engine::TitleScreenScene::TitleScreenScene()
	:Scene("TitleScreenScene")
	, m_selectedButton{Button::ButtonSolo}
	, m_spFire2{ std::make_shared<GameObject>() }
	, m_spFire2Comp{ std::make_shared<SpriteComponent>() }
	, m_sign{ 0.1f }
	, m_soloPos{ Float2{ 180.0f, 245.0f } }, m_coopPos{ Float2{ 180.0f, 300.0f } },m_exitPos{ Float2{ 180.0f, 360.0f } }
	, m_firePos1{ Float2{ 580.0f, 175.0f } }, m_firePos2{ Float2{ 40.0f, 50.0f } }, m_firePos3{ Float2{ 500.0f, 45.0f } }, m_firePos4{ Float2{ 500.0f, 400.0f } }, m_firePos5{ Float2{ 30.0f, 175.0f } }
	, m_letterD{ Float2{ 200.0f, 125.0f } }, m_letterI{ Float2{ 240.0f, 125.0f } }, m_letterG1{ Float2{ 280.0f, 125.0f } }, m_letterG2{ Float2{ 320.0f, 125.0f } }, m_letterE{ Float2{ 360.0f, 125.0f } }, m_letterR{ Float2{ 400.0f, 125.0f } }
{
	Initialize();
}

void engine::TitleScreenScene::Initialize()
{
	if (GetInitialized())
	{
		return;
	}

	// Input
	ServiceLocator::GetInputManager()->GetInstance().AddInput("enter", 1073741912);
	ServiceLocator::GetInputManager()->GetInstance().AddInput("up", 1073741906);
	ServiceLocator::GetInputManager()->GetInstance().AddInput("down", 1073741905);

	// background
	auto resourceManager = ServiceLocator::GetResourceManager();

	auto go = std::make_shared<GameObject>();
	auto tex = resourceManager->GetInstance().LoadTexture("menu.jpg");
	auto texComp = std::make_shared<TextureComponent>();
	texComp->SetTexture(tex);
	go->AddComponent(texComp);
	Add(go);
	
	SetupButton();

	SetupSprites();
	
	SetupLettres();

	ServiceLocator::GetRenderer()->GetInstance().SetScale(1);
}

void engine::TitleScreenScene::Update()
{
	UpdateInput();

	// Selection position
	m_spFire2Comp->GetActiveAnimation().SetPos(m_spFire2->GetTransform()->GetPosition());

	// Letters position
	for (size_t i{ 0 }; i < m_vspLetters.size(); ++i)
	{
		auto trans = m_vspLetters[i]->GetTransform();
		auto pos = trans->GetPosition();

		if (pos._y < 100.0f)
		{
			pos._y = 101.0f;
			m_sign *= -1;
		}
		else if (pos._y > 130.0f)
		{
			pos._y = 129.0f;
			m_sign *= -1;
		}

		auto temp = Float2{ pos._x, pos._y + m_sign };
		trans->SetPosition(temp);
	}

	Scene::Update();
}

void engine::TitleScreenScene::ButtonClicked(Button button)
{
	auto& sceneManager = ServiceLocator::GetSceneManager()->GetInstance();

	switch (button)
	{
	case Button::ButtonSolo:
		engine::Game::SwitchScene();
		sceneManager.SetActiveScene("GameScenes");
		break;
	case Button::ButtonMultiplayer:
		sceneManager.AddScene(std::make_shared<GameScenes>(GameMode::Multiplayer));
		sceneManager.SetActiveScene("GameScenes");
		break;
	case Button::ButtonExit:
		// no game
		break;
	}
}

void engine::TitleScreenScene::UpdateInput()
{
	if (InputManager::GetInstance().IsUp("up"))
	{
		switch (m_selectedButton)
		{
		case Button::ButtonSolo:
			m_selectedButton = Button::ButtonExit;
			m_spFire2->GetTransform()->SetPosition(m_exitPos);
			break;
		case Button::ButtonMultiplayer:
			m_selectedButton = Button::ButtonSolo;
			m_spFire2->GetTransform()->SetPosition(m_soloPos);
			break;
		case Button::ButtonExit:
			m_selectedButton = Button::ButtonMultiplayer;
			m_spFire2->GetTransform()->SetPosition(m_coopPos);
			break;
		default:
			break;
		}
	}
	if (InputManager::GetInstance().IsUp("down"))
	{
		switch (m_selectedButton)
		{
		case Button::ButtonSolo:
			m_selectedButton = Button::ButtonMultiplayer;
			m_spFire2->GetTransform()->SetPosition(m_coopPos);
			break;
		case Button::ButtonMultiplayer:
			m_selectedButton = Button::ButtonExit;
			m_spFire2->GetTransform()->SetPosition(m_exitPos);
			break;
		case Button::ButtonExit:
			m_selectedButton = Button::ButtonSolo;
			m_spFire2->GetTransform()->SetPosition(m_soloPos);
			break;
		default:
			break;
		}
	}
	if (InputManager::GetInstance().IsUp("enter"))
	{

		switch (m_selectedButton)
		{
		case Button::ButtonSolo:
			ButtonClicked(Button::ButtonSolo);
			break;
		case Button::ButtonMultiplayer:
			ButtonClicked(Button::ButtonMultiplayer);
			break;
		case Button::ButtonExit:
			ButtonClicked(Button::ButtonExit);
			break;
		default:
			break;
		}
	}
}

void engine::TitleScreenScene::SetupLettres()
{
	auto resourceManager = ServiceLocator::GetResourceManager();

	auto go = std::make_shared<GameObject>();
	auto tex = resourceManager->GetInstance().LoadTexture("VLETD.png");
	auto texComp = std::make_shared<TextureComponent>();
	texComp->SetTexture(tex);

	go->GetTransform()->SetPosition(m_letterD);
	go->AddComponent(texComp);
	m_vspLetters.push_back(go);

	Add(go);

	//---

	go = std::make_shared<GameObject>();
	tex = resourceManager->GetInstance().LoadTexture("VLETI.png");
	texComp = std::make_shared<TextureComponent>();
	texComp->SetTexture(tex);

	go->GetTransform()->SetPosition(m_letterI);
	go->AddComponent(texComp);
	m_vspLetters.push_back(go);

	Add(go);

	//---

	go = std::make_shared<GameObject>();
	tex = resourceManager->GetInstance().LoadTexture("VLETG.png");
	texComp = std::make_shared<TextureComponent>();
	texComp->SetTexture(tex);

	go->GetTransform()->SetPosition(m_letterG1);
	go->AddComponent(texComp);
	m_vspLetters.push_back(go);

	Add(go);

	//---

	go = std::make_shared<GameObject>();
	texComp = std::make_shared<TextureComponent>();
	texComp->SetTexture(tex);

	go->GetTransform()->SetPosition(m_letterG2);
	go->AddComponent(texComp);
	m_vspLetters.push_back(go);

	Add(go);

	//---

	go = std::make_shared<GameObject>();
	tex = resourceManager->GetInstance().LoadTexture("VLETE.png");
	texComp = std::make_shared<TextureComponent>();
	texComp->SetTexture(tex);

	go->GetTransform()->SetPosition(m_letterE);
	go->AddComponent(texComp);
	m_vspLetters.push_back(go);

	Add(go);

	//---

	go = std::make_shared<GameObject>();
	tex = resourceManager->GetInstance().LoadTexture("VLETR.png");
	texComp = std::make_shared<TextureComponent>();
	texComp->SetTexture(tex);

	go->GetTransform()->SetPosition(m_letterR);
	go->AddComponent(texComp);
	m_vspLetters.push_back(go);

	Add(go);
}

void engine::TitleScreenScene::SetupSprites()
{
	auto resourceManager = ServiceLocator::GetResourceManager();

	auto tex = resourceManager->GetInstance().LoadTexture("Digger/Fire2.png");
	auto sequence = std::make_shared<Animation>(tex, "fire2", 4);
	m_spFire2Comp = std::make_shared<SpriteComponent>();

	m_spFire2->GetTransform()->Translate(m_soloPos);

	sequence->SetPos(m_spFire2->GetTransform()->GetPosition());
	sequence->SetFrameDeltatime(0.2f);
	m_spFire2Comp->AddAnimation(sequence);
	m_spFire2Comp->SetActiveAnimation("fire2");
	m_spFire2->AddComponent(m_spFire2Comp);
	Add(m_spFire2);

	//---

	tex = resourceManager->GetInstance().LoadTexture("Digger/Fire1.png");
	sequence = std::make_shared<Animation>(tex, "fire1", 4);

	for (int i{ 0 }; i < 5; ++i)
	{
		m_vspFire.push_back(std::make_shared<GameObject>());
		m_vspFireComp.push_back(std::make_shared<SpriteComponent>());

		sequence = std::make_shared<Animation>(tex, "fire1" + std::to_string(i), 4);
		sequence->SetFrameDeltatime(0.2f);

		switch (i) // different positions for fires 
		{
		case 0:
			m_vspFire[i]->GetTransform()->Translate(m_firePos1);
			sequence->SetPos(m_vspFire[i]->GetTransform()->GetPosition());
			break;
		case 1:
			m_vspFire[i]->GetTransform()->Translate(m_firePos2);
			sequence->SetPos(m_vspFire[i]->GetTransform()->GetPosition());
			break;
		case 2:
			m_vspFire[i]->GetTransform()->Translate(m_firePos3);
			sequence->SetPos(m_vspFire[i]->GetTransform()->GetPosition());
			break;
		case 3:
			m_vspFire[i]->GetTransform()->Translate(m_firePos4);
			sequence->SetPos(m_vspFire[i]->GetTransform()->GetPosition());
			break;
		case 4:
			m_vspFire[i]->GetTransform()->Translate(m_firePos5);
			sequence->SetPos(m_vspFire[i]->GetTransform()->GetPosition());
			break;
		}

		m_vspFireComp[i]->AddAnimation(sequence);
		m_vspFireComp[i]->SetActiveAnimation("fire1" + std::to_string(i));
		m_vspFire[i]->AddComponent(m_vspFireComp[i]);
		Add(m_vspFire[i]);
	}
}

void engine::TitleScreenScene::SetupButton()
{
	auto resourceManager = ServiceLocator::GetResourceManager();
	Float2 buttonDimension{ 196.0f, 42.0f };

	auto go = std::make_shared<GameObject>();
	auto tex = resourceManager->GetInstance().LoadTexture("ButtonSolo.png");
	auto buttonComp = std::make_shared<ButtonComponent>(tex, buttonDimension._x, buttonDimension._y);
	go->AddComponent(buttonComp);
	Add(go);

	go->GetTransform()->Translate(Float2{ 210.0f, 237.0f });
	auto list = std::make_shared<Listener>();
	list->SetNotifyFunction([this]() {this->ButtonClicked(Button::ButtonSolo); });
	buttonComp->m_spClick->AddListener(list);


	go = std::make_shared<GameObject>();
	tex = resourceManager->GetInstance().LoadTexture("ButtonCoop.png");
	buttonComp = std::make_shared<ButtonComponent>(tex, buttonDimension._x, buttonDimension._y);
	go->AddComponent(buttonComp);
	Add(go);

	go->GetTransform()->Translate(Float2{ 210.0f, 295.0f });
	list = std::make_shared<Listener>();
	list->SetNotifyFunction([this]() {this->ButtonClicked(Button::ButtonMultiplayer); });
	buttonComp->GetEvent()->AddListener(list);

	go = std::make_shared<GameObject>();
	tex = resourceManager->GetInstance().LoadTexture("ButtonQuit.png");
	buttonComp = std::make_shared<ButtonComponent>(tex, buttonDimension._x, buttonDimension._y);
	go->AddComponent(buttonComp);
	Add(go);

	go->GetTransform()->Translate(Float2{ 210.0f, 353.0f });
	list = std::make_shared<Listener>();
	list->SetNotifyFunction([this]() {this->ButtonClicked(Button::ButtonExit); });
	buttonComp->GetEvent()->AddListener(list);
}
