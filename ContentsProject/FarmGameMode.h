#pragma once
#include <EngineCore/GameMode.h>
#include "TileMap.h"
#include "ContentsEnum.h"


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
	void PutTile();
	void UIImageRender();
	void GetTileSpriteName(FVector2D Location);

protected:

private:
	ATileMap* FarmTileMap = nullptr;
	// ATileMap* TreeTileMap = nullptr;

	ETileImage TileImages = ETileImage::Dirt;
	ATileMap* GroundTileMap = nullptr;
};

