#include "MiniginPCH.h"
#include "Font.h"
#include <SDL_ttf.h>

TTF_Font* engine::Font::GetFont() const {
	return mFont;
}

engine::Font::Font(const std::string& fullPath, unsigned int size)
	: mFont(nullptr), mSize(size)
{
	mFont = TTF_OpenFont(fullPath.c_str(), size);
	if (mFont == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

engine::Font::~Font()
{
	TTF_CloseFont(mFont);
}
