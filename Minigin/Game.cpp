#include "pch.h"
#include "Game.h"

#include "Minigin.h"
#include "SceneManager.h"

#include "TestScene.h"
#include "GameScenes.h"
#include "TitleScreenScene.h"

void engine::Game::Run()
{
	engine::Minigin engine{};
	engine.Initialize();

	LoadScenes();

	engine.Run();
}

void engine::Game::LoadScenes()
{
	std::shared_ptr<Scene> scene = std::make_shared<TitleScreenScene>();

	SceneManager::GetInstance().AddScene(scene);
	SceneManager::GetInstance().SetActiveScene(scene->GetName());
}

void engine::Game::SwitchScene()
{
	std::shared_ptr<Scene> scene = std::make_shared<GameScenes>();

	SceneManager::GetInstance().AddScene(scene);
	SceneManager::GetInstance().SetActiveScene(scene->GetName());
}
