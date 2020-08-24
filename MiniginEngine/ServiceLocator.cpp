#include "MiniginPCH.h"
#include "ServiceLocator.h"

#include "Structs.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "CollisionManager.h"

#include "Renderer.h"
#include "GameTime.h"
#include "AudioResource.h"

std::shared_ptr<engine::SDLWindowInfo> engine::ServiceLocator::m_pWindowInfo{};

std::shared_ptr<engine::InputManager> engine::ServiceLocator::m_pInputManager{};
std::shared_ptr<engine::ResourceManager> engine::ServiceLocator::m_pResourceManager{};
std::shared_ptr<engine::SceneManager> engine::ServiceLocator::m_pSceneManager{};
std::shared_ptr<engine::CollisionManager> engine::ServiceLocator::m_pCollisionManager{};

std::shared_ptr<engine::Renderer> engine::ServiceLocator::m_pRenderer{};
std::shared_ptr<engine::GameTime> engine::ServiceLocator::m_pGameTime{};
//std::shared_ptr<engine::AudioService> engine::ServiceLocator::m_pAudioResource{};

void engine::ServiceLocator::Initialize(float windowX, float windowY)
{
	m_pWindowInfo = std::make_shared<SDLWindowInfo>();
	m_pWindowInfo->_x = windowX;
	m_pWindowInfo->_y = windowY;
	
	SetInputManager(std::make_shared<InputManager>());
	SetResourceManager(std::make_shared<ResourceManager>());
	SetSceneManager(std::make_shared<SceneManager>());
	SetCollisionManager(std::make_shared<CollisionManager>());
	
	SetRenderer(std::make_shared<Renderer>());
	SetGameTime(std::make_shared<GameTime>());
	//SetAudioResource(std::make_shared<AudioService>());
}

void engine::ServiceLocator::SetWindowInfo(std::shared_ptr<engine::SDLWindowInfo> window)
{
	m_pWindowInfo = window;
}

void engine::ServiceLocator::SetInputManager(std::shared_ptr<InputManager> input)
{
	m_pInputManager = input;
}

void engine::ServiceLocator::SetResourceManager(std::shared_ptr<ResourceManager> resource)
{
	m_pResourceManager = resource;
}

void engine::ServiceLocator::SetSceneManager(std::shared_ptr<SceneManager> scene)
{
	m_pSceneManager = scene;
}

void engine::ServiceLocator::SetCollisionManager(std::shared_ptr<engine::CollisionManager> collision)
{
	m_pCollisionManager = collision;
}

void engine::ServiceLocator::SetRenderer(std::shared_ptr<Renderer> renderer)
{
	m_pRenderer = renderer;
}

void engine::ServiceLocator::SetGameTime(std::shared_ptr<GameTime> gametime)
{
	m_pGameTime = gametime;
}

/*void engine::ServiceLocator::SetAudioResource(std::shared_ptr<AudioService> audio)
{
	m_pAudioResource = audio;
}*/
