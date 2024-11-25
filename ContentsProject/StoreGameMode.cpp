#include "PreCompile.h"

#include "StoreGameMode.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/Level.h>

#include "StoreMap.h"
#include "Player.h"

AStoreGameMode::AStoreGameMode()
{
}

AStoreGameMode::~AStoreGameMode()
{
}

void AStoreGameMode::BeginPlay()
{
	APlayer* Player = GetWorld()->GetPawn<APlayer>();
	Player->SetBackImage("Store.png");

	AStoreMap* StoreMap = GetWorld()->SpawnActor<AStoreMap>();

	Player->SetActorLocation({ 400, /*1800*/1300 });

	StoreTileMap = GetWorld()->SpawnActor<ATileMap>();
	StoreTileMap->Create({ 39,30 }, { 388, 70 });

	FIntPoint CounterPoint1 = StoreTileMap->LocationToIndex({ 350, 1150 });
	StoreTileMap->SetTileIndex("Counter.png", CounterPoint1, { 192, -43 }, { 388.f, 200.f }, 0);
	FIntPoint CounterPoint2 = StoreTileMap->LocationToIndex({ 390, 1150 });

	StoreTileMap->SetTileIndex("Counter.png", CounterPoint2, { -195, -43 }, { 388.f, 200.f }, 0);

}


void AStoreGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	APlayer* Player = GetWorld()->GetPawn<APlayer>();
	Player->SetColImage("Store_col.png");
	FVector2D CameraPos = GetWorld()->GetCameraPos();
	FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
	FVector2D MouseLocation = MousePos + CameraPos;

	if (true == UEngineInput::GetInst().IsDown(VK_RBUTTON))
	{
		if (GetStoreTileSpriteName(MouseLocation) == "COUNTER.PNG" && Player->IsMouseInPlayerPos == true)
		{

			IsOpenCounter = true;

		}
	}

	if (true == UEngineInput::GetInst().IsUp(VK_RBUTTON))
	{
		IsOpenCounter = false;
	}
}

std::string AStoreGameMode::GetStoreTileSpriteName(FVector2D Location)
{
	Tile* TileRef = StoreTileMap->GetTileRef(Location);
	if (TileRef)
	{
		std::string SpriteName = TileRef->GetSpriteName();

		return SpriteName;
	}
	else
	{
		return "NONE";

	}

}


