#include "PreCompile.h"
#include "FarmGameMode.h"

#include <EngineCore/Level.h>

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>

#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>

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

	DirtTileMap->Create("Dirt.png", {50,40}, { 64, 64 });
	
	AFarmMap* GroundTileMap = GetWorld()->SpawnActor<AFarmMap>();
}

void AFarmGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	APlayer* Player = GetWorld()->GetPawn<APlayer>();
	if (true == UEngineInput::GetInst().IsPress(VK_LBUTTON))
	{
		DirtTileMap->SetTileLocation(Player->GetActorLocation(), 0);
	}

}