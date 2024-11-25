#pragma once
#include <EngineCore/GameMode.h>
#include "TileMap.h"
#include "ContentsEnum.h"
// Ό³Έν :
class AStoreGameMode : public AGameMode
{
public:
	// constrcuter destructer
	AStoreGameMode();
	~AStoreGameMode();

	// delete Function
	AStoreGameMode(const AStoreGameMode& _Other) = delete;
	AStoreGameMode(AStoreGameMode&& _Other) noexcept = delete;
	AStoreGameMode& operator=(const AStoreGameMode& _Other) = delete;
	AStoreGameMode& operator=(AStoreGameMode&& _Other) noexcept = delete;
	std::string GetStoreTileSpriteName(FVector2D Location);

	bool GetIsOpenCounter()
	{
		return IsOpenCounter;
	}

protected:
	void BeginPlay() override;

	void Tick(float _DeltaTime) override;

private:
	ATileMap* StoreTileMap = nullptr;
	
	bool IsOpenCounter = false;
};

