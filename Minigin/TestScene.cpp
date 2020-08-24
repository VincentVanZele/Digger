#include "pch.h"
#include "TestScene.h"

#include "ServiceLocator.h"

#include "Scene.h"
#include "Renderer.h"
#include "GameTime.h"
#include "GameObject.h"

#include "SceneManager.h"
#include "ResourceManager.h"
#include "InputManager.h"

#include "TextComponent.h"
#include "SpriteComponent.h"
#include "TextComponent.h"

engine::TestScene::TestScene()
	:Scene("TestScene")
	, m_pSprite(nullptr), m_pText(nullptr), m_pTexture(nullptr)
{
	Initialize();
}

void engine::TestScene::Initialize()
{
	if (GetInitialized())
	{
		return;
	}

	// Input
	InputManager::GetInstance().AddInput("left", 'a');
	InputManager::GetInstance().AddInput("right", 'd');
	InputManager::GetInstance().AddInput("up", 'w');
	InputManager::GetInstance().AddInput("down", 's');

	// Texture Object
	auto spriteComponent = std::make_shared<TextureComponent>();
	auto background = ServiceLocator::GetResourceManager()->GetInstance().LoadTexture("background.jpg");
	spriteComponent->SetTexture(background);

	auto go = std::make_shared<GameObject>();
	go->AddComponent(spriteComponent);
	Add(go);

	// Text object
	std::shared_ptr<Font> font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textComp = std::make_shared<TextComponent>("Text Component Test ", font);
	textComp->Texture();

	auto goText = std::make_shared<GameObject>();
	goText->AddComponent(textComp);
	goText->GetTransform()->SetPosition({ 80, 20 });
	Add(goText);

	

	// Sprite Object
	auto tex = ResourceManager::GetInstance().LoadTexture("Sprites/Bobby/Run.png");
	auto sequence = std::make_shared<Animation>(tex, "run", 4);

	sequence->SetPos(m_SpriteObject->GetTransform()->GetPosition());
	sequence->SetFrameDeltatime(0.2f);
	spritecomp->AddAnimation(sequence);
	spritecomp->SetActiveAnimation("run");
	m_SpriteObject->AddComponent(spritecomp);
	Add(m_SpriteObject);

	Renderer::GetInstance().SetScale(1);

	SetInitialized(true);
}

void engine::TestScene::Update()
{
	auto deltaT = GameTime::GetInstance().GetDeltaTime();

	// Object update
	if (InputManager::GetInstance().IsPressed("left"))
	{
		m_SpriteObject->GetTransform()->Translate(Float2(-deltaT*75, 0));
		spritecomp->GetActiveAnimation().SetPos(m_SpriteObject->GetTransform()->GetPosition());
	}
	if (InputManager::GetInstance().IsPressed("right"))
	{
		m_SpriteObject->GetTransform()->Translate(Float2(deltaT * 75, 0));
		spritecomp->GetActiveAnimation().SetPos(m_SpriteObject->GetTransform()->GetPosition());

	}
	if (InputManager::GetInstance().IsPressed("up"))
	{
		m_SpriteObject->GetTransform()->Translate(Float2(0, -deltaT * 75));
		spritecomp->GetActiveAnimation().SetPos(m_SpriteObject->GetTransform()->GetPosition());

	}
	if (InputManager::GetInstance().IsPressed("down"))
	{
		m_SpriteObject->GetTransform()->Translate(Float2(0, deltaT * 75));
		spritecomp->GetActiveAnimation().SetPos(m_SpriteObject->GetTransform()->GetPosition());

	}

	// scene root update
	Scene::Update();
}
