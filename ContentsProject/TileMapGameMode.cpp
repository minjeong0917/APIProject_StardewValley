#include "PreCompile.h"
#include "TileMapGameMode.h"
#include <EngineCore/Level.h>

ATileMapGameMode::ATileMapGameMode()
{
}

ATileMapGameMode::~ATileMapGameMode()
{
}

// Ÿ����� ������ �� �ִ� ����
void ATileMapGameMode::BeginPlay()
{
	Super::BeginPlay();

	GroundTileMap = GetWorld()->SpawnActor<ATileMap>();

	GroundTileMap->Create("TileSet", { 100, 100 }, { 32, 32 });

}

void ATileMapGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}
