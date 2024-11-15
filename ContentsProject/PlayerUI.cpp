#include "PreCompile.h"
#include "PlayerUI.h"
#include <EngineCore/EngineAPICore.h>

#include "Clock.h"
#include "Gold.h"
#include "Text.h"
#include "Item.h"

APlayerUI::APlayerUI()
{
}

APlayerUI::~APlayerUI()
{
}

void APlayerUI::BeginPlay()
{
    UIImageRender();
}

void APlayerUI::Tick(float _DeltaTime)
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


void APlayerUI::UIImageRender()
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
    Slot_1->SetName("EmptySlot");
    Slot_1->SetComponentLocation({ Size.Half().iX() - 311, Size.iY() - 81 });
    AllSlots.push_back(Slot_1);

    ASlot* Slot_2 = GetWorld()->SpawnActor<ASlot>();
    Slot_2->SetSprite("UI", 5);
    Slot_2->SetName("EmptySlot");
    Slot_2->SetActorLocation({ Size.Half().iX() - 255, Size.iY() - 81 });
    AllSlots.push_back(Slot_2);
}


void APlayerUI::SlotCheck(std::string _SpriteName, int _Index)
{
    for (size_t i = 0; i < AllSlots.size(); i++)
    {
        std::string SlotSpriteName = AllSlots[i]->GetName();
        if (SlotSpriteName != "EmptySlot")
        {
            IsEmptySlot = false;
        }
        else if (SlotSpriteName == "EmptySlot")
        {
            IsEmptySlot = true;
        }

        if (true == IsEmptySlot)
        {
            AllSlots[i]->SetSprite(_SpriteName, _Index);
            AllSlots[i]->SetName(_SpriteName);
            AllSlots[i]->SetActorLocation(AllSlots[i]->GetActorLocation());
            AllSlots[i]->SetScale({ 14 * 3.5f, 14 * 3.5f });
            break;
        }
    }
}
