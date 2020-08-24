#include "MiniginPCH.h"
#include "Texture2D.h"
#include <SDL.h>

engine::Texture2D::Texture2D(SDL_Texture* texture)
	: m_Texture(texture)
{
	SDL_QueryTexture(m_Texture, &m_Format, &m_Access, &m_Width, &m_Height);
}

engine::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

int engine::Texture2D::GetTextWidth() const
{
	return m_Width;
}

int engine::Texture2D::GetTextHeight() const
{
	return m_Height;
}

SDL_Texture* engine::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

void engine::Texture2D::SetInitialized(bool init)
{
	m_isInitialized = init;
}

bool engine::Texture2D::GetInitilialized() const
{
	return m_isInitialized;
}

