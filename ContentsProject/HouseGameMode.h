#pragma once
#include <EngineCore/GameMode.h>
#include "TileMap.h"

// Ό³Έν :
class AHouseGameMode : public AGameMode
{
public:
	// constrcuter destructer
	AHouseGameMode();
	~AHouseGameMode();

	// delete Function
	AHouseGameMode(const AHouseGameMode& _Other) = delete;
	AHouseGameMode(AHouseGameMode&& _Other) noexcept = delete;
	AHouseGameMode& operator=(const AHouseGameMode& _Other) = delete;
	AHouseGameMode& operator=(AHouseGameMode&& _Other) noexcept = delete;
	std::string GetHouseTileSpriteName(FVector2D Location);


	bool GetIsBedIn()
	{

		return IsBedIn;
	}
	bool GetIsNo()
	{

		return IsNo;
	}
	void SetIsNo(bool _IsNo)
	{

		IsNo = _IsNo;
	}
protected:
	void BeginPlay() override;

	void Tick(float _DeltaTime) override;

private:
	ATileMap* HouseTileMap = nullptr;
	bool IsBedIn = false;
	bool IsNo = false;

};

