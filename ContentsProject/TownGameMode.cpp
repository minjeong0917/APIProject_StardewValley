#include "PreCompile.h"

#include "TownGameMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>

#include "TownMap.h"
#include "Player.h"
#include "Clock.h"
#include "Gold.h"

ATownGameMode::ATownGameMode()
{
}

ATownGameMode::~ATownGameMode()
{
}

void ATownGameMode::BeginPlay()
{


	APlayer* Player = GetWorld()->GetPawn<APlayer>();
	Player->SetBackImage("PelicanTown.png");

	ATownMap* Town = GetWorld()->SpawnActor<ATownMap>();

	Player->SetActorLocation({ 80, 2700});

}


void ATownGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	APlayer* Player = GetWorld()->GetPawn<APlayer>();
	Player->SetColImage("PelicanTown_col.png");

	if (true == UEngineInput::GetInst().IsDown('T'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Farm");
	}
	if (true == UEngineInput::GetInst().IsDown('K'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Store");
	}
}

void ATownGameMode::UIImageRender()
{
	APlayer* Player = GetWorld()->GetPawn<APlayer>();
	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

}
