#pragma once
#include <cmath>
#include <Xinput.h>
#pragma comment(lib,"Xinput.lib")


namespace engine
{
	// --------- WINDOW STRUCTS/CLASSES ---------

	// SDL window size information (connected to service locator)
	struct SDLWindowInfo
	{
		friend class ServiceLocator;

	public:
		float GetWindowWidth() { return _x; }
		float GetWindowHeight() { return _y; }

	private:
		float _x, _y;
	};
	// --------- COMMAND STRUCTS/CLASSES ---------

	// SDL Key code
	struct SDLCommand
	{ 
		SDLCommand()
			:_sdlKey{ '\0' } //https://wiki.libsdl.org/SDLKeycodeLookup SDL_UNKNOWN
		{}
		// int32_t correspond to a certain key code by SDL
		SDLCommand(int32_t key) 
			:_sdlKey{ key }
		{}

		int32_t _sdlKey;

		bool _keyPressed{ false };
		bool _keyUp{ false };
		bool _keyDown{ false };
	};

	struct KeyAxis
	{
		KeyAxis() // need default constructor because error 
			: _keyPositive{ '\0' }, _keyNegative{ '\0' }
			, _value{ 0.0f }
		{
		}

		KeyAxis(int32_t key1, int32_t key2)
			: _keyPositive{ key1 }, _keyNegative{ key2 }
			, _value{0.0f}
		{
		}

		void SetValue(float value)
		{
			_value = value;
		}

		float GetValue() const 
		{
			return _value;
		}

		int32_t _keyPositive, _keyNegative;
		float _value;
	};

	// XBox controller input layout 
	enum class ControllerButton
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY,
		DPLeft,
		DPRight,
		DPUp,
		DPDown
	};

	// --------- FLOAT STRUCTS/CLASSES ---------

	// F2
	struct Float2
	{
		// Variables
		float _x{}, _y{};

		// Constructors
		Float2()
			: _x(0), _y(0)
		{
		}

		Float2(float x, float y)
			:_x(x), _y(y)
		{
		}

		// Functions 
		float Length()
		{
			return (sqrt(_x * _x + _y * _y));
		}

		void Normalize()
		{
			_x /= Length();
			_y /= Length();
		}
	};

	// F3
	struct Float3
	{
		float _x{}, _y{}, _z{};

		Float3(float x, float y, float z)
			:_x(x), _y(y), _z(z)
		{
		}

		Float3()
			:_x(0), _y(0), _z(0)
		{
		}
	};

	// F4
	struct Float4
	{
		float _x{}, _y{}, _z{}, _w{};

		Float4(float x, float y, float z, float w)
			: _x(x), _y(y), _z(z), _w(w)
		{
		}
		Float4()
			:_x(0), _y(0), _z(0), _w(0)
		{
		}
	};

	// --------- WORLD STRUCTS/CLASSES ---------

	// World axis 
	enum class WorldDirection
	{
		Default,
		Left,
		Right,
		Up,
		Down
	};

	// --------- GRID & TILE STRUCTS/CLASSES ---------

	// tile components
	enum class TileSurrounding
	{
		Default, // itself
		Left,
		Right,
		Up,
		Down
	};

	struct TileSurroundingState
	{
		//TileSurroundingState() = default;
		//~TileSurroundingState() = default; 

		// broken or not
		bool _DefaultState = true,
			 _LeftState = true,
			 _RightState = true,
			 _UpState = true,
			 _DownState = true;
	};

	// tile base states
	enum class TileState
	{
		Default,
		Breaking,
		Moving
	};

	// tile movement states
	enum class TileMovement
	{
		Open, // good to go
		Closed, // blocked
		Breaking
	};

	// collider
	enum ColliderTag
	{
		FireBall,
		GoldBags,
		Default
	};

}