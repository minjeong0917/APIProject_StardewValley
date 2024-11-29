#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AHouseMap : public AActor
{
public:
	// constrcuter destructer
	AHouseMap();
	~AHouseMap();

	// delete Function
	AHouseMap(const AHouseMap& _Other) = delete;
	AHouseMap(AHouseMap&& _Other) noexcept = delete;
	AHouseMap& operator=(const AHouseMap& _Other) = delete;
	AHouseMap& operator=(AHouseMap&& _Other) noexcept = delete;

protected:

private:

};

