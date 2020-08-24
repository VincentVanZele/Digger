#pragma once
#include "Structs.h"
#include "BaseComponent.h"

namespace engine
{
	class TransformComponent final : public BaseComponent
	{
	public:
		TransformComponent();

		GameObject* GetChildObject() const { return m_pChild; }
		void SetChildObject(GameObject* pGO);

		void Translate(const Float2& pos);
		void Rotate(float rot);
		void Scale(const Float2& sca);

		void SetPosition(Float2 pos);
		Float2 GetPosition() const;
		void SetObjectPosition(Float2 pos);
		Float2 GetObjectPosition() const;

		void SetRotation(float rot);
		float GetRotation() const;
		void SetObjectRotation(float rot);
		float GetObjectRotation() const;

		void SetScale(Float2 sca);
		Float2 GetScale() const;
		void SetObjectScale(Float2 sca);
		Float2 GetObjectScale() const;

	protected:
	private:
		GameObject* m_pChild;

		Float2 m_Position, m_Scale;
		float m_Rotation;
	};
}
