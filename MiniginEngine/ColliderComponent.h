#pragma once
#include "BaseComponent.h"
#include <iostream>

#include "Structs.h"
#include "Event.h"
#include "Listener.h"

namespace engine
{
	
	class ColliderComponent final : public BaseComponent
	{
		friend class CollisionManager; // manager for rectangle overlapping calculation
		friend class PlayerCharacter;
	public:
		ColliderComponent(std::string tag); // using tags to differenciate each and every collider
											// enemies != player != bags
		~ColliderComponent() = default;

		virtual void Initialize() override;
		virtual void Destroy() override;

		// --- Not used virtual functions ---
		//virtual void Update() {};
		//virtual void LateUpdate() {};
		//virtual void Draw() {};

		// This comp
		std::string GetTag();
		void SetTag(std::string tag); // in case we need to change

		// Collided comp
		std::string GetCollidedTag();
		void SetCollidedTag(std::string tag); // in case we need to change

		size_t GetId(); // same idea as with listeners ID but non static
						// as colliders depend on their creation and destruction
		void SetId(size_t id);
		bool CompareId(size_t id);

		// overlaping rectangle
		Float4 GetCollisionRect() const;
		void SetCollisionRect(const Float4& rect);

		// collider object 
		ColliderComponent* GetColliderComp();
		// SetColliderComp() not needed !

		// detection between & for who 
		void AddTarget(std::string target);
		void RemoveTarget(std::string target);

		std::vector<std::string> GetTargetVector();
		void SetTargetVector(std::vector<std::string> targetVect);

		Event GetEvent() const;
		void SetEvent(Event event);

	protected:
		ColliderComponent* m_pColliderComp; // collider object
	private:
		std::string m_tag;
		std::vector<std::string> m_vTargets;
		
		// Event 
		Event m_HasCollided;

		size_t m_id = 0;
		Float4 m_collisionRect;
	};
}

