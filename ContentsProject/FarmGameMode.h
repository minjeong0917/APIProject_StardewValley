#pragma once
#include <EngineCore/GameMode.h>
#include "TileMap.h"
#include "ContentsEnum.h"
#include "Time.h"
#include <vector>
#include "Item.h"
// ���� ���� ���
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

	std::string GetTileSpriteName(FVector2D Location);



	ATileMap* GetFarmTilMap()
	{
		if (nullptr != FarmTileMap)
		{
			return FarmTileMap;
		}
		return nullptr;
	}
	void TileDestroy();

protected:

private:
	void ItemDrop(std::string _ItemName, FVector2D _ItemLocatioln, FVector2D _PlayerPos, int _ItemIndex, float _ItemScale);

	ATileMap* FarmTileMap = nullptr;
	ATileMap* CropTileMap = nullptr;

	AItem* TreeItem = nullptr;
	ETileImage TileImages = ETileImage::Dirt;
	ATileMap* GroundTileMap = nullptr;

	ATime* Time = nullptr;
	int speed = 1;
	bool IsNextDay = false;
};

