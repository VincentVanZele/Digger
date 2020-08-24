#pragma once
#include <string>
#include <memory>
#include "Font.h"
#include "Structs.h"
#include "TextureComponent.h"

namespace engine
{
	class TextComponent final : public TextureComponent
	{
	public:
		TextComponent(const std::string& text, const std::shared_ptr<Font> font, const Float4& color = { 1, 1, 1, 1 });

		std::string GetText() const;
		void SetText(const std::string& newText);

		Font& GetFont() const;
		void SetFont(const std::shared_ptr<Font>& newFont);

		Float4 GetColor() const;
		void SetColor(const Float4& col);

		void Texture();

		virtual void Update() override;

	private:

		std::shared_ptr<Font> m_pFont;
		std::string m_Text;
		Float4 m_Color;
	};
}
