#pragma once
#include "Scene.h"
#include "Structs.h"

namespace engine
{
	enum Button
	{
		ButtonSolo,
		ButtonMultiplayer,
		ButtonExit
	};

	class SpriteComponent;

	class TitleScreenScene final : public Scene
	{
	public:
		TitleScreenScene();

		virtual void Initialize() override;
		virtual void Update() override;
		//virtual void Draw() const override;

		void ButtonClicked(Button button);

		void UpdateInput();
		void SetupLettres();
		void SetupSprites();
		void SetupButton();

	protected:
	private:
		Button m_selectedButton;

		float m_sign;

		Float2 m_soloPos{}, m_coopPos{}, m_exitPos{}, // button pos
			m_firePos1{}, m_firePos2{}, m_firePos3{}, m_firePos4{}, m_firePos5{},
			m_letterD{}, m_letterI{}, m_letterG1{}, m_letterG2{}, m_letterE{}, m_letterR{}; // rotating fire sprites 

		std::vector<std::shared_ptr<GameObject>> m_vspLetters;
		std::vector<std::shared_ptr<GameObject>> m_vspFire; // random fire in scene
		std::vector<std::shared_ptr<SpriteComponent>> m_vspFireComp; // random fire in scene 

		std::shared_ptr<GameObject> m_spFire2; // select fire
		std::shared_ptr<SpriteComponent> m_spFire2Comp; // select fire comp
	};
}