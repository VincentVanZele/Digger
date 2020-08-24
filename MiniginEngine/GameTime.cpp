#include "MiniginPCH.h"
#include "GameTime.h"

void engine::GameTime::Update(float deltaTime)
{
	m_DeltaTime = deltaTime;
	m_ElapsedTime += m_DeltaTime;
}

float engine::GameTime::GetDeltaTime() const
{
	return m_DeltaTime;
}

float engine::GameTime::GetFPS() const
{
	return (int)1.0f / m_DeltaTime;
}
