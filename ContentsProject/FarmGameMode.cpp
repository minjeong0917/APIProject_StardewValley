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


	DirtTileMap = GetWorld()->SpawnActor<ATileMap>();
	DirtTileMap->Create("Dirt.png", {72,52}, {50, 50 });

	TreeTileMap = GetWorld()->SpawnActor<ATileMap>();
	TreeTileMap->Create("TreeTile", { 25, 22 }, { 144, 140 });

	//ColTreeTileMap = GetWorld()->SpawnActor<ATileMap>();
	//ColTreeTileMap->Create("TreeTile", { 25, 22 }, { 144, 140 });

	AFarmMap* GroundTileMap = GetWorld()->SpawnActor<AFarmMap>();


}

void AFarmGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	APlayer* Player = GetWorld()->GetPawn<APlayer>();
	FVector2D PlayerLocation = Player->GetActorLocation();

	FVector2D PlayerLoctaionToTilePos = PlayerLocation - TreeTileMap->GetActorLocation();
	FIntPoint Point = TreeTileMap->LocationToIndex(PlayerLoctaionToTilePos);

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
			DirtTileMap->SetTileLocation({ PlayerLocation.X, PlayerLocation.Y + 10 }, 0);
			
			break;
		case ETileImage::Tree001:
			TreeTileMap->SetTileIndex(Point, { 0, -180 }, { 144, 240 }, 1);
			/*ColTreeTileMap->SetTileIndex(Point, { 0, -180 }, { 144, 240 }, 1);*/
			break;
		default:
			break;
		}
	}




}