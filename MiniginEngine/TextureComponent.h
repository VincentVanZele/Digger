#pragma once
#include "BaseComponent.h"


namespace engine
{
	class Texture2D;

	class TextureComponent : public BaseComponent
	{
	public:
		TextureComponent();

		virtual void Draw() override;

		Texture2D& GetTexture() const;
		void SetTexture(std::shared_ptr<Texture2D> pTexture);

	protected:
		std::shared_ptr<Texture2D> m_pTexture2D;
	private:
	};

}