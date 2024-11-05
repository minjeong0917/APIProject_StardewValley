#include "PreCompile.h"
#include "TileMapGameMode.h"
#include <EngineCore/Level.h>

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>

ATileMapGameMode::ATileMapGameMode()
{
}

ATileMapGameMode::~ATileMapGameMode()
{
}

// 타일찍고 저장할 수 있는 레벨
void ATileMapGameMode::BeginPlay()
{
	Super::BeginPlay();

	{
		GroundTileMap = GetWorld()->SpawnActor<ATileMap>();

		GroundTileMap->Create("TileSet", { 100, 100 }, { 32, 32 });

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				GroundTileMap->SetTileIndex({ y,x }, 0);
			}
		}
	}

	{
		WallTileMap = GetWorld()->SpawnActor<ATileMap>();
		WallTileMap->Create("TileSet", { 100, 100 }, { 32, 32 });

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				WallTileMap->SetTileIndex({ y,x }, { 0, -6 }, { 32, 44 }, 2);
			}
		}
	}
}


void ATileMapGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsPress(VK_LBUTTON))
	{
		FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
		GroundTileMap->SetTileLocation(MousePos, 1);
	}

	if (true == UEngineInput::GetInst().IsPress(VK_RBUTTON))
	{
		//FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
		//GroundTileMap->SetTileLocation(MousePos, 1);
	}

}
