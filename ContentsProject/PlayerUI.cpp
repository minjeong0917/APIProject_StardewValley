#include "PreCompile.h"
#include "PlayerUI.h"
#include <EngineCore/EngineAPICore.h>

#include "Clock.h"
#include "Gold.h"
#include "Text.h"
#include "Item.h"

PlayerUI::PlayerUI()
{
}

PlayerUI::~PlayerUI()
{
}

void PlayerUI::BeginPlay()
{
    UIImageRender();
}

void PlayerUI::Tick(float _DeltaTime)
{
    Super::Tick(_DeltaTime);
    FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
    FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

    // cursor
    Cursor->SetActorLocation({ MousePos.X + 10, MousePos.Y + 15 });

    // time
    int Min = MinTime->SetMinute(_DeltaTime);
    HourTime->SetHour(Min);

    // slot
    FVector2D CameraPos = GetWorld()->GetCameraPos();
    Slot_1->SetColisionLocation({ CameraPos.X + Size.Half().X - 311, CameraPos.Y + Size.Y - 81 });
}


void PlayerUI::UIImageRender()
{

    FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
    APlayer* Player = GetWorld()->GetPawn<APlayer>();


    // Clock
    AClock* Clock = GetWorld()->SpawnActor<AClock>();
    Clock->SetActorLocation({ Size.iX() - 154, 128 });

    // Gold
    AGold* Gold = GetWorld()->SpawnActor<AGold>();

    Gold->SetActorLocation({ Size.iX() - 54 , 218 });
    Gold->SetTextSpriteName("Gold3.png");
    Gold->SetOrder(ERenderOrder::UIFont);
    Gold->SetTextScale({ 22, 33 });
    Gold->SetValue(Player->GetGold());

    // Text
    AText* Text = GetWorld()->SpawnActor<AText>();
    Text->SetSprite("apm.png", 0, 1.0f);
    Text->SetActorLocation({ Size.iX() - 130, 138 });

    // Cursor
    Cursor = GetWorld()->SpawnActor<ACursor>();

    // Time
    MinTime = GetWorld()->SpawnActor<ATime>();
    MinTime->SetActorLocation({ Size.iX() - 98 , 138 });
    MinTime->SetTextSpriteName("Time.png");

    HourTime = GetWorld()->SpawnActor<ATime>();
    HourTime->SetActorLocation({ Size.iX() - 145 , 138 });
    HourTime->SetTextSpriteName("Time.png");

    // InventoryBar
    InventoryBar = GetWorld()->SpawnActor<AInventoryBar>();
    InventoryBar->SetActorLocation({ Size.Half().iX(), Size.iY() - 80 });

    // Slot
    Slot_1 = GetWorld()->SpawnActor<ASlot>();
    Slot_1->SetSprite("UI", 5);
    Slot_1->SetComponentLocation({ Size.Half().iX() - 311, Size.iY() - 81 });

}
