#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include <SDL.h>

#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ServiceLocator.h"

#include "ResourceManager.h"
#include "SpriteComponent.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"

#include "GameTime.h"
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"
#include "Animation.h"

void engine::Minigin::Initialize()
{
	auto width{ 640 }, height{ 480 };

	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	ServiceLocator::Initialize((float)width, (float)height);

	ServiceLocator::GetRenderer()->GetInstance().Init(window);

	ServiceLocator::GetResourceManager()->GetInstance().Init("../Data/");
}

void engine::Minigin::LoadGame() const
{
	
}

void engine::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void engine::Minigin::Run()
{
	LoadGame();				

	{
		//modification added according to powerpoint slides 
		auto t = std::chrono::high_resolution_clock::now();

		auto& renderer = ServiceLocator::GetRenderer()->GetInstance();
		auto& sceneManager = ServiceLocator::GetSceneManager()->GetInstance();
		auto& input = ServiceLocator::GetInputManager()->GetInstance();
		auto& gameTime = ServiceLocator::GetGameTime()->GetInstance();

		bool doContinue = true;

		while (doContinue)
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - t).count();
			if (deltaTime > 0.06f)
				deltaTime = 0.06f;
			t = currentTime;

			doContinue = input.ProcessInput();

			sceneManager.Update();
			renderer.Render();
			gameTime.Update(deltaTime);
		}
	}

	Cleanup();
}
