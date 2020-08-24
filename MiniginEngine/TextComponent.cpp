#include "MiniginPCH.h"
#include "Renderer.h"
#include "TextComponent.h"
#include "Texture2D.h"
#include <SDL_ttf.h>

engine::TextComponent::TextComponent(const std::string& txt, const std::shared_ptr<Font> font, const Float4& col)
	:TextureComponent()
	, m_Text(txt), m_pFont(font), m_Color(col)
{
}

std::string engine::TextComponent::GetText() const
{
	return m_Text;
}

void engine::TextComponent::SetText(const std::string& txt)
{
	m_Text = txt;
}

engine::Font& engine::TextComponent::GetFont() const
{
	return *m_pFont;
}

void engine::TextComponent::SetFont(const std::shared_ptr<Font>& font)
{
	m_pFont = font;
}

engine::Float4 engine::TextComponent::GetColor() const
{
	return m_Color;
}

void engine::TextComponent::SetColor(const Float4& col)
{
	m_Color = col;
}

void engine::TextComponent::Texture()
{
	SDL_Color col = {
		Uint8(m_Color._x * 255.0f),
		Uint8(m_Color._y * 255.0f),
		Uint8(m_Color._z * 255.0f)
	};

	// Surface Render
	auto render = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), col);
	if (!render)
	{throw SDL_GetError();}
	
	// Texture creation
	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), render);
	if (!texture)
	{throw SDL_GetError();}

	SDL_FreeSurface(render);
	m_pTexture2D = std::make_shared<Texture2D>(texture);
}

void engine::TextComponent::Update()
{
}
