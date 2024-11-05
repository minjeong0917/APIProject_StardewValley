#include "PreCompile.h"
#include "FarmGameMode.h"

#include <EngineCore/Level.h>

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>

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

	DirtTileMap = GetWorld()->SpawnActor<ATileMap>();
	DirtTileMap->Create("Dirt.png", {72,52}, {50, 50 });

	TreeTileMap = GetWorld()->SpawnActor<ATileMap>();
	TreeTileMap->Create("Tree001.png", { 34,16 }, { 96, 160 });

	AFarmMap* GroundTileMap = GetWorld()->SpawnActor<AFarmMap>();
}

void AFarmGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	APlayer* Player = GetWorld()->GetPawn<APlayer>();

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

			DirtTileMap->SetTileLocation(Player->GetActorLocation(), 0);

			break;
		case ETileImage::Tree001:

			TreeTileMap->SetTileLocation(Player->GetActorLocation(), 0);
			break;
		default:
			break;
		}
	}



}