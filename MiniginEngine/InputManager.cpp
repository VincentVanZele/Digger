#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>

#include "Event.h"
#include "Listener.h"

engine::InputManager::InputManager()
{
}

bool engine::InputManager::ProcessInput()
{
	if (!m_GameRunning)
	{
		return false;
	}
	if (!ProcessControllerInput())
	{
		return false;
	}
	if (!ProcessKeyboardInput())
	{
		return false;
	}

	return true;
}

void engine::InputManager::AddInput(const std::string& name, int32_t sdlKey)
{
	m_KeyCommands[name] = SDLCommand(sdlKey);
}

bool engine::InputManager::IsPressed(std::string&& name)
{
	return m_KeyCommands[std::move(name)]._keyPressed;
}

bool engine::InputManager::IsDown(std::string&& name)
{
	return m_KeyCommands[std::move(name)]._keyDown;
}

bool engine::InputManager::IsUp(std::string&& name)
{
	return m_KeyCommands[std::move(name)]._keyUp;
}

void engine::InputManager::AddAxis(std::string name, int32_t button1, int32_t button2)
{
	m_Axis[name] = KeyAxis(button1, button2);
}

float engine::InputManager::GetAxis(std::string&& axis)
{
	return m_Axis[std::move(axis)]._value;
}

bool engine::InputManager::ProcessKeyboardInput()
{
	for (auto& cmd : m_KeyCommands)
	{
		cmd.second._keyDown = false;
		cmd.second._keyUp = false;
	}

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		auto key = event.key.keysym.sym;

		switch (event.type)
		{
		case SDL_QUIT:
			return false;
		case SDL_KEYDOWN:
			// command buttons
			for (std::pair<const std::string, SDLCommand>& cmd : m_KeyCommands)
			{
				if (cmd.second._sdlKey == key)
				{
					if (cmd.second._keyPressed)
						break;

					cmd.second._keyPressed = true;
					cmd.second._keyDown = true;
					break;
				}
			}
			break;
		case SDL_KEYUP:
			if (key == SDLK_ESCAPE)
				return false;

			for (std::pair<const std::string, SDLCommand>& cmd : m_KeyCommands)
			{
				if (cmd.second._sdlKey == key)
				{
					cmd.second._keyPressed = false;
					cmd.second._keyUp = true;
					break;
				}
			}
			break;
		}
	}
	return true;
}

engine::Float2 engine::InputManager::GetMousePos()
{
	return m_mousePos;
}

void engine::InputManager::UpdateMousePos()
{
	int x{}, y{};
	SDL_GetMouseState(&x, &y);

	m_mousePos._x = (float)x;
	m_mousePos._y = (float)y;
}

XINPUT_STATE engine::InputManager::GetControllerInputState(int index)
{
	return m_controllerState[index];
}

bool engine::InputManager::IsButton(int index, ControllerButton cButton)
{
	if (!m_IsControllerValid[index])
	{
		return false;
	}

	switch (cButton)
	{
	case ControllerButton::ButtonA:
	{
		return m_controllerState[index].Gamepad.wButtons & XINPUT_GAMEPAD_A;
		break;
	}
	case ControllerButton::ButtonB:
	{
		return m_controllerState[index].Gamepad.wButtons & XINPUT_GAMEPAD_B;
		break;
	}
	case ControllerButton::ButtonX:
	{
		return m_controllerState[index].Gamepad.wButtons & XINPUT_GAMEPAD_X;
		break;
	}
	case ControllerButton::ButtonY:
	{
		return m_controllerState[index].Gamepad.wButtons & XINPUT_GAMEPAD_Y;
		break;
	}
	case ControllerButton::DPDown:
	{
		return m_controllerState[index].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
		break;
	}
	case ControllerButton::DPUp:
	{
		return m_controllerState[index].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
		break;
	}
	case ControllerButton::DPLeft:
	{
		return m_controllerState[index].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
		break;
	}
	case ControllerButton::DPRight:
	{
		return m_controllerState[index].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
		break;
	}
	}

	return false;
}

void engine::InputManager::SetGameRunning(bool game)
{
	m_GameRunning = game;
}

bool engine::InputManager::GetGameRunning() const
{
	return m_GameRunning;
}

bool engine::InputManager::GetControllerIsValid(int index)
{
	return m_IsControllerValid[index];
}

bool engine::InputManager::ProcessControllerInput()
{
	for (int i{ 0 }; i < 2; i++)
	{
		m_IsControllerValid[i] = XInputGetState(0, &m_controllerState[i]) == ERROR_SUCCESS;
	}
	return true;
}


