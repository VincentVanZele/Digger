#pragma once

namespace engine
{
	class GoldBag;

	// GoldBag state
	// https://gameprogrammingpatterns.com/state.html

	class GoldBagState // stores gold bag pointer
	{
		
	public:
		virtual ~GoldBagState() {};
		virtual void Update() = 0;

		GoldBag* _pGoldBag;
	protected:
	private:
	};

	// we need :
	// - Default / immobile 
	// - ReadyToFall / wiggling for a few seconds before falling ->
	// - Falling / falling until ground ->
	// - Destroyed / fell on the ground

	class gbsDefault : public GoldBagState // Gold Bag State
	{
	public:
		// determines if will fall or not then change state
		virtual void Update() override;
	};

	//  |   |   |
	//  v   v   v

	class gbsWiggling : public GoldBagState
	{
	public:
		// will wiggle for a certains amount of frames until falling 
		// frameDeltaT >= wigglingDeltaT -> modify frame
		// currDeltaT >= MaxDeltaT -> change state
		virtual void Update() override;

		void SetFrameDeltaT(float f);
		float GetFrameDeltaT() const;

		void SetWiggleDeltaT(float f);
		float GetWiggleDeltaT() const;

		void SetCurrentDeltaT(float f);
		float GetCurrentDeltaT() const;

		void SetMaxDeltaT(float f);
		float GetMaxDeltaT() const;

	protected:
	private:
		int _frameCount = 0;

		float _frameDeltaT = 0.0f,
			_wiggleDeltaT = 0.0f,
			_currDeltaT = 0.0f,
			_maxDeltaT = 0.0f;
	};

	//  |   |   |
	//  v   v   v

	class gbsFalling : public GoldBagState
	{
	public:
		// falls then determines if hit ground or not to change state
		virtual void Update() override;
	};

	//  |   |   |
	//  v   v   v

	class gbsDestroyed : public GoldBagState
	{
	public:
		// determines if object needs to be destroyed
		// if currDeltaT > MaxDeltaT -> destroy
		virtual void Update() override;

		void SetCurrentDeltaT(float f);
		float GetCurrentDeltaT() const;

		void SetMaxDeltaT(float f);
		float GetMaxDeltaT() const;

	protected:
	private:
		float _currDeltaT = 0.0f,
			_maxDeltaT = 0.0f;
	};
}