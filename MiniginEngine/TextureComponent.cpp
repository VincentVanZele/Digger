#include "MiniginPCH.h"
#include "Structs.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "Renderer.h"

engine::TextureComponent::TextureComponent()
	: BaseComponent()
	, m_pTexture2D(nullptr)
{
}

void engine::TextureComponent::Draw()
{
	Float2 pos{ GetGameObject()->GetTransform()->GetPosition() };
	Renderer::GetInstance().RenderTexture(*m_pTexture2D, pos._x, pos._y);
}

engine::Texture2D& engine::TextureComponent::GetTexture() const
{
	return *m_pTexture2D;
}

void engine::TextureComponent::SetTexture(std::shared_ptr<Texture2D> pTexture)
{
	m_pTexture2D = pTexture;
}
