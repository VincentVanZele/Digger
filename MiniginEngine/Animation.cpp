#include "MiniginPCH.h"
#include "Animation.h"
#include "Texture2D.h"
#include "Renderer.h"

engine::Animation::Animation(std::shared_ptr<Texture2D> tex, const std::string& name, int nbrFrames)
	: m_pTexture2D{ tex }
	, m_Name{ name }
	, m_nbrFrames{ nbrFrames }, m_currFrame{ 0 }
{
}

void engine::Animation::Update(float& deltaT)
{
	if (m_FrameDeltatime < 0)
	{
		return;
	}
	else if (m_FrameDeltatime <= deltaT)
	{
		deltaT -= m_FrameDeltatime;
		m_currFrame = (m_currFrame + 1) % m_nbrFrames;

		if (m_currFrame == 0 && !m_Loop)
		{
			m_currFrame = m_nbrFrames - 1;
		}
	}
}

void engine::Animation::Draw() const
{
	Float4 dest{}, src{};
	float col = (float) (m_pTexture2D->GetTextWidth() / m_nbrFrames);
	float row = (float)m_pTexture2D->GetTextHeight();

	dest = Float4{
		dest._x = m_Pos._x - (col / 2),
		dest._y = m_Pos._y - (dest._w / 2),
		dest._z = col,
		dest._w = row
	};
	
	src = Float4{
		src._x = dest._z * m_currFrame,
		src._y = 0,
		src._z = dest._z,
		src._w = dest._w
	};

	Renderer::GetInstance().RenderTexture(*m_pTexture2D, dest, src);
}

void engine::Animation::SetFrameDeltatime(float deltaTime)
{
	m_FrameDeltatime = deltaTime;
}

void engine::Animation::SetName(const std::string& name)
{
	m_Name = name;
}

std::string engine::Animation::GetName() const
{
	return m_Name;
}

bool engine::Animation::CheckName(const std::string& name)
{
	return (m_Name.compare(name) == 0);
}

void engine::Animation::SetNbrOfFrames(int nbrFrames)
{
	m_nbrFrames = nbrFrames;
}

int engine::Animation::GetNbrOfFrames() const
{
	return m_nbrFrames;
}

void engine::Animation::SetCurrFrame(int currFrame)
{
	m_currFrame = currFrame;
}

int engine::Animation::GetCurrFrame() const
{
	return m_currFrame;
}

void engine::Animation::SetPos(Float2 pos)
{
	m_Pos = pos;
}

engine::Float2 engine::Animation::GetPos() const
{
	return m_Pos;
}

void engine::Animation::SetLoop(bool loop)
{
	m_Loop = loop;
}

bool engine::Animation::GetLoop() const
{
	return m_Loop;
}

void engine::Animation::SetTexture(std::shared_ptr<Texture2D> tex)
{
	m_pTexture2D = tex;
}

engine::Texture2D& engine::Animation::GetTexture() const
{
	return *m_pTexture2D;
}

void engine::Animation::SetFrame(int frame)
{
	m_currFrame = frame;
}

