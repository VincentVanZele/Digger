#pragma once
#include "Singleton.h"
#include "Structs.h"

struct SDL_Window;
struct SDL_Renderer;

namespace engine
{
	class Texture2D;

	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render();
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& tex, const Float4& destRect, const Float4& srcRect) const;

		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }

		float GetScale() const;
		void SetScale(float scale);

	private:
		SDL_Renderer* m_Renderer = nullptr;
		float m_Scale;
	};
}

