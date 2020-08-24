#pragma once
#include "SceneManager.h"

namespace engine
{
	class GameObject;
	class Scene // not final because we will have different types of scenes
	{			// when creating the main game
	public:
		explicit Scene(const std::string& name);
		virtual ~Scene() = default;

		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		virtual void Initialize() = 0;
		virtual void Update();
		//virtual void LateUpdate();
		virtual void Draw() const;

		void Add(const std::shared_ptr<GameObject>& object);

		void SetName(std::string& name);
		std::string GetName() const;

		void SetInitialized(bool init);
		bool GetInitialized() const;
	protected:
		bool m_IsInitialized;

	private: 
		std::string mName{};
		std::vector<std::shared_ptr<GameObject>> mObjects{};

		static unsigned int idCounter; 
	};

}
