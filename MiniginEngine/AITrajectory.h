#pragma once
#include "Structs.h"

namespace engine
{
	struct Trajectory
	{
		// basically going from one point (pathfinder node) to another 
		// needs the previous direction and path node as we can compare indexes afterwards
		Trajectory(std::shared_ptr<Trajectory> traj, int idx, WorldDirection dir);

		void SetTrajectory(std::shared_ptr<Trajectory> ai);
		std::shared_ptr<engine::Trajectory> GetTrajectory() const;

		bool CompareIndex(int idx);

		void SetIndex(int idx);
		int GetIndex() const;

		void SetWorldDirection(WorldDirection wDir);
		WorldDirection GetWordDirection() const;

	protected:
	private:
		std::shared_ptr<Trajectory> m_Node;

		int m_Index;

		WorldDirection m_WorldDirection;
	};

	class AITrajectory
	{
		AITrajectory() = default;
		~AITrajectory() = default;
	};


}