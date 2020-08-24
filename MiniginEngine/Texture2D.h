#pragma once
struct SDL_Texture;

namespace engine
{
	class Texture2D
	{
	public:
		explicit Texture2D(SDL_Texture* texture);
		~Texture2D();

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;

		int GetTextWidth() const;
		int GetTextHeight() const;
		
		SDL_Texture* GetSDLTexture() const;

		void SetInitialized(bool init);
		bool GetInitilialized() const;

	private:
		SDL_Texture* m_Texture;
		uint32_t m_Format;
		int m_Width = 0, m_Height = 0, m_Access = 0;
		bool m_isInitialized = false;
	};
}
