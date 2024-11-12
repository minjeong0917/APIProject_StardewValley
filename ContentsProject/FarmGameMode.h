#pragma once
#include <EngineCore/GameMode.h>
#include "TileMap.h"
#include "ContentsEnum.h"

#include <vector>

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
	void TileChange();
	void PutTile(float _DeltaTime);

	bool CropsTime(float _Deltatime);


	std::string GetTileSpriteName(FVector2D Location);

protected:

private:
	ATileMap* FarmTileMap = nullptr;
	ATileMap* CropTileMap = nullptr;
	// ATileMap* TreeTileMap = nullptr;

	ETileImage TileImages = ETileImage::Dirt;
	ATileMap* GroundTileMap = nullptr;

	bool IsNextDay = false;
};

