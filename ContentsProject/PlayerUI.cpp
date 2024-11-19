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
    if (IsOpenIven == 0)
    {
        CurSlotItemSpawn();
    }

    // Inventory
    if (true == UEngineInput::GetInst().IsDown('E') && IsOpenIven == 1)
    {
        --IsOpenIven;
        Inventory->SetActive(false);
        InventoryBar->SetActive(true);
        for (int i = 0; i < 12; i++)
        {
            FVector2D Loc = AllSlots[0][i]->GetActorLocation();
            FVector2D Loc2 = AllSlots[0][i]->GetLocation() + AllSlots[0][i]->GetScale().Half();

            AllSlots[0][i]->SetActorLocation(Loc + FVector2D::DOWN * 347.0f);
            if (AllSlots[0][i]->GetText() != nullptr)
            {
                AllSlots[0][i]->SetTextLocation(Loc2);
            }
        }
        for (size_t y = 1; y < 3; y++)
        {
            for (float i = 0; i < 12; i++)
            {
                AllSlots[y][i]->SetActive(false);
            }
        }
        CurItem->SetActive(true);
        CurSlot->SetActive(true);

    }
    else if (true == UEngineInput::GetInst().IsDown('E'))
    {

        Inventory->SetActive(true);

        ++IsOpenIven;
        InventoryBar->SetActive(false);
        for (int i = 0; i < 12; i++)
        {

            FVector2D Loc = AllSlots[0][i]->GetActorLocation();
            FVector2D Loc2 = AllSlots[0][i]->GetLocation() + AllSlots[0][i]->GetScale().Half();

            AllSlots[0][i]->SetActorLocation(Loc + FVector2D::UP * 347.0f);
            if (AllSlots[0][i]->GetText() != nullptr)
            {
               AllSlots[0][i]->SetTextLocation(Loc2 + FVector2D::UP * 347.0f);
            }
        }

        for (size_t y = 1; y < 3; y++)
        {
            for (float i = 0; i < 12; i++)
            {
                AllSlots[y][i]->SetActive(true);
            }
        }

        CurItem->SetActive(false);
        CurSlot->SetActive(false);

    }

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

    AllSlots.resize(3);

    // Slot

    for (float i = 0; i < 12; i++)
    {
        ASlot* Slot = GetWorld()->SpawnActor<ASlot>();
        // Slot->SetSprite("UI", 6);
        Slot->SetName("EmptySlot");
        Slot->SetScale(FVector2D{ 16 * 3.5f, 16 * 3.5f });
        Slot->SaveItemInfo("UI", 6, FVector2D{ 16 * 3.5f, 16 * 3.5f });
        Slot->SetComponentLocation(StartLocation + (InterLocation * i));
        AllSlots[0].push_back(Slot);
    }

    StartLocation = { Size.Half().iX() - 311, Size.Half().iY() - 50 };

    for (size_t y = 1; y < 3; y++)
    {
        for (float i = 0; i < 12; i++)
        {
            ASlot* Slot = GetWorld()->SpawnActor<ASlot>();
            //Slot->SetSprite("UI", 6);
            Slot->SetName("EmptySlot");
            Slot->SetScale(FVector2D{ 16 * 3.5f, 16 * 3.5f });
            Slot->SaveItemInfo("UI", 6, FVector2D{ 16 * 3.5f, 16 * 3.5f });
            FVector2D Location = { 0, 60 };
            Slot->SetComponentLocation(StartLocation + (InterLocation * i) + (Location * y));
            Slot->SetActive(false);
            AllSlots[y].push_back(Slot);
        }
    }




    // 기본 아이템 지급
    DefaultItem({ 0,0 }, "Tools.png", "Hoe", 26, { 14 * 3.5f, 30 * 3.5f }, { 0,25 });
    DefaultItem({ 0,1 }, "Items.png", "Seeds", 624, { 14 * 3.5f, 14 * 3.5f });


    // CulSlot
    CurSlot = GetWorld()->SpawnActor<ASlot>();
    CurSlot->SetSprite("UI", 5);
    CurSlot->SetOrder(ERenderOrder::CURSLOT);
    CurSlot->SetScale(FVector2D{ 16 * 3.5f, 16 * 3.5f });
    CurSlot->SetComponentLocation(AllSlots[0][CurSlotNum]->GetLocation());

    CurItem = GetWorld()->SpawnActor<ACurItem>();

    // Inventory
    Inventory = GetWorld()->SpawnActor<AInventory>();
    Inventory->SetActorLocation({ Size.Half().iX()+1, Size.Half().iY() });
    Inventory->SetActive(false);

}

void APlayerUI::DefaultItem(FIntPoint _SlotIndex, std::string _SpriteName, std::string _ItemName, int _ItemIndex, FVector2D _Scale, FVector2D _Location)
{
    FVector2D DefaultLocation = AllSlots[_SlotIndex.X][_SlotIndex.Y]->GetActorLocation();
    AllSlots[_SlotIndex.X][_SlotIndex.Y]->SetSprite(_SpriteName, _ItemIndex);
    AllSlots[_SlotIndex.X][_SlotIndex.Y]->SetName(_ItemName);
    AllSlots[_SlotIndex.X][_SlotIndex.Y]->SetActorLocation(DefaultLocation + _Location);
    AllSlots[_SlotIndex.X][_SlotIndex.Y]->SetScale(_Scale);
    AllSlots[_SlotIndex.X][_SlotIndex.Y]->SaveItemInfo(_SpriteName, _ItemIndex, _Scale);
}


void APlayerUI::AddItem(AItem* _Item)
{
    bool IsOver = _Item->ItemTypeCheck(_Item->GetItemType());
    _Item->Destroy();
    SlotCheck(_Item, _Item->GetItemName(), _Item->GetItemSpriteName(), _Item->GetItemIndex(), IsOver);
}

void APlayerUI::SlotCheck(AItem* _Item, std::string _ItemName ,std::string _SpriteName, int _Index, bool IsOver)
{
    FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

    for (size_t i = 0; i < AllSlots.size(); i++)
    {
        std::string SlotSpriteName = AllSlots[0][i]->GetName();
        FVector2D Location = AllSlots[0][i]->GetActorLocation();
        if (SlotSpriteName != "EmptySlot")
        {
            IsEmptySlot = false;
        }
        else if (SlotSpriteName == "EmptySlot")
        {
            IsEmptySlot = true;
        }

        int CurItemCount = AllSlots[0][i]->GetSlotItemCount();

        if (true == IsEmptySlot)
        {
            //_Item = GetWorld()->SpawnActor<AItem>();
            //_Item->SetSprite(_SpriteName, _Index, 3.0f);
            //_Item->SetCameraEffect(false);
            //_Item->SetActorLocation(AllSlots[i]->GetLocation());
            //_Item->SetOrder(ERenderOrder::SLOTITEM);
            //AllSlots[i]->SaveItemInfo(_SpriteName, _Index, { 14 * 3.5f, 14 * 3.5f });
            AllSlots[0][i]->SetName(_ItemName);
            AllSlots[0][i]->SetActorLocation(Location);
            AllSlots[0][i]->SetSprite(_SpriteName, _Index);
            AllSlots[0][i]->SetScale({ 14 * 3.5f, 14 * 3.5f });

            AllSlots[0][i]->SaveItemInfo(_SpriteName, _Index, { 14 * 3.5f, 14 * 3.5f });


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
                AllSlots[0][i]->SetSlotItemCount(CurItemCount);


                if (nullptr != AllSlots[0][i]->GetText())
                {
                    AllSlots[0][i]->GetText()->Destroy();
                }

                AllSlots[0][i]->CountText();

                return;

            }
            else if (false == IsOver)
            {

                AllSlots[0][i]->SetSlotItemCount(CurItemCount);
                return;

            }
        }
    }
}

std::string APlayerUI::CurSlotItemName()
{
    std::string CurSlotSpriteName = AllSlots[0][CurSlotNum]->GetName();
    return CurSlotSpriteName;
}



void APlayerUI::CurSlotItemSpawn()
{
    std::string ItemName = AllSlots[0][CurSlotNum]->GetName();
    APlayer* Player = GetWorld()->GetPawn<APlayer>();

    EItemType ItemType = CurItem->SetItemType(ItemName);
    TypeCheck = CurItem->ItemTypeCheck(ItemType);

    if (ItemName != "EmptySlot" && true == TypeCheck)
    {
        CurItem->SetActive(true);

        std::string SpriteName = AllSlots[0][CurSlotNum]->GetItemSpriteName();
        int Index = AllSlots[0][CurSlotNum]->GetItemIndex();

        CurItem->SetSprite(SpriteName, Index, 3.0f);
        CurItem->SetActorLocation({ Player->GetActorLocation().X,Player->GetActorLocation().Y - 90 });
    }
    else if (ItemName == "EmptySlot" || false == TypeCheck)
    {
        CurItem->SetActive(false);

    }

}


void APlayerUI::SetCurSlot()
{
    int Key = '1';

    for (size_t i = 0; i < 9; i++)
    {
        if (true == UEngineInput::GetInst().IsDown(i + Key))
        {
            CurSlotNum = i;
            CurSlot->SetComponentLocation(AllSlots[0][i]->GetLocation());
            return;
        }
    }

    if (true == UEngineInput::GetInst().IsDown('0'))
    {
        CurSlotNum = 9;
        CurSlot->SetComponentLocation(AllSlots[0][9]->GetLocation());
    }
    if (true == UEngineInput::GetInst().IsDown(VK_OEM_MINUS))
    {
        CurSlotNum = 10;
        CurSlot->SetComponentLocation(AllSlots[0][10]->GetLocation());
    }
    if (true == UEngineInput::GetInst().IsDown(VK_OEM_PLUS))
    {
        CurSlotNum = 11;
        CurSlot->SetComponentLocation(AllSlots[0][11]->GetLocation());
    }
}
