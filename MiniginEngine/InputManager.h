#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "Structs.h"
#include <unordered_map>

namespace engine
{
	class Event;
	class Listener;

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		//~InputManager();

		bool ProcessInput(); // keyboard + controller input 
		bool ProcessKeyboardInput();
		bool ProcessControllerInput();
		
		void AddInput(const std::string& name, int32_t sdlKey);

		// Mouse
		Float2 GetMousePos();
		void UpdateMousePos();

		// Keyboard
		// neww && because of std::move 
		// https://www.artima.com/cppsource/rvalue.html

		bool IsPressed(std::string&& name);	  // get input by name
		bool IsDown(std::string&& name);
		bool IsUp(std::string&& name);

		// Axis
		void AddAxis(std::string name, int32_t button1, int32_t button2);
		float GetAxis(std::string&& axis);
		
		// Gamepad
		XINPUT_STATE GetControllerInputState(int index);
		bool GetControllerIsValid(int index);

		bool IsButton(int index, ControllerButton cButton);

		// Game 
		void SetGameRunning(bool game);
		bool GetGameRunning() const;

	protected:
	private:
		// Keyboard
		Float2 m_mousePos;

		std::unordered_map<std::string, SDLCommand> m_KeyCommands;	// access each input easily via name 
		std::unordered_map<std::string, KeyAxis> m_Axis; // acces axis via name

		// Gamepad
		XINPUT_STATE m_controllerState[2]{};
		bool m_IsControllerValid[2]{ false };

		// Game 
		bool m_GameRunning = true;
	};
}

