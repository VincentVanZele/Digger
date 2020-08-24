#include "MiniginPCH.h"
#include "AITrajectory.h"

engine::Trajectory::Trajectory(std::shared_ptr<Trajectory> traj, int idx, WorldDirection dir)
	: m_Node{ traj }
	, m_Index{ idx }
	, m_WorldDirection{ dir }
{
}

void engine::Trajectory::SetTrajectory(std::shared_ptr<Trajectory> ai)
{
	m_Node = ai;
}

std::shared_ptr<engine::Trajectory> engine::Trajectory::GetTrajectory() const
{
	return m_Node;
}

bool engine::Trajectory::CompareIndex(int idx)
{
	return (m_Index == idx);
}

void engine::Trajectory::SetIndex(int idx)
{
	m_Index = idx;
}

int engine::Trajectory::GetIndex() const
{
	return m_Index;
}

void engine::Trajectory::SetWorldDirection(WorldDirection wDir)
{
	m_WorldDirection = wDir;
}

engine::WorldDirection engine::Trajectory::GetWordDirection() const
{
	return m_WorldDirection;
}
