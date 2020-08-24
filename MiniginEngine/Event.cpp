#include "MiniginPCH.h"
#include "Event.h"

#include "Listener.h"

engine::Event::~Event()
{
}

void engine::Event::CallNotify()
{
	for (auto listener : m_spListenerVect)
	{
		listener->Notify(); // calling notify function 
	}
}

void engine::Event::AddListener(std::shared_ptr<Listener> listenerSP)
{
	m_spListenerVect.push_back(listenerSP);
	// link listener to THIS event 
	listenerSP->m_pEvent = this;
}

void engine::Event::RemoveListener(size_t id)
{
	m_spListenerVect.erase
	(
		std::remove_if
		(
			m_spListenerVect.begin(), m_spListenerVect.end(),
			[id](std::shared_ptr<Listener> listener)
			{
				return listener->GetListenerId() == id; 
			}
		), m_spListenerVect.end()
	);
}
