#pragma once
#include "Singleton.h"

namespace engine
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void AddScene(std::shared_ptr<Scene> scene);
		void SetActiveScene(const std::string& name);

		void Update();
		void Draw();

		std::vector<std::shared_ptr<Scene>> GetScenes() const;

	private:
		std::vector<std::shared_ptr<Scene>> mScenes;
		std::shared_ptr<Scene> mActiveScene;
	};

}
