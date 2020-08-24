#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int engine::Scene::idCounter = 0;

engine::Scene::Scene(const std::string& name) 
	: mName(name) 
	, m_IsInitialized(false)
{
}

void engine::Scene::Add(const std::shared_ptr<GameObject>& object)
{
	mObjects.push_back(object);
	
}

void engine::Scene::SetName(std::string& name)
{
	mName = name;
}

std::string engine::Scene::GetName() const
{
	return mName;
}

void engine::Scene::SetInitialized(bool init)
{
	m_IsInitialized = init;
}

bool engine::Scene::GetInitialized() const
{
	return m_IsInitialized;
}

void engine::Scene::Update()
{
	for(auto gameObject : mObjects)
	{
		gameObject->Update();
	}
}

void engine::Scene::Draw() const
{
	for (const auto gameObject : mObjects)
	{
		gameObject->Draw();
	}
}

