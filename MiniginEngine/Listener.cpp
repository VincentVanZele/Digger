#include "MiniginPCH.h"
#include "Listener.h"

#include "Event.h"
 
int engine::Listener::idCounter{};

engine::Listener::Listener()
	: m_NotifyFunction{}
{
	currId = idCounter; // the total amount of ids gets updated
					// each time a new listener get initialized
	idCounter++;
}

void engine::Listener::SetNotifyFunction(std::function<void()> notifyFunc)
{
	m_NotifyFunction = notifyFunc;
}

void engine::Listener::Notify()
{
	// call notify function
	m_NotifyFunction();
}

size_t engine::Listener::GetListenerId()
{
	return currId;
}

bool engine::Listener::CompareId(const Listener& list)
{
	// does currId and id match 
	return currId = list.currId;
}

void engine::Listener::StopListening()
{
	// remove THIS listener from event
	m_pEvent->RemoveListener(currId);
}
