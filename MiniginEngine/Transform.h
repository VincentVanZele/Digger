#pragma once
#include "Structs.h"

namespace engine
{
	class Transform 
	{
	public:
		const Float3& GetPosition() const { return m_Position; }
		void SetPosition(const Float3& newPos);
		void SetPosition(float x, float y, float z);

		const Float2& GetScale() const;
		void SetScale(const Float2& scale);
		void SetScale(float x, float y);

	protected:
	private:
		Float3 m_Position;
		Float2 m_Scale;
	};
}
