#pragma once
namespace engine
{
	class SceneObject : public std::enable_shared_from_this<SceneObject>
	{
	public:
		SceneObject() = default;
		virtual ~SceneObject() = default;
		
		virtual void Update() = 0;
		virtual void Draw() const = 0;
		virtual void Destroy() = 0;

		SceneObject(const SceneObject& other) = delete;
		SceneObject(SceneObject&& other) = delete;
		SceneObject& operator=(const SceneObject& other) = delete;
		SceneObject& operator=(SceneObject&& other) = delete;
	};
}
