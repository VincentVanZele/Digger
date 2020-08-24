#pragma once
#include "BaseComponent.h"
#include "Structs.h"
#include <memory>

namespace engine
{
	class Texture2D;

	class Event;
	class Listener;

	class ButtonComponent final : public BaseComponent
	{
	public:
		ButtonComponent(std::shared_ptr<Texture2D> texture, float width, float height);

		//virtual void Update() override;
		virtual void Draw() override;

		void MouseClickedEvent();

		// Texture
		void SetTexture(std::shared_ptr<Texture2D> texture);
		std::shared_ptr<Texture2D> GetTexture() const;

		void SetDimensionRect(Float2& dimension);
		Float2 GetDimensionRect() const;


		// Event
		std::shared_ptr<Event> GetEvent() const;

		std::shared_ptr<Event> m_spClick;
		std::shared_ptr<Listener> listener;
	protected:

	private:
		Float2 m_dimensionRect;

		std::shared_ptr<Texture2D> m_spTexture;
	};
}