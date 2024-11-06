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
	FarmTileMap->Create({72,52}, {50, 50});

	//TreeTileMap = GetWorld()->SpawnActor<ATileMap>();
	//TreeTileMap->Create("TreeTile", { 36, 22 }, { 100, 140 });

	AFarmMap* GroundTileMap = GetWorld()->SpawnActor<AFarmMap>();
}

void AFarmGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	APlayer* Player = GetWorld()->GetPawn<APlayer>();
	Player->SetColImage("farm_col.png");
	FVector2D PlayerLocation = Player->GetActorLocation();

	FVector2D PlayerLoctaionToTilePos = PlayerLocation - FarmTileMap->GetActorLocation();
	FIntPoint Point = FarmTileMap->LocationToIndex(PlayerLoctaionToTilePos);

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

	UEngineDebug::CoreOutPutString("CurTileMap : " + TileImageName);

	if (true == UEngineInput::GetInst().IsDown(VK_RBUTTON))
	{
		++TileImages;
		if (TileImages > static_cast<int>(ETileImage::Tree001))
		{
			TileImages = 0;
		}
		return;
	}

	if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON))
	{
		switch (static_cast<ETileImage>(TileImages))
		{
		case ETileImage::Dirt:
			FarmTileMap->SetTileLocation("Dirt.png", {PlayerLocation.X, PlayerLocation.Y + 10}, 0);
			
			break;
		case ETileImage::Tree001:
			FarmTileMap->SetTileIndex("TreeTile", Point, {0, -110}, {144, 240}, 1);
		
			break;
		default:
			break;
		}
	}




}