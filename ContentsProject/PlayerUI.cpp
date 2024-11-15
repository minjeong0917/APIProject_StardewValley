#include "PreCompile.h"
#include "PlayerUI.h"
#include <EngineCore/EngineAPICore.h>
#include "ContentsEnum.h"
#include "Clock.h"
#include "Gold.h"
#include "Text.h"
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

    // slot
    FVector2D CameraPos = GetWorld()->GetCameraPos();
    //Slot_1->SetColisionLocation({ CameraPos.X + Size.Half().X - 311, CameraPos.Y + Size.Y - 81 });
    //Slot_2->SetColisionLocation({ CameraPos.X + Size.Half().X - 255, CameraPos.Y + Size.Y - 81 });
    //Slot_3->SetColisionLocation({ CameraPos.X + Size.Half().X - 199, CameraPos.Y + Size.Y - 81 });
    //Slot_4->SetColisionLocation({ CameraPos.X + Size.Half().X - 143, CameraPos.Y + Size.Y - 81 });
    //Slot_5->SetColisionLocation({ CameraPos.X + Size.Half().X - 87, CameraPos.Y + Size.Y - 81 });
    //Slot_6->SetColisionLocation({ CameraPos.X + Size.Half().X - 31, CameraPos.Y + Size.Y - 81 });
    //Slot_7->SetColisionLocation({ CameraPos.X + Size.Half().X + 25, CameraPos.Y + Size.Y - 81 });
    //Slot_8->SetColisionLocation({ CameraPos.X + Size.Half().X + 81, CameraPos.Y + Size.Y - 81 });
    //Slot_9->SetColisionLocation({ CameraPos.X + Size.Half().X + 137, CameraPos.Y + Size.Y - 81 });
    //Slot_10->SetColisionLocation({ CameraPos.X + Size.Half().X + 193, CameraPos.Y + Size.Y - 81 });
    //Slot_11->SetColisionLocation({ CameraPos.X + Size.Half().X + 249, CameraPos.Y + Size.Y - 81 });
    //Slot_12->SetColisionLocation({ CameraPos.X + Size.Half().X + 305, CameraPos.Y + Size.Y - 81 });
    

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

    FVector2D StartLocation = { Size.Half().iX() - 311, Size.iY() - 81 };
    FVector2D InterLocation = { 56.0f, 0.0f };

    // Slot
    for (size_t i = 0; i < 12; i++)
    {
        ASlot* Slot_1 = GetWorld()->SpawnActor<ASlot>();
        Slot_1->SetSprite("UI", 5);
        Slot_1->SetName("EmptySlot");
        Slot_1->SetComponentLocation(StartLocation + (InterLocation * i));
        AllSlots.push_back(Slot_1);
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

