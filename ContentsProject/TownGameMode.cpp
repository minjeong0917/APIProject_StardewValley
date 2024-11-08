#include "PreCompile.h"

#include "TownGameMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>

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
	Super::BeginPlay();

	APlayer* Player = GetWorld()->GetPawn<APlayer>();
	Player->SetBackImage("PelicanTown.png");

	ATownMap* Town = GetWorld()->SpawnActor<ATownMap>();

	AClock* Clock = GetWorld()->SpawnActor<AClock>();
	AGold* Gold = GetWorld()->SpawnActor<AGold>();

	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();


	Gold->SetActorLocation({ Size.iX() - 41 , 166 });
	Gold->SetTextSpriteName("Gold2.png");
	Gold->SetOrder(ERenderOrder::UIFont);
	Gold->SetTextScale({ 18, 24 });

	Gold->SetValue(Player->GetGold());

}


void ATownGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('T'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Farm");
	}
}