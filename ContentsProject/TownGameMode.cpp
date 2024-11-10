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

	Player->SetActorLocation({ 80,2180});
	UIImageRender();

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
}

void ATownGameMode::UIImageRender()
{
	APlayer* Player = GetWorld()->GetPawn<APlayer>();
	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

	// Clock
	AClock* Clock = GetWorld()->SpawnActor<AClock>();

	// Gold
	AGold* Gold = GetWorld()->SpawnActor<AGold>();

	Gold->SetActorLocation({ Size.iX() - 41 , 166 });
	Gold->SetTextSpriteName("Gold3.png");
	Gold->SetOrder(ERenderOrder::UIFont);
	Gold->SetTextScale({ 18, 24 });

	Gold->SetValue(Player->GetGold());
}
