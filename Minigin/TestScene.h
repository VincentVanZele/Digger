#pragma once
#include "Scene.h"
#include "SpriteComponent.h"

namespace engine
{
	class GameObject;

	class TestScene final : public Scene
	{
	public:
		TestScene();

		virtual void Initialize() override;
		virtual void Update() override;

	private:
		std::shared_ptr<GameObject> m_pSprite, m_pText, m_pTexture;

		std::shared_ptr<GameObject> m_SpriteObject = std::make_shared<GameObject>();
		std::shared_ptr<SpriteComponent> spritecomp = std::make_shared<SpriteComponent>();
	};
}


