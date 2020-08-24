#pragma once
#include "Structs.h"
#include <memory>

namespace engine
{
	//forward decl
	class InputManager;
	class ResourceManager;
	class SceneManager;
	class CollisionManager;

	class Renderer;
	class GameTime;
	//class AudioService;

	// all static 
	class ServiceLocator final
	{
	public:
		static void Initialize(float windowX, float windowY);

		// Window Info
		static std::shared_ptr<engine::SDLWindowInfo> GetWindowInfo() { return m_pWindowInfo; }
		static void SetWindowInfo(std::shared_ptr<engine::SDLWindowInfo> window);

		// Input Manager
		static std::shared_ptr<engine::InputManager> GetInputManager() { return m_pInputManager; }
		static void SetInputManager(std::shared_ptr<engine::InputManager> input);
	
		// Resource Manager
		static std::shared_ptr<engine::ResourceManager> GetResourceManager() { return m_pResourceManager; }
		static void SetResourceManager(std::shared_ptr<engine::ResourceManager> resource);

		// Scene Manager
		static std::shared_ptr<engine::SceneManager> GetSceneManager() { return m_pSceneManager; }
		static void SetSceneManager(std::shared_ptr<engine::SceneManager> scene);

		// Collision Manager
		static std::shared_ptr<engine::CollisionManager> GetCollisionManager() { return m_pCollisionManager; }
		static void SetCollisionManager(std::shared_ptr<engine::CollisionManager> collision);

		// Renderer
		static std::shared_ptr<engine::Renderer> GetRenderer() { return m_pRenderer; }
		static void SetRenderer(std::shared_ptr<engine::Renderer> renderer);

		// Game Time
		static std::shared_ptr<engine::GameTime> GetGameTime() { return m_pGameTime; }
		static void SetGameTime(std::shared_ptr<engine::GameTime> gametime);

		// Audio Resource 
		//static std::shared_ptr<engine::AudioService> GetAudioResource() { return m_pAudioResource; }
		//static void SetAudioResource(std::shared_ptr<engine::AudioService> audio);

	private:
		static std::shared_ptr<engine::SDLWindowInfo> m_pWindowInfo;

		static std::shared_ptr<engine::InputManager> m_pInputManager;
		static std::shared_ptr<engine::ResourceManager> m_pResourceManager;
		static std::shared_ptr<engine::SceneManager> m_pSceneManager;
		static std::shared_ptr<engine::CollisionManager> m_pCollisionManager;

		static std::shared_ptr<engine::Renderer> m_pRenderer;
		static std::shared_ptr<engine::GameTime> m_pGameTime;
		//static std::shared_ptr<engine::AudioService> m_pAudioResource;
	};

}

