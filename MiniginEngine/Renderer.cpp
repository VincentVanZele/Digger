#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"


void engine::Renderer::Init(SDL_Window * window)
{
	m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void engine::Renderer::Render()
{
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Draw();
	
	SDL_RenderPresent(m_Renderer);
}

void engine::Renderer::Destroy()
{
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void engine::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void engine::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void engine::Renderer::RenderTexture(const Texture2D& tex, const Float4& destRect, const Float4& srcRect) const
{
	SDL_Rect dst{
		int(destRect._x * m_Scale),
		int(destRect._y * m_Scale),
		int(destRect._z * m_Scale),
		int(destRect._w * m_Scale) };

	SDL_Rect src{
		int(srcRect._x),
		int(srcRect._y),
		int(srcRect._z),
		int(srcRect._w) };

	SDL_RenderCopy(GetSDLRenderer(), tex.GetSDLTexture(), &src, &dst);
}

float engine::Renderer::GetScale() const
{
	return m_Scale;
}

void engine::Renderer::SetScale(float scale)
{
	m_Scale = scale;
}
