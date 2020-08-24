#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "ResourceManager.h"

void engine::FPSComponent::Update()
{
	int deltaTime{};
	m_FPS = 1.f / deltaTime;
}

float engine::FPSComponent::GetFPS() const
{
	return m_FPS;
}
