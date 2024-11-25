#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AStoreMap : public AActor
{
public:
	// constrcuter destructer
	AStoreMap();
	~AStoreMap();

	// delete Function
	AStoreMap(const AStoreMap& _Other) = delete;
	AStoreMap(AStoreMap&& _Other) noexcept = delete;
	AStoreMap& operator=(const AStoreMap& _Other) = delete;
	AStoreMap& operator=(AStoreMap&& _Other) noexcept = delete;

protected:

private:

};

