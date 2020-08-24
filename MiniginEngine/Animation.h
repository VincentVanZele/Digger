#pragma once
#include <memory>
#include "Structs.h"

namespace engine
{
	class Texture2D;
	class GameObject;

	class Animation
	{
	public:
		Animation(std::shared_ptr<Texture2D> tex, const std::string& name, int nbrFrames);

		void Draw() const;
		void Update(float& accuSec);

		void SetTexture(std::shared_ptr<Texture2D> tex);
		Texture2D& GetTexture() const;

		void SetName(const std::string& name);
		std::string GetName() const;
		bool CheckName(const std::string& name);

		void SetNbrOfFrames(int nbrFrames);
		int GetNbrOfFrames() const;

		void SetCurrFrame(int currFrame);
		int GetCurrFrame() const;

		void SetFrameDeltatime(float deltaTime);
		void SetFrame(int frame);

		void SetPos(Float2 pos);
		Float2 GetPos() const;

		void SetLoop(bool loop);
		bool GetLoop() const;

	private:
		std::shared_ptr<Texture2D> m_pTexture2D;
		std::string m_Name;

		int m_nbrFrames, m_currFrame;
		float m_FrameDeltatime = 0.333f;

		Float2 m_Pos;
		bool m_Loop = true;
	};
}