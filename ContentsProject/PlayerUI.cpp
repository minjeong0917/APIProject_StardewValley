#include "PreCompile.h"
#include "PlayerUI.h"
#include <EngineCore/EngineAPICore.h>
#include "ContentsEnum.h"
#include "Clock.h"


#include "Item.h"
#include "FarmGameMode.h"

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
    APlayer* Player = GetWorld()->GetPawn<APlayer>();

    // cursor
    Cursor->SetActorLocation({ MousePos.X + 10, MousePos.Y + 15 });

    // time
    int Min = MinTime->SetMinute(_DeltaTime);
    HourTime->SetHour(Min);

    bool IsAM = HourTime->AMCheck(Min);
    if (true == IsAM)
    {
        APText->SetSprite("apm.png", 1, 1.0f);
        APText->SetActorLocation({ Size.iX() - 80, 145 });
    }
    else if (false == IsAM)
    {
        APText->SetSprite("apm.png", 2, 1.0f);
        APText->SetActorLocation({ Size.iX() - 80, 145 });
    }

    int Week = HourTime->WeekCheck(Min);
    WeekText->SetSprite("Week.png", Week, 1.0f);
    WeekText->SetActorLocation({ Size.iX() - 140, 50 });

    int Day = HourTime->DayCheck(Min);

    DayText->SetActorLocation({ Size.iX() - 70 , 50 });
    DayText->SetTextSpriteName("Time.png");
    DayText->SetOrder(ERenderOrder::UIFont);
    DayText->SetTextScale({ 20, 28 });
    DayText->SetValue(Day);
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
    Text->SetActorLocation({ Size.iX() - 140, 138 });

    AText* MText = GetWorld()->SpawnActor<AText>();
    MText->SetSprite("apm.png", 3, 1.0f);
    MText->SetActorLocation({ Size.iX() - 50, 145 });

    APText = GetWorld()->SpawnActor<AText>();
    WeekText = GetWorld()->SpawnActor<AText>();
    DayText = GetWorld()->SpawnActor<AGold>();


    // Cursor
    Cursor = GetWorld()->SpawnActor<ACursor>();

    // Time
    MinTime = GetWorld()->SpawnActor<ATime>();
    MinTime->SetActorLocation({ Size.iX() - 108 , 138 });
    MinTime->SetTextSpriteName("Time.png");

    HourTime = GetWorld()->SpawnActor<ATime>();
    HourTime->SetActorLocation({ Size.iX() - 155 , 138 });
    HourTime->SetTextSpriteName("Time.png");

    // InventoryBar
    InventoryBar = GetWorld()->SpawnActor<AInventoryBar>();
    InventoryBar->SetActorLocation({ Size.Half().iX(), Size.iY() - 80 });

    FVector2D StartLocation = { Size.Half().iX() - 311, Size.iY() - 81 };
    FVector2D InterLocation = { 56.0f, 0.0f };

    // Slot
    for (size_t i = 0; i < 12; i++)
    {
        ASlot* Slot = GetWorld()->SpawnActor<ASlot>();
        Slot->SetSprite("UI", 5);
        Slot->SetName("EmptySlot");
        Slot->SetComponentLocation(StartLocation + (InterLocation * i));
        AllSlots.push_back(Slot);
    }
}



void APlayerUI::AddItem(AItem* _Item)
{
    _Item->Destroy();
}


//void APlayerUI::SlotCheck(std::string _SpriteName, int _Index)
//{
//    for (size_t i = 0; i < AllSlots.size(); i++)
//    {
//        std::string SlotSpriteName = AllSlots[i]->GetName();
//        if (SlotSpriteName != "EmptySlot")
//        {
//            IsEmptySlot = false;
//        }
//        else if (SlotSpriteName == "EmptySlot")
//        {
//            IsEmptySlot = true;
//        }
//
//        int CurItemCount = AllSlots[i]->GetSlotItemCount();
//
//        if (true == IsEmptySlot)
//        {
//            AllSlots[i]->SetSprite(_SpriteName, _Index);
//            AllSlots[i]->SetName(_SpriteName);
//            AllSlots[i]->SetActorLocation(AllSlots[i]->GetActorLocation());
//            AllSlots[i]->SetScale({ 14 * 3.5f, 14 * 3.5f });
//            break;
//        }
//        else if (SlotSpriteName == AllSlots[i]->GetName())
//        {
//            ++CurItemCount;
//            AllSlots[i]->SetSlotItemCount(CurItemCount);
//        }
//
//        //if (SlotSpriteName != "EmptySlot")
//        //{
//        //    AText* Text = GetWorld()->SpawnActor<AText>();
//        //    Text->SetActorLocation(AllSlots[i]->GetActorLocation());
//        //    Text->SetTextSpriteName("Item.png");
//        //    Text->SetOrder(ERenderOrder::UIFont);
//        //    Text->SetTextScale({ 13, 15 });
//        //    Text->SetValue(CurItemCount);
//        //}
//
//
//    }
//}

