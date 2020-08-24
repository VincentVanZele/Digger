#pragma once

namespace engine
{
	class EnemyCharacter;
	class Event;
	class Listener;

	enum class EnemyState
	{
		Moving,
		DyingToBomb,
		DyingToGoldBag,
		Dying
	};

	class BaseEnemyState // stores enemy pointer
	{
	public:
		BaseEnemyState(EnemyState enemyState);

		virtual void Update() = 0;
		
		EnemyState _enemyState;
	protected:
		EnemyCharacter* _pEnemy;
	private:
	};

	class MovingEnemyState final : public BaseEnemyState
	{
	public:
		MovingEnemyState();

		virtual void Update() override;
	protected:
	private:
	};

	class DyingToBombEnemyState final : public BaseEnemyState
	{
	public:
		DyingToBombEnemyState(std::shared_ptr<Event> event);

		virtual void Update() override;
		void DeadCheck();

	protected:
	private:
		std::shared_ptr<engine::Listener> m_spListener;
	};
	
	class DyingEnemyState final : public BaseEnemyState
	{
	public:
		DyingEnemyState();

		virtual void Update() override;
	protected:
	private:
		float _deltaT = 0.0f,
			_maxDeltaT = 0.0f;
	};

	class DyingToGoldBagEnemyState final : public BaseEnemyState
	{
	public:
		DyingToGoldBagEnemyState();

		virtual void Update() override;
	protected:
	private:
	};
}
