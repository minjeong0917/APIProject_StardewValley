#include "PreCompile.h"
#include "FarmGameMode.h"

#include <EngineCore/Level.h>

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/EngineCoreDebug.h>

#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include "ContentsEnum.h"

#include "FarmMap.h"
#include "Player.h"


AFarmGameMode::AFarmGameMode()
{

}

AFarmGameMode::~AFarmGameMode()
{
}

void AFarmGameMode::BeginPlay()
{
	APlayer* Player = GetWorld()->GetPawn<APlayer>();
	Player->SetBackImage("Farm.png");

	FarmTileMap = GetWorld()->SpawnActor<ATileMap>();
	FarmTileMap->Create({72,52}, {55, 55});

	Player->SetTileMap(FarmTileMap);

	AFarmMap* GroundTileMap = GetWorld()->SpawnActor<AFarmMap>();
}

void AFarmGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	APlayer* Player = GetWorld()->GetPawn<APlayer>();
	Player->SetColImage("farm_col.png");

	TileChange();
	PutTile();

}


void AFarmGameMode::PutTile()
{
	APlayer* Player = GetWorld()->GetPawn<APlayer>();

	FVector2D PlayerLocation = Player->GetActorLocation();
	float TilePosX = PlayerLocation.X - FarmTileMap->GetActorLocation().X;
	float TilePosY = PlayerLocation.Y - FarmTileMap->GetActorLocation().Y + 53;
	FIntPoint Point = FarmTileMap->LocationToIndex({ TilePosX, TilePosY });

	FIntPoint HousePoint = FarmTileMap->LocationToIndex({ 2550, 500 });
	FarmTileMap->SetTileIndex("HouseTile", HousePoint, { -18, -20 }, { 361, 361 }, 0);

	if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON))
	{
		switch (static_cast<ETileImage>(TileImages))
		{
		case ETileImage::Dirt:
			FarmTileMap->SetTileLocation("Dirt.png", { PlayerLocation.X, PlayerLocation.Y + 10 }, 0);
			break;

		case ETileImage::Tree001:
			FarmTileMap->SetTileIndex("TreeTile", Point, { 0, -113 }, { 144, 240 }, 0, false);
			break;
		default:
			break;
		}
	}
}


void AFarmGameMode::TileChange()
{
	std::string TileImageName;

	switch (static_cast<ETileImage>(TileImages))
	{
	case ETileImage::Dirt:
		TileImageName = "Dirt";
		break;
	case ETileImage::Tree001:
		TileImageName = "Tree001";
		break;
	default:
		TileImageName = "Unknown";
		break;
	}

	UEngineDebug::CoreOutPutString("CurTile : " + TileImageName);

	if (true == UEngineInput::GetInst().IsDown(VK_RIGHT))
	{
		++TileImages;
		if (TileImages >= static_cast<int>(ETileImage::End))
		{
			TileImages = 0;
		}
		return;
	}

	if (true == UEngineInput::GetInst().IsDown(VK_LEFT))
	{
		--TileImages;
		if (TileImages < static_cast<int>(ETileImage::Dirt))
		{
			TileImages = 0;
		}
		return;
	}

}