#include "pch.h"
#include "GoldBagState.h"
#include "GoldBag.h"

#include "BaseComponent.h"
#include "WorldGridComponent.h"
#include "WorldMovementComponent.h"
#include "SpriteComponent.h"

#include "ServiceLocator.h"
#include "GameTime.h"

// --- DEFAULT ---
void engine::gbsDefault::Update()
{
	auto index = _pGoldBag->GetWorldGridComp()->GetCols();

	bool wiggling{ _pGoldBag->GetWorldGridComp()->GetBlankFromTile(index) };

	if (wiggling)
	{
		// collision 
		//...

		_pGoldBag->SetState(std::make_shared<gbsWiggling>());
	}
}

// --- READY TO FALL ---
void engine::gbsWiggling::Update()
{
	float deltaT = ServiceLocator::GetGameTime()->GetInstance().GetDeltaTime();
	_frameDeltaT += deltaT;

	// Wiggling
	if (_frameDeltaT >= _wiggleDeltaT)
	{
		_frameDeltaT -= _wiggleDeltaT;
		_frameCount = 1 - _frameCount;
		_pGoldBag->GetSpriteComp()->SetFrame(_frameCount);
	}

	//---
	_currDeltaT += deltaT;

	if (_currDeltaT >= _maxDeltaT)
	{
		_pGoldBag->SetState(std::make_shared<gbsFalling>());
	}
}

void engine::gbsWiggling::SetFrameDeltaT(float f)
{
	_frameDeltaT = f;
}

float engine::gbsWiggling::GetFrameDeltaT() const
{
	return _frameDeltaT;
}

void engine::gbsWiggling::SetWiggleDeltaT(float f)
{
	_wiggleDeltaT = f;
}

float engine::gbsWiggling::GetWiggleDeltaT() const
{
	return _wiggleDeltaT;
}

void engine::gbsWiggling::SetCurrentDeltaT(float f)
{
	_currDeltaT = f;
}

float engine::gbsWiggling::GetCurrentDeltaT() const
{
	return _currDeltaT;
}

void engine::gbsWiggling::SetMaxDeltaT(float f)
{
	_maxDeltaT = f;
}

float engine::gbsWiggling::GetMaxDeltaT() const
{
	return _maxDeltaT;
}

// --- FALLING ---
void engine::gbsFalling::Update()
{
	if (_pGoldBag->GetWorldMovementComp()->GenerateDirection(WorldDirection::Down) == engine::TileMovement::Closed)
	{
		_pGoldBag->SetState(std::make_shared<gbsDestroyed>());
	}
}

// --- DESTROYED ---
void engine::gbsDestroyed::Update()
{
	_currDeltaT += ServiceLocator::GetGameTime()->GetDeltaTime();
	if (_currDeltaT >= _maxDeltaT)
	{
		_pGoldBag->Destroy();
	}
}

void engine::gbsDestroyed::SetCurrentDeltaT(float f)
{
	_currDeltaT = f;
}

float engine::gbsDestroyed::GetCurrentDeltaT() const
{
	return _currDeltaT;
}

void engine::gbsDestroyed::SetMaxDeltaT(float f)
{
	_maxDeltaT = f;
}

float engine::gbsDestroyed::GetMaxDeltaT() const
{
	return _maxDeltaT;
}
