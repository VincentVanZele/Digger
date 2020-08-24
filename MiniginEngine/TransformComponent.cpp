#include "MiniginPCH.h"
#include "TransformComponent.h"
#include "Structs.h"
#include "GameObject.h"

engine::TransformComponent::TransformComponent()
	: BaseComponent()
	, m_pChild(nullptr)
	
{
}

void engine::TransformComponent::SetChildObject(GameObject* pGO)
{
	m_pChild = pGO;
}

void engine::TransformComponent::SetPosition(Float2 pos)
{
	m_Position = pos;
}

engine::Float2 engine::TransformComponent::GetPosition() const
{
	return m_Position;
}

void engine::TransformComponent::SetObjectPosition(Float2 pos)
{
	Translate(Float2(pos._x - GetObjectPosition()._x, pos._y - GetObjectPosition()._y));
}

engine::Float2 engine::TransformComponent::GetObjectPosition() const
{
	Float2 temp{};
	GameObject* tempObj{ m_pChild };

	while (tempObj)
	{
		temp._x += tempObj->GetTransform()->GetPosition()._x;
		temp._y += tempObj->GetTransform()->GetPosition()._y;

		tempObj = tempObj->GetParent();
	}

	return temp;
}

void engine::TransformComponent::SetRotation(float rot)
{
	m_Rotation = rot;
}

float engine::TransformComponent::GetRotation() const
{
	return m_Rotation;
}

void engine::TransformComponent::SetObjectRotation(float rot)
{
	Rotate( rot - m_Rotation );
}

float engine::TransformComponent::GetObjectRotation() const
{
	float temp{};
	GameObject* tempObj{ m_pChild };

	while (tempObj)
	{
		temp += tempObj->GetTransform()->GetRotation();

		tempObj = tempObj->GetParent();
	}

	return temp;
}

void engine::TransformComponent::SetScale(Float2 sca)
{
	m_Scale = sca;
}

engine::Float2 engine::TransformComponent::GetScale() const
{
	return m_Scale;
}

void engine::TransformComponent::SetObjectScale(Float2 sca)
{
	Scale(Float2(sca._x - m_Scale._x, sca._y - m_Scale._y));
}

engine::Float2 engine::TransformComponent::GetObjectScale() const
{
	Float2 temp{};
	GameObject* tempObj{ m_pChild };

	while (tempObj)
	{
		temp._x *= tempObj->GetTransform()->GetScale()._x;
		temp._y *= tempObj->GetTransform()->GetScale()._y;

		tempObj = tempObj->GetParent();
	}

	return temp;
}

void engine::TransformComponent::Translate(const Float2& pos)
{
	m_Position._x += pos._x;
	m_Position._y += pos._y;
}

void engine::TransformComponent::Rotate(float rot)
{
	m_Rotation += rot;
}

void engine::TransformComponent::Scale(const Float2& sca)
{
	m_Scale._x += sca._x;
	m_Scale._y += sca._y;
}