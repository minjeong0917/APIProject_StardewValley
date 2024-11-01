#include "PreCompile.h"

#include "TownGameMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>

#include "TownMap.h"

ATownGameMode::ATownGameMode()
{
}

ATownGameMode::~ATownGameMode()
{
}

void ATownGameMode::BeginPlay()
{
	Super::BeginPlay();
	ATownMap* Town = GetWorld()->SpawnActor<ATownMap>();

}


void ATownGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('T'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Farm");
	}
}