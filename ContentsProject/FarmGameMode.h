#pragma once
#include <EngineCore/GameMode.h>
#include "TileMap.h"


// 농장 게임 모드
class AFarmGameMode : public AGameMode
{
public:
	// constrcuter destructer
	AFarmGameMode();
	~AFarmGameMode();

	// delete Function
	AFarmGameMode(const AFarmGameMode& _Other) = delete;
	AFarmGameMode(AFarmGameMode&& _Other) noexcept = delete;
	AFarmGameMode& operator=(const AFarmGameMode& _Other) = delete;
	AFarmGameMode& operator=(AFarmGameMode&& _Other) noexcept = delete;

	void BeginPlay();
	void Tick(float _DeltaTime) override;

protected:

private:
	ATileMap* FarmTileMap = nullptr;
	// ATileMap* TreeTileMap = nullptr;

	int TileImages = 0;
	ATileMap* GroundTileMap = nullptr;
};

