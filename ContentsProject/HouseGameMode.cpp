#include "PreCompile.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>
#include "HouseGameMode.h"
#include "HouseMap.h"
#include "Player.h"

AHouseGameMode::AHouseGameMode()
{

}

AHouseGameMode::~AHouseGameMode()
{
}

void AHouseGameMode::BeginPlay()
{

	APlayer* Player = GetWorld()->GetPawn<APlayer>();
	Player->SetBackImage("House.png");

	AHouseMap* House = GetWorld()->SpawnActor<AHouseMap>();

	Player->SetActorLocation({ 490, 720 });

	HouseTileMap = GetWorld()->SpawnActor<ATileMap>();
	HouseTileMap->Create({ 19,12 }, { 70, 70 });
	FIntPoint BedPoint = HouseTileMap->LocationToIndex({ 850, 600 });
	HouseTileMap->SetTileIndex("HouseTile", BedPoint, { 20, 20 }, { 128.f, 120.f }, 1);
	HouseTileMap->SetTileOrder(BedPoint, 1000.0f);
}


void AHouseGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	APlayer* Player = GetWorld()->GetPawn<APlayer>();
	Player->SetColImage("House_col.png");

	if (GetHouseTileSpriteName(Player->GetActorLocation()) == "HOUSETILE" && IsNo == false)
	{
		IsBedIn = true;
	}
	else
	{
		IsBedIn = false;
		
	}

	if (IsNo == true)
	{
		if (GetHouseTileSpriteName(Player->GetActorLocation()) != "HOUSETILE")
		{
			IsNo = false;
			IsBedIn = false;
		}
	}
}

std::string AHouseGameMode::GetHouseTileSpriteName(FVector2D Location)
{
	Tile* TileRef = HouseTileMap->GetTileRef(Location);
	if (TileRef)
	{
		std::string SpriteName = TileRef->GetSpriteName();
		return SpriteName;
	}
	else
	{
		return "NONE";
	}

}


