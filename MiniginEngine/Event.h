#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>

namespace engine
{
	class Listener;

	class Event // on collide for example
	{
	public:
		~Event();

		void CallNotify();
		
		void AddListener(std::shared_ptr<Listener> listenerSP);
		void RemoveListener(size_t id);

	private:

		std::vector<std::shared_ptr<Listener>> m_spListenerVect{};
	};
}