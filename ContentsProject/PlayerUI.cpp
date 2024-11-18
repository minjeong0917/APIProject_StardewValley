#include "PreCompile.h"
#include "PlayerUI.h"
#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineInput.h>

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

    SetCurSlot();
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
    for (float i = 0; i < 12; i++)
    {
        ASlot* Slot = GetWorld()->SpawnActor<ASlot>();
        Slot->SetSprite("UI", 6);
        Slot->SetName("EmptySlot");
        Slot->SetComponentLocation(StartLocation + (InterLocation * i));
        AllSlots.push_back(Slot);
    }

    AllSlots[0]->SetSprite("Tools.png", 26);
    AllSlots[0]->SetName("Hoe");
    AllSlots[0]->SetActorLocation({ AllSlots[0]->GetActorLocation().X, AllSlots[0]->GetActorLocation().Y + 25 });
    AllSlots[0]->SetScale({ 14 * 3.5f, 28 * 3.5f });

    AllSlots[1]->SetSprite("Items.png", 624);
    AllSlots[1]->SetName("Seeds");
    AllSlots[1]->SetActorLocation(AllSlots[1]->GetActorLocation());
    AllSlots[1]->SetScale({ 14 * 3.5f, 14 * 3.5f });

    // CulSlot
    CurSlot = GetWorld()->SpawnActor<ASlot>();
    CurSlot->SetSprite("UI", 5);
    CurSlot->SetOrder(ERenderOrder::CURSLOT);
    CurSlot->SetScale(FVector2D{ 16 * 3.5f, 16 * 3.5f });
    CurSlot->SetComponentLocation(AllSlots[CurSlotNum]->GetLocation());
}



void APlayerUI::AddItem(AItem* _Item)
{
    bool IsOver = _Item->ItemTypeCheck(_Item->GetItemType());
    _Item->Destroy();
    SlotCheck(_Item, _Item->GetItemName(),_Item->GetItemSpriteName(), _Item->GetItemIndex(), IsOver);

}


void APlayerUI::SlotCheck(AItem* _Item, std::string _ItemName ,std::string _SpriteName, int _Index, bool IsOver)
{
    FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

    for (size_t i = 0; i < AllSlots.size(); i++)
    {
        std::string SlotSpriteName = AllSlots[i]->GetName();
        FVector2D Location = AllSlots[i]->GetActorLocation();
        if (SlotSpriteName != "EmptySlot")
        {
            IsEmptySlot = false;
        }
        else if (SlotSpriteName == "EmptySlot")
        {
            IsEmptySlot = true;
        }

        int CurItemCount = AllSlots[i]->GetSlotItemCount();

        if (true == IsEmptySlot)
        {
            AllSlots[i]->SetSprite(_SpriteName, _Index);
            AllSlots[i]->SetName(_ItemName);
            AllSlots[i]->SetActorLocation(Location);
            AllSlots[i]->SetScale({ 14 * 3.5f, 14 * 3.5f });
            AllSlots[i]->ItemInfoSave(_Item);
            break;
        }
        else if (false == IsEmptySlot && SlotSpriteName != _ItemName)
        {
            continue;
        }
        else if (SlotSpriteName == _ItemName)
        {
            if (true == IsOver)
            {
                ++CurItemCount;
                AllSlots[i]->SetSlotItemCount(CurItemCount);


                if (nullptr != AllSlots[i]->GetText())
                {
                    AllSlots[i]->GetText()->Destroy();
                }

                AllSlots[i]->CountText();

                return;

            }
            else if (false == IsOver)
            {

                AllSlots[i]->SetSlotItemCount(CurItemCount);
                return;

            }

        }

    }
}

std::string APlayerUI::CurSlotItemName()
{
    std::string CurSlotSpriteName = AllSlots[CurSlotNum]->GetName();
    return CurSlotSpriteName;
}

bool APlayerUI::CurSlotItemTypeCheck()
{
    bool check = AllSlots[CurSlotNum]->GetItemTypeCheck();
    return check;
}

void APlayerUI::CurSlotItemSpawn()
{
    std::string SpriteName = AllSlots[CurSlotNum]->GetItemSpriteName();
    int Index = AllSlots[CurSlotNum]->GetItemIndex();

    AItem* Item = GetWorld()->SpawnActor<AItem>();
    Item->SetSprite(SpriteName, Index, 1.0f);
}


void APlayerUI::SetCurSlot()
{
    if (true == UEngineInput::GetInst().IsDown('1'))
    {
        CurSlotNum = 0;
        CurSlot->SetComponentLocation(AllSlots[0]->GetLocation());
        return;
    }
    else if (true == UEngineInput::GetInst().IsDown('2'))
    {
        CurSlotNum = 1;
        CurSlot->SetComponentLocation(AllSlots[1]->GetLocation());
    }
    else if (true == UEngineInput::GetInst().IsDown('3'))
    {
        CurSlotNum = 2;
        CurSlot->SetComponentLocation(AllSlots[2]->GetLocation());
    }
    else if (true == UEngineInput::GetInst().IsDown('4'))
    {
        CurSlotNum = 3;
        CurSlot->SetComponentLocation(AllSlots[3]->GetLocation());
    }
    else if (true == UEngineInput::GetInst().IsDown('5'))
    {
        CurSlotNum = 4;
        CurSlot->SetComponentLocation(AllSlots[4]->GetLocation());
    }
    else if (true == UEngineInput::GetInst().IsDown('6'))
    {
        CurSlotNum = 5;
        CurSlot->SetComponentLocation(AllSlots[5]->GetLocation());
    }
    else if (true == UEngineInput::GetInst().IsDown('7'))
    {
        CurSlotNum = 6;
        CurSlot->SetComponentLocation(AllSlots[6]->GetLocation());
    }
    else if (true == UEngineInput::GetInst().IsDown('8'))
    {
        CurSlotNum = 7;
        CurSlot->SetComponentLocation(AllSlots[7]->GetLocation());
    }
    else if (true == UEngineInput::GetInst().IsDown('9'))
    {
        CurSlotNum = 8;
        CurSlot->SetComponentLocation(AllSlots[8]->GetLocation());
    }
    else if (true == UEngineInput::GetInst().IsDown('0'))
    {
        CurSlotNum = 9;
        CurSlot->SetComponentLocation(AllSlots[9]->GetLocation());
    }
    else if (true == UEngineInput::GetInst().IsDown(VK_OEM_MINUS))
    {
        CurSlotNum = 10;
        CurSlot->SetComponentLocation(AllSlots[10]->GetLocation());
    }
    else if (true == UEngineInput::GetInst().IsDown(VK_OEM_PLUS))
    {
        CurSlotNum = 11;
        CurSlot->SetComponentLocation(AllSlots[11]->GetLocation());
    }
}
