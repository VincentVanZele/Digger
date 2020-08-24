#include "MiniginPCH.h"
#include "Transform.h"

void engine::Transform::SetPosition(const Float3& newPos)
{
	m_Position = newPos;
}

void engine::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position._x = x;
	m_Position._y = y;
	m_Position._z = z;
}

const engine::Float2& engine::Transform::GetScale() const
{
	return m_Scale;
}

void engine::Transform::SetScale(const Float2& scale)
{
	m_Scale = scale;
}

void engine::Transform::SetScale(float x, float y)
{
	m_Scale._x = x;
	m_Scale._y = y;
}
