#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void engine::SceneManager::AddScene(std::shared_ptr<Scene> scene)
{
	mScenes.push_back(scene);
}

void engine::SceneManager::Update()
{
	mActiveScene->Update();
}

void engine::SceneManager::Draw()
{
	mActiveScene->Draw();
}

std::vector<std::shared_ptr<engine::Scene>> engine::SceneManager::GetScenes() const
{
	return mScenes;
}

void engine::SceneManager::SetActiveScene(const std::string& name)
{
	for (auto scene : mScenes)
	{
		if (scene->GetName() == name)
		{
			mActiveScene = scene;
			return;
		}
	}
}
