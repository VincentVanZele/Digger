#pragma once
#include <functional>

namespace engine
{
	class Listener
	{
		friend class Event; 
	public:
		Listener();

		void SetNotifyFunction(std::function<void()> notifyFunc);
		//void GetNotifyFunction(); std::function !!!
		
		void Notify();
		
		size_t GetListenerId();
		bool CompareId(const Listener& listener);
		
		void StopListening();

		// variable
		Event* m_pEvent;

	private:
		int currId;
		static int idCounter;
		
		std::function<void()> m_NotifyFunction;
	};
}