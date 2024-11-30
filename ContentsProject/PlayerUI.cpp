#include "PreCompile.h"
#include "PlayerUI.h"
#include <EngineCore/EngineAPICore.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineCoreDebug.h>

#include "ContentsEnum.h"
#include "Clock.h"

#include "Item.h"
#include "FarmGameMode.h"
#include "StoreGameMode.h"
#include "HouseGameMode.h"
#include "PlayerManager.h"

std::string APlayerUI::Text2Explain;
std::string APlayerUI::Text3Explain;

APlayerUI::APlayerUI()
{
}

APlayerUI::~APlayerUI()
{
}

void APlayerUI::BeginPlay()
{
    Super::BeginPlay();

    UIImageRender();

}



void APlayerUI::UIImageRender()
{
    FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
    APlayer* Player = GetWorld()->GetPawn<APlayer>();

    // Clock
    AClock* Clock = GetWorld()->SpawnActor<AClock>();
    Clock->SetActorLocation({ Size.iX() - 154, 128 });

    ClockHand = GetWorld()->SpawnActor<AUI>();
    ClockHand->SetActorLocation({ Size.iX() - 154, 128 });


    // Gold
    Gold = GetWorld()->SpawnActor<AGold>();
    Gold->SetActorLocation({ Size.iX() - 54 , 218 });
    Gold->SetTextSpriteName("Gold3.png");
    Gold->SetOrder(ERenderOrder::UIFont);
    Gold->SetTextScale({ 22, 33 });

    // Text
    AText* APMText = GetWorld()->SpawnActor<AText>();
    APMText->SetSprite("apm.png", 0, 1.0f);
    APMText->SetActorLocation({ Size.iX() - 140, 138 });

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

    for (float i = 0; i < 12; i++)
    {
        ASlot* Slot = GetWorld()->SpawnActor<ASlot>();
        // Slot->SetSprite("UI", 6);
        Slot->SetName("EmptySlot");
        Slot->SetScale(FVector2D{ 16 * 3.5f, 16 * 3.5f });
        Slot->SaveItemInfo("Slot.png", 0, FVector2D{ 16 * 3.5f, 16 * 3.5f });
        Slot->SetActorLocation(StartLocation + (InterLocation * i));
        AllSlots[0].push_back(Slot);
    }

    StartLocation = { Size.Half().iX() - 310, Size.Half().iY() - 143 };

    for (float y = 1; y < AllSlots.size(); y++)
    {
        for (float i = 0; i < 12; i++)
        {
            ASlot* Slot = GetWorld()->SpawnActor<ASlot>();
            //Slot->SetSprite("UI", 6);
            Slot->SetName("EmptySlot");
            Slot->SetScale(FVector2D{ 16 * 3.5f, 16 * 3.5f });
            Slot->SaveItemInfo("Slot.png", 0, FVector2D{ 16 * 3.5f, 16 * 3.5f });
            FVector2D Location = { 0, 60 };
            Slot->SetActorLocation(StartLocation + (InterLocation * i) + (Location * y));
            Slot->SetActive(false);

            AllSlots[static_cast<int>(y)].push_back(Slot);
        }
    }


    // 기본 아이템 지급
    DefaultItem({ 0,0 }, "Hoe.png", "Hoe", 0, { 16 * 3.5f, 16 * 3.5f });
    DefaultItem({ 0,1 }, "Ax.png", "Axe", 0, { 16 * 3.5f, 16 * 3.5f });
    DefaultItem({ 0,2 }, "Items.png", "ParsnipSeed", 624, { 14 * 3.5f, 14 * 3.5f }, { 0,0 }, 10);
    DefaultItem({ 0,3 }, "Items.png", "BeanStarter", 625, { 14 * 3.5f, 14 * 3.5f }, { 0,0 }, 10);
    DefaultItem({ 0,4 }, "WateringCan.png", "WateringCan", 2, { 20 * 3.5f, 20 * 3.5f });

    // CulSlot
    CurSlot = GetWorld()->SpawnActor<ASlot>();
    CurSlot->SetSprite("SelectedSlot.png", 0);
    CurSlot->SetOrder(ERenderOrder::CURSLOT);
    CurSlot->SetScale(FVector2D{ 16 * 3.5f, 16 * 3.5f });
    CurSlot->SetActorLocation(AllSlots[0][CurSlotNum]->GetActorLocation());
    CurSlot->SaveItemInfo("SelectedSlot.png",0, FVector2D{ 16 * 3.5f, 16 * 3.5f });
    CurSlot->SetName(AllSlots[0][CurSlotNum]->GetName());
    CurSlot->CollisionDestroy();

    CulStoreColumn = GetWorld()->SpawnActor<ASlot>();
    CulStoreColumn->SetSprite("CurStoreColumn.png", 0);
    CulStoreColumn->SetOrder(ERenderOrder::CURSLOT);
    CulStoreColumn->SetScale(FVector2D{ 294 * 3.5f, 28 * 3.5f });
    CulStoreColumn->CollisionDestroy();
    CulStoreColumn->SetActive(false);

    // CulItem
    CurItem = GetWorld()->SpawnActor<ACurItem>();

    // Inventory
    Inventory = GetWorld()->SpawnActor<AInventory>();
    Inventory->SetActorLocation({ Size.Half().iX() + 1, Size.Half().iY() });
    Inventory->SetActive(false);
    Inventory->SetSprite("Inventory2.png", 0);
    Inventory->SetComponentScale(FVector2D{ 216 * 3.5f, 159 * 3.5f });

    StoreInven = GetWorld()->SpawnActor<AInventory>();
    StoreInven->SetActive(false);
    StoreInven->SetSprite("Inventory.png", 0);
    StoreInven->SetComponentScale(FVector2D{ 214 * 3.5f, 74 * 3.5f });
    StoreInven->SetActorLocation({ Size.iX() - 214 * 3.5f / 2 - 120, Size.iY() - 74 * 3.5f / 2 });

    InvenPlayer = GetWorld()->SpawnActor<AUI>();
    InvenPlayer->SetSprite("Farmer_Right.png", 0, 3.5f);
    InvenPlayer->SetComponentScale({ 220, 440 });
    InvenPlayer->SetOrder(ERenderOrder::SLOTITEM);
    InvenPlayer->SetActorLocation({ Size.Half().iX() - 227, Size.Half().iY() + 188 });
    InvenPlayer->CreateAnimation("Idle", "Farmer_Right.png", { 0, 15,0 }, { 1.0f,0.1f,2.0f });
    InvenPlayer->SetActive(false);

    ExplainNameText = GetWorld()->SpawnActor<AUI>();
    ExplainNameText->SetSprite("TextBox.png", 0, 3.5f);
    ExplainNameText->SetOrder(ERenderOrder::SelectedItem);
    ExplainNameText->SetActive(false);

    TextBoxTop = GetWorld()->SpawnActor<AUI>();
    TextBoxTop->SetComponentScale({ 100 * 3.5f,6 * 3.5f });
    TextBoxTop->SetSprite("TextBox_Top.png", 0, 3.5f);
    TextBoxTop->SetOrder(ERenderOrder::ExplainTextBox);
    TextBoxTop->SetActive(false);

    TextBoxMid = GetWorld()->SpawnActor<AUI>();
    TextBoxMid->SetComponentScale({ 100 * 3.5f, 14 * 3.5f });
    TextBoxMid->SetSprite("TextBox_Mid.png", 0, 3.5f);
    TextBoxMid->SetOrder(ERenderOrder::ExplainTextBox);
    TextBoxMid->SetActive(false);

    TextBoxBot = GetWorld()->SpawnActor<AUI>();
    TextBoxBot->SetComponentScale({ 100 * 3.5f,7 * 3.5f });
    TextBoxBot->SetSprite("TextBox_Bot.png", 0, 3.5f);
    TextBoxBot->SetOrder(ERenderOrder::ExplainTextBox);
    TextBoxBot->SetActive(false);

    StoreBox = GetWorld()->SpawnActor<AUI>();
    StoreBox->SetComponentScale({ 280 * 3.5f,130 * 3.5f });
    StoreBox->SetSprite("StoreBox.png", 0, 3.5f);
    StoreBox->SetOrder(ERenderOrder::INVEN);
    StoreBox->SetActive(false);
    StoreBox->SetActorLocation({ Size.Half().X , Size.Half().Y - 90 });

    UpArrow = GetWorld()->SpawnActor<AUI>();
    UpArrow->SetComponentScale({ 11 * 4.f,12 * 4.f });
    UpArrow->SetCollisionComponentScale({ 11 * 4.f,12 * 4.f });
    UpArrow->SetCollisionComponentLocation({ 0.0f , 0.0f });
    UpArrow->SetSprite("Up.png", 0, 4.f);
    UpArrow->SetOrder(ERenderOrder::SLOT);
    UpArrow->SetActive(false);
    UpArrow->SetActorLocation({ Size.X - 80.f ,120.f });

    DownArrow = GetWorld()->SpawnActor<AUI>();
    DownArrow->SetComponentScale({ 11 * 4.f, 12 * 4.f });
    DownArrow->SetCollisionComponentScale({ 11 * 4.f,12 * 4.f });
    DownArrow->SetCollisionComponentLocation({ 0.0f , 0.0f });
    DownArrow->SetSprite("Down.png", 0, 4.f);
    DownArrow->SetOrder(ERenderOrder::SLOT);
    DownArrow->SetActive(false);
    DownArrow->SetActorLocation({ Size.X - 80.f ,Size.Y - 120.f });

    Text = GetWorld()->SpawnActor<AGold>();
    Text2 = GetWorld()->SpawnActor<AGold>();
    Text3 = GetWorld()->SpawnActor<AGold>();

    Text->SetTextSpriteName("Alphabet.png");
    Text->SetOrder(ERenderOrder::ExplainText);
    Text->SetTextScale({ 27, 31 });
    Text->SetActive(false);

    Text2->SetTextSpriteName("Alphabet.png");
    Text2->SetOrder(ERenderOrder::ExplainText);
    Text2->SetTextScale({ 21, 24 });
    Text2->SetActive(false);

    Text3->SetTextSpriteName("Alphabet.png");
    Text3->SetOrder(ERenderOrder::ExplainText);
    Text3->SetTextScale({ 21, 24 });
    Text3->SetActive(false);

    ExplianBoxScaleY = TextBoxTop->GetScale().Y;

    ToolsAnimation = GetWorld()->SpawnActor<APlayerToolsAnimation>();

    Fade = GetWorld()->SpawnActor<AFade>();
    Fade->SetOrder(ERenderOrder::Black);
    Fade->SetActive(false);
    Fade->SetAlphaChar(150);

    Night = GetWorld()->SpawnActor<AFade>();
    //Night->SetSprite("Night.png");
    Night->SetOrder(ERenderOrder::Night);


    StoreGoldText = GetWorld()->SpawnActor<AGold>();
    StoreGoldText->SetActorLocation({ 355.f , Size.Y - 196.f });
    StoreGoldText->SetTextSpriteName("Gold3.png");
    StoreGoldText->SetOrder(ERenderOrder::GLODTEXT);
    StoreGoldText->SetTextScale({ 22, 33 });
    StoreGoldText->SetActive(false);

    StoreExitButton = GetWorld()->SpawnActor<AUI>();
    StoreExitButton->SetComponentScale({ 12 * 3.5f,12 * 3.5f });
    StoreExitButton->SetCollisionComponentScale({ 12 * 3.5f,12 * 3.5f });
    StoreExitButton->SetSprite("ExitButton.png", 0, 3.5f);
    StoreExitButton->SetOrder(ERenderOrder::GLODTEXT);
    StoreExitButton->SetActorLocation({ Size.X - 95 , 50.f });
    StoreExitButton->SetCollisionComponentLocation({ 0.0f , 0.0f });
    StoreExitButton->SetActive(false);



    for (size_t i = 0; i < 9; i++)
    {
        ASlot* StoreColumn = GetWorld()->SpawnActor<ASlot>();
        StoreColumn->SetCollisionComponentScale(FVector2D{ 294 * 3.5f, 28 * 3.5f });
        StoreColumn->SetActive(false);
        AllStoreColumns.push_back(StoreColumn);
    }
    AllStoreColumns[0]->SetName("START");

    AllStoreColumns[1]->SetName("ParsnipSeed");
    AllStoreColumns[1]->SaveItemInfo("Items.png", 624, { 16 * 3.5f,16 * 3.5f });

    AllStoreColumns[2]->SetName("BeanStarter");
    AllStoreColumns[2]->SaveItemInfo("Items.png", 625, { 16 * 3.5f,16 * 3.5f });

    AllStoreColumns[3]->SetName("CauliflowerSeed");
    AllStoreColumns[3]->SaveItemInfo("Items.png", 626, { 16 * 3.5f,16 * 3.5f });

    AllStoreColumns[4]->SetName("PotatoSeed");
    AllStoreColumns[4]->SaveItemInfo("Items.png", 627, { 16 * 3.5f,16 * 3.5f });

    AllStoreColumns[5]->SetName("GarlicSeed");
    AllStoreColumns[5]->SaveItemInfo("Items.png", 628, { 16 * 3.5f,16 * 3.5f });

    AllStoreColumns[6]->SetName("KaleSeed");
    AllStoreColumns[6]->SaveItemInfo("Items.png", 629, { 16 * 3.5f,16 * 3.5f });

    AllStoreColumns[7]->SetName("RhubarbSeed");
    AllStoreColumns[7]->SaveItemInfo("Items.png", 630, { 16 * 3.5f,16 * 3.5f });

    AllStoreColumns[8]->SetName("END");


    StartLocation = { 177, 112 };
    InterLocation = { 0.0f, 98.0f };

    for (float i = 0; i < 4; i++)
    {
        ASelectedItem* StoreItem = GetWorld()->SpawnActor<ASelectedItem>();
        StoreItem->SetActorLocation(StartLocation + (InterLocation * i));
        StoreItem->SetActive(false);
        AllStoreItem.push_back(StoreItem);
    }
    StartLocation = { 240, 112 };

    for (float i = 0; i < 4; i++)
    {
        AGold* StoreItemName = GetWorld()->SpawnActor<AGold>();
        StoreItemName->SetActorLocation(StartLocation + (InterLocation * i));
        StoreItemName->SetTextSpriteName("AlphabetBold.png");
        StoreItemName->SetOrder(ERenderOrder::SLOTFont);
        StoreItemName->SetTextScale({ 24, 48 });
        StoreItemName->SetActive(false);
        AllStoreItemName.push_back(StoreItemName);
    }
    StartLocation = { Size.X - 200.f, 112.f };

    for (float i = 0; i < 4; i++)
    {
        AGold* StoreItemPrice = GetWorld()->SpawnActor<AGold>();
        StoreItemPrice->SetActorLocation(StartLocation + (InterLocation * i));
        StoreItemPrice->SetTextSpriteName("Gold3.png");
        StoreItemPrice->SetOrder(ERenderOrder::SLOTFont);
        StoreItemPrice->SetTextScale({ 22, 33 });
        StoreItemPrice->SetActive(false);
        AllStoreItemPrice.push_back(StoreItemPrice);
    }

    CurText = GetWorld()->SpawnActor<AGold>();
    CurText->SetTextSpriteName("Item.png");
    CurText->SetOrder(ERenderOrder::ExplainTextBox);
    CurText->SetTextScale({ 13, 15 });

    SellItem = GetWorld()->SpawnActor<ASelectedItem>();



    BedTextBox = GetWorld()->SpawnActor<AUI>();
    BedTextBox->SetComponentScale({ 1280 * 3.5f,300 * 3.5f });
    BedTextBox->SetActorLocation({ Size.Half().X, Size.Y - (BedTextBox->GetScale().Half().Y/3.5f) });
    BedTextBox->SetSprite("BedTextBox.png", 0, 1.f);
    BedTextBox->SetOrder(ERenderOrder::ExplainTextBox);
    BedTextBox->SetActive(false);

    YesTextBox = GetWorld()->SpawnActor<AUI>();
    YesTextBox->SetComponentScale({ 1194 * 3.5f,67 * 3.5f });
    YesTextBox->SetCollisionComponentScale({ 1194 ,67  });
    YesTextBox->SetCollisionComponentLocation({ 0.0f , 0.0f });
    YesTextBox->SetActorLocation({ Size.Half().X, Size.Y - (YesTextBox->GetScale().Y / 3.5f * 2) });
    YesTextBox->SetSprite("YesUnSelected.png", 0, 1.f);
    YesTextBox->SetOrder(ERenderOrder::ExplainTextBox);
    YesTextBox->SetActive(false);

    NoTextBox = GetWorld()->SpawnActor<AUI>();
    NoTextBox->SetComponentScale({ 1194 * 3.5f,67 * 3.5f });
    NoTextBox->SetCollisionComponentScale({ 1194 , 67 });
    NoTextBox->SetCollisionComponentLocation({ 0.0f, 0.0f });
    NoTextBox->SetActorLocation({ Size.Half().X, Size.Y - (NoTextBox->GetScale().Y / 3.5f) });
    NoTextBox->SetSprite("NoUnSelected.png", 0, 1.f);
    NoTextBox->SetOrder(ERenderOrder::ExplainTextBox);
    NoTextBox->SetActive(false);

    BedText = GetWorld()->SpawnActor<AGold>();
    BedText->SetActorLocation({ 70.f, Size.Y - (YesTextBox->GetScale().Y / 3.5f * 3) });
    BedText->SetTextSpriteName("AlphabetBold.png");
    BedText->SetOrder(ERenderOrder::ExplainText);
    BedText->SetTextScale({ 24, 48 });
    BedText->SetText2("Go to sleep for the night?");
    BedText->SetActive(false);
}

void APlayerUI::Tick(float _DeltaTime)
{

    Super::Tick(_DeltaTime);
    FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
    FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
    APlayer* Player = GetWorld()->GetPawn<APlayer>();

    // cursor
    Cursor->SetActorLocation({ MousePos.X + 10, MousePos.Y + 15 });
    ToolsAnimation->SetActorLocation(Player->GetActorLocation());
    // time
    Min = MinTime->SetMinute(_DeltaTime);
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

    Week = HourTime->WeekCheck(Min);
    WeekText->SetSprite("Week.png", Week, 1.0f);
    WeekText->SetActorLocation({ Size.iX() - 140, 50 });

    Day = HourTime->DayCheck(Min);

    DayText->SetActorLocation({ Size.iX() - 70 , 50 });
    DayText->SetTextSpriteName("Time.png");
    DayText->SetOrder(ERenderOrder::UIFont);
    DayText->SetTextScale({ 20, 28 });
    DayText->SetValue(Day, 1.6f);
    TextLocation = { 60 , 90 };

    if (false == IsChoose)
    {
        CurText->SetActive(false);
        SlotItemTextLocation(TextLocation.iX(), TextLocation.iY());
        if (TextBoxBot->GetActorLocation().iY() + TextBoxBot->GetScale().Half().iY() >= Size.iY())
        {
            int InterY = TextBoxBot->GetActorLocation().iY() + TextBoxBot->GetScale().Half().iY() - Size.iY();
            SlotItemTextLocation(TextLocation.iX() + 10, TextLocation.iY() - InterY);
        }
    }
    else if (true == IsChoose)
    {
        CurText->SetActorLocation({ MousePos.X + 56, MousePos.Y + 61 });
        CurText->SetValue(BuyItemCount, 1.3f);
        SlotItemTextLocation(TextLocation.iX() + 30, TextLocation.iY() + 30);
        if (TextBoxBot->GetActorLocation().Y + TextBoxBot->GetScale().Half().Y >= Size.Y)
        {
            int InterY = TextBoxBot->GetActorLocation().iY() + TextBoxBot->GetScale().Half().iY() - Size.iY();
            SlotItemTextLocation(TextLocation.iX() + 40, TextLocation.iY() - InterY);
        }
    }

    if (IsOpenIven == 0)
    {
        CurSlotItemSpawn();
    }

    SetCurSlot();
    BuyStoreItem();
    SlotItemChange();
    ItemExplainText();
    ToolsAnimationCheck();
    InventoryCheck();
    StoreInvenCheck();
    SellStoreItem();
    SleepCheck();

    if (SelectedItem != nullptr)
    {
        SelectedItem->SetActorLocation({ MousePos.X + 40, MousePos.Y + 45 });
        SelectedItem->SetCameraEffect(false);
    }


    IsInventoryEnter = Cursor->GetIsEnter();


    ToolsAnimationTimer(_DeltaTime, AnimationDuration);

    if (true == StoreExitButton->GetIsCollisionEnter())
    {
        StoreExitButton->SetComponentScale({ 14 * 3.5f,14 * 3.5f });
        StoreExitButton->SetCollisionComponentScale({ 14 * 3.5f,14 * 3.5f });

    }
    else if (true == StoreExitButton->GetIsCollisionEnd())
    {
        StoreExitButton->SetComponentScale({ 12 * 3.5f,12 * 3.5f });
        StoreExitButton->SetCollisionComponentScale({ 12 * 3.5f,12 * 3.5f });


    }
    ShopItemLists();

    for (int i = 0; i < 4; i++)
    {
        if (AllStoreColumns[StartIndex + i] == nullptr)
        {
            continue;
        }

        bool IsCulColumns = AllStoreColumns[StartIndex + i]->GetIsStay();

        if (true == IsCulColumns)
        {
            CulStoreColumnNum = StartIndex + i;
            CulStoreColumn->SetActive(true);
            CulStoreColumn->SetActorLocation({ AllStoreColumns[CulStoreColumnNum]->GetActorLocation().X, AllStoreColumns[CulStoreColumnNum]->GetActorLocation().Y });
            continue;
        }

    }

    if (CulcolumsCheck() == false)
    {
        CulStoreColumn->SetActive(false);

    }

    Gold->SetValue(PlayerManager::GetInst().GetGold(), 1.6f);


    StoreGoldText->SetValue(PlayerManager::GetInst().GetGold(), 4.3f);


    if (6 <= Min && 18 >= Min)
    {
        NightTime = 0;
    }
    if (18 <= Min && 26 >= Min)
    {
        Night->SetActive(true);

        NightTime += _DeltaTime * MinTime->GetTimeSpeed() * 0.05f;

    }
    if (NightTime > 100)
    {
        int a = 0;
    }
    Night->SetAlphaChar(NightTime);
    if (Min < 27)
    {
        ClockHand->SetSprite("ClockHand", Min - 6, 4.0f);
    }
    if (true == IsPlayerSleep)
    {
        OverDayTimeSetting(_DeltaTime);
    }
}
void APlayerUI::SleepCheck()
{
    if (GetWorld()->GetGameMode<AHouseGameMode>() == nullptr)
    {
        return;
    }
    APlayer* Player = GetWorld()->GetPawn<APlayer>();

    AHouseGameMode* House = GetWorld()->GetGameMode<AHouseGameMode>();
    IsBedIn = House->GetIsBedIn();
    if (true == IsBedIn)
    {
        if (IsPlayerSleep == false)
        {
            BedTextBox->SetActive(true);
            YesTextBox->SetActive(true);
            NoTextBox->SetActive(true);
            BedText->SetActive(true);
            YesTextBox->SetCollisionActive(true);
            NoTextBox->SetCollisionActive(true);

            InventoryBar->SetActive(false);
            for (int i = 0; i < AllSlots[0].size(); i++)
            {
                AllSlots[0][i]->SetActive(false);
            }

        }



        if (true == YesTextBox->GetIsCollisionStay() && IsPlayerSleep == false)
        {
            YesTextBox->SetSprite("YesSelected.png", 0, 1.f);
            if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON))
            {

                BedTextBox->SetActive(false);
                YesTextBox->SetActive(false);
                YesTextBox->SetCollisionActive(false);
                NoTextBox->SetActive(false);
                NoTextBox->SetCollisionActive(false);

                BedText->SetActive(false);
                InventoryBar->SetActive(true);

                for (int i = 0; i < AllSlots[0].size(); i++)
                {
                    AllSlots[0][i]->SetActive(true);
                }
                Player->SetIsOverDay(true);
                IsOverDays = true;

                Player->Fade->FadeInOut();
                IsPlayerSleep = true;
                TimeValue = 0.0f;
               
            }
            if (true == UEngineInput::GetInst().IsUp(VK_LBUTTON))
            {
                //IsOverDay = false;

            }

        }
        else if (true == YesTextBox->GetIsCollisionEnd())
        {
            YesTextBox->SetSprite("YesUnSelected.png", 0, 1.f);
        }

        if (true == NoTextBox->GetIsCollisionEnter())
        {
            NoTextBox->SetSprite("NoSelected.png", 0, 1.f);

            if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON))
            {
                House->SetIsNo(true);
            }

        }
        else if (true == NoTextBox->GetIsCollisionEnd())
        {
            NoTextBox->SetSprite("NoUnSelected.png", 0, 1.f);
        }

    }
    if (false == IsBedIn)
    {
        BedTextBox->SetActive(false);
        YesTextBox->SetActive(false);
        NoTextBox->SetActive(false);
        BedText->SetActive(false);
        IsPlayerSleep = false;

        InventoryBar->SetActive(true);
        for (int i = 0; i < AllSlots[0].size(); i++)
        {
            AllSlots[0][i]->SetActive(true);
        }
        TimeOnce = 0;
        
    }
}

void APlayerUI::OverDayTimeSetting(float _Deltatime)
{

    TimeValue += _Deltatime;

    if (TimeValue >= 2.0f && TimeOnce == 0)
    {
        MinTime->SetMinutes(0);
        MinTime->SetHours(6);
      

        int Day = HourTime->GetDay();
        int Week = HourTime->GetWeek();
        Day += 1;
        Week += 1;
        HourTime->SetDay(Day);
        HourTime->SetWeek(Week);

        TimeOnce += 1;
    }

}

void APlayerUI::ShopItemLists()
{
    FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

    for (int i = 0; i < 9; i++)
    {
        AllStoreColumns[i]->SetActive(false);

    }

    if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON) && true == DownArrow->GetIsClick())
    {
        ++StartIndex;
    }
    if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON) && true == UpArrow->GetIsClick())
    {
        --StartIndex;
    }

    if (AllStoreColumns[StartIndex]->GetName() == "START")
    {
        ++StartIndex;
        return;
    }
    if (AllStoreColumns[StartIndex + 3]->GetName() == "END")
    {
        --StartIndex;
        return;
    }

    for (size_t i = 0; i < 4; i++)
    {
        AllStoreItem[i]->SetSprite(AllStoreColumns[StartIndex + i]->GetItemSpriteName(), AllStoreColumns[StartIndex + i]->GetItemIndex(), 3.5f);
        AllStoreItemName[i]->SetText2(AllStoreColumns[StartIndex + i]->GetName());
        SellItem->SetPrice(AllStoreColumns[StartIndex + i]->GetName());
        int Price = SellItem->GetPrice();
        AllStoreItemPrice[i]->SetValue(Price, 1.3f);

    }

    FVector2D StartLocation = { Size.Half().iX() + 1, 108 };
    FVector2D InterLocation = { 0, 99 };
    for (__int64 i = 0; i < 4; i++)
    {
        AllStoreColumns[StartIndex + i]->SetActorLocation(StartLocation + (InterLocation * static_cast<float>(i)));
        AllStoreColumns[StartIndex + i]->SetActive(true);

        if (IsOpenStore == 1)
        {
            AllStoreColumns[StartIndex + i]->SetActive(true);

        }
        if (IsOpenStore == 0)
        {
            AllStoreColumns[StartIndex + i]->SetActive(false);

        }

    }


}


void APlayerUI::ToolsAnimationCheck()
{

    APlayer* Player = GetWorld()->GetPawn<APlayer>();

    if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON) && false == Player->IsPlayerMove && false == GetIsInventoryEnter() && AnimationTimer == 0 && IsBedIn == false)
    {
        if (CurSlotItemName() == "Axe")
        {
            IsAnimationPlay = true;
            ToolsAnimation->SetActive(true);
            ToolsAnimationDir("Axe", 0.45f);

        }
        else if (CurSlotItemName() == "Hoe")
        {
            IsAnimationPlay = true;
            ToolsAnimation->SetActive(true);
            ToolsAnimationDir("Hoe", 0.45f);

        }

        else if (CurSlotItemName() == "WateringCan")
        {
            IsAnimationPlay = true;
            ToolsAnimation->SetActive(true);
            ToolsAnimationDir("Water", 0.55f);
        }
    }
}

void APlayerUI::ToolsAnimationDir(std::string _AnimationName, float _time)
{
    APlayer* Player = GetWorld()->GetPawn<APlayer>();
    if (false == Player->IsButtonClick)
    {
        switch (Player->PlayerDir)
        {
        case EPlayerDir::Left:
            ToolsAnimation->ChangeAnimation(_AnimationName + "_Left", true);
            SetAnimationDuration(_time);
            break;
        case EPlayerDir::Right:
            ToolsAnimation->ChangeAnimation(_AnimationName + "_Right", true);
            SetAnimationDuration(_time);

            break;
        case EPlayerDir::Up:
            ToolsAnimation->ChangeAnimation(_AnimationName + "_Back", true);
            SetAnimationDuration(_time);

            break;
        case EPlayerDir::Down:
            ToolsAnimation->ChangeAnimation(_AnimationName + "_Front", true);
            SetAnimationDuration(_time);

            break;
        default:
            break;
        }
    }

}

void APlayerUI::SetAnimationDuration(float _Duration)
{
    AnimationDuration = _Duration;

}

void APlayerUI::ToolsAnimationTimer(float _DeltaTime, float _Duration)
{

    if (IsAnimationPlay)
    {
        AnimationTimer += _DeltaTime;
        if (AnimationTimer >= _Duration)
        {
            IsAnimationPlay = false;
            AnimationTimer = 0.0f;
            ToolsAnimation->SetActive(false);
        }
    }
}


void APlayerUI::SlotItemTextLocation(int X, int Y)
{
    FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

    Text->SetActorLocation({ MousePos.X + X , MousePos.Y + Y });
    Text2->SetActorLocation({ MousePos.X + X, MousePos.Y + Y + 30 });
    Text3->SetActorLocation({ MousePos.X + X, MousePos.Y + Y + 95 });

    ExplainNameText->SetActorLocation({ MousePos.X + X + 140, MousePos.Y + Y + 20 });
    TextBoxTop->SetActorLocation({ MousePos.X + X + 140, MousePos.Y + Y + 60 });
    TextBoxMid->SetActorLocation({ MousePos.X + X + 140, MousePos.Y + Y + 50 + TextBoxTop->GetScale().Y + TextBoxScale / 2 - 1 });
    TextBoxBot->SetActorLocation({ MousePos.X + X + 140, MousePos.Y + Y + 60 + TextBoxTop->GetScale().Y + TextBoxMid->GetScale().Y });
}



void APlayerUI::InventoryCheck()
{
    APlayer* Player = GetWorld()->GetPawn<APlayer>();

    // Inventory
    // 인벤토리 닫기
    if (true == UEngineInput::GetInst().IsDown('E') && IsOpenIven == 1)
    {
        BGMPlayer = UEngineSound::Play("InvenClose.wav");

        Player->IsOpenIven = false;

        --IsOpenIven;
        Inventory->SetActive(false);
        InvenPlayer->SetActive(false);

        InventoryBar->SetActive(true);
        for (int i = 0; i < 12; i++)
        {
            Loc0 = AllSlots[0][i]->GetActorLocation();
            Loc0 = { Loc0.X - 1, Loc0.Y };
            Loc0_2 = AllSlots[0][i]->GetActorLocation() + AllSlots[0][i]->GetScale().Half();

            AllSlots[0][i]->SetActorLocation(Loc0 + FVector2D::DOWN * 440.0f);
            if (AllSlots[0][i]->GetText() != nullptr)
            {
                AllSlots[0][i]->SetTextLocation(Loc0_2 + FVector2D::DOWN * 440.0f);
            }
        }
        for (int y = 1; y < 3; y++)
        {
            for (int i = 0; i < 12; i++)
            {
                AllSlots[y][i]->SetActive(false);
                if (AllSlots[y][i]->GetText() != nullptr)
                {
                    AllSlots[y][i]->GetText()->SetActive(false);
                }
            }
        }
        CurItem->SetActive(true);
        CurSlot->SetActive(true);

    }
    // 인벤토리 열기
    else if (true == UEngineInput::GetInst().IsDown('E') && IsOpenStore != 1)
    {
        BGMPlayer = UEngineSound::Play("InvenOpen.wav");
        Player->IsOpenIven = true;

        Inventory->SetActive(true);
        InvenPlayer->SetActive(true);

        InvenPlayer->ChangeAnimation("Idle", true);



        ++IsOpenIven;
        InventoryBar->SetActive(false);
        for (int i = 0; i < 12; i++)
        {

            Loc0 = AllSlots[0][i]->GetActorLocation();
            Loc0 = { Loc0.X + 1, Loc0.Y };
            Loc0_2 = AllSlots[0][i]->GetActorLocation() + AllSlots[0][i]->GetScale().Half();

            AllSlots[0][i]->SetActorLocation(Loc0 + FVector2D::UP * 440.0f);
            if (AllSlots[0][i]->GetText() != nullptr)
            {
                AllSlots[0][i]->SetTextLocation(Loc0_2 + FVector2D::UP * 440.0f);
            }
        }

        for (int y = 1; y < 3; y++)
        {
            for (int i = 0; i < 12; i++)
            {
                AllSlots[y][i]->SetActive(true);
                if (AllSlots[y][i]->GetText() != nullptr)
                {
                    AllSlots[y][i]->GetText()->SetActive(true);
                }
            }
        }

        CurItem->SetActive(false);
        CurSlot->SetActive(false);

    }
}


void APlayerUI::StoreInvenCheck()
{
    APlayer* Player = GetWorld()->GetPawn<APlayer>();
    AStoreGameMode* StoreGameMode = Player->GetWorld()->GetGameMode<AStoreGameMode>();

    if (nullptr == StoreGameMode)
    {
        return;
    }

    if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON) && true == StoreExitButton->GetIsClick() && IsOpenStore == 1 && false == IsChoose)
    {
        Player->IsOpenIven = false;
        Player->IsButtonClick = false;
        --IsOpenStore;
        StartIndex = 0;
        StoreInven->SetActive(false);
        StoreBox->SetActive(false);
        Fade->SetActive(false);
        StoreGoldText->SetActive(false);
        UpArrow->SetActive(false);
        DownArrow->SetActive(false);

        StoreExitButton->SetActive(false);
        StoreExitButton->SetCollisionActive(false);


        for (int i = 0; i < 4; i++)
        {
            AllStoreColumns[StartIndex + i]->SetActive(false);
            AllStoreItem[i]->SetActive(false);
            AllStoreItemName[i]->SetActive(false);
            AllStoreItemPrice[i]->SetActive(false);

        }


        InventoryBar->SetActive(true);
        for (int i = 0; i < 12; i++)
        {
            Loc0 = AllSlots[0][i]->GetActorLocation();
            Loc0 = { Loc0.X - 1, Loc0.Y };
            Loc0_2 = AllSlots[0][i]->GetActorLocation() + AllSlots[0][i]->GetScale().Half();

            AllSlots[0][i]->SetActorLocation(Loc0 + FVector2D::DOWN * 115.0f + FVector2D::LEFT * 145.0f);
            if (AllSlots[0][i]->GetText() != nullptr)
            {
                AllSlots[0][i]->SetTextLocation(Loc0_2 + FVector2D::DOWN * 115.0f + FVector2D::LEFT * 145.0f);
            }
        }
        for (int y = 1; y < 3; y++)
        {
            for (int i = 0; i < 12; i++)
            {
                Loc1 = AllSlots[y][i]->GetActorLocation();
                Loc1 = { Loc1.X - 1, Loc1.Y };
                Loc1_2 = AllSlots[y][i]->GetActorLocation() + AllSlots[y][i]->GetScale().Half();

                AllSlots[y][i]->SetActorLocation(Loc1 + FVector2D::UP * 325.0f + FVector2D::LEFT * 145.0f);
                AllSlots[y][i]->SetActive(false);
                if (AllSlots[y][i]->GetText() != nullptr)
                {
                    AllSlots[y][i]->SetTextLocation(Loc1_2 + FVector2D::UP * 325.0f + FVector2D::LEFT * 145.0f);
                    AllSlots[y][i]->GetText()->SetActive(false);
                }
            }
        }
        CurItem->SetActive(true);
        CurSlot->SetActive(true);

    }
    // 인벤토리 열기
    else if (true == UEngineInput::GetInst().IsDown(VK_RBUTTON) && true == StoreGameMode->GetIsOpenCounter() && IsOpenStore == 0 && IsOpenIven == 0)
    {

        Player->IsOpenIven = true;
        Player->IsButtonClick = true;

        StoreInven->SetActive(true);
        StoreBox->SetActive(true);
        UpArrow->SetActive(true);
        DownArrow->SetActive(true);
        
        Fade->SetActive(true);
        StoreGoldText->SetActive(true);
        StoreExitButton->SetActive(true);
        StoreExitButton->SetCollisionActive(true);

        for (int i = 0; i < 4; i++)
        {
            AllStoreItem[i]->SetActive(true);
            AllStoreItemName[i]->SetActive(true);
            AllStoreItemPrice[i]->SetActive(true);

        }

        ++IsOpenStore;
        InventoryBar->SetActive(false);
        for (int i = 0; i < 12; i++)
        {

            FVector2D Loc = AllSlots[0][i]->GetActorLocation();
            Loc = { Loc.X + 1, Loc.Y };
            FVector2D Loc2 = AllSlots[0][i]->GetActorLocation() + AllSlots[0][i]->GetScale().Half();


            AllSlots[0][i]->SetActorLocation(Loc + FVector2D::UP * 115.0f + FVector2D::RIGHT * 145.0f);
            if (AllSlots[0][i]->GetText() != nullptr)
            {
                AllSlots[0][i]->SetTextLocation(Loc2 + FVector2D::UP * 115.0f + FVector2D::RIGHT * 145.0f);


            }
        }

        for (int y = 1; y < 3; y++)
        {
            for (int i = 0; i < 12; i++)
            {
                Loc1 = AllSlots[y][i]->GetActorLocation();
                Loc1 = { Loc1.X + 1, Loc1.Y };
                Loc1_2 = AllSlots[y][i]->GetActorLocation() + AllSlots[y][i]->GetScale().Half();

                AllSlots[y][i]->SetActive(true);
                AllSlots[y][i]->SetActorLocation(Loc1 + FVector2D::DOWN * 325.0f + FVector2D::RIGHT * 145.0f);

                if (AllSlots[y][i]->GetText() != nullptr)
                {
                    AllSlots[y][i]->GetText()->SetActive(true);
                    AllSlots[y][i]->SetTextLocation(Loc1_2 + FVector2D::DOWN * 325.0f + FVector2D::RIGHT * 145.0f);

                }

            }
        }

        CurItem->SetActive(false);
        CurSlot->SetActive(false);

    }
}


void APlayerUI::DefaultItem(FIntPoint _SlotIndex, std::string _SpriteName, std::string _ItemName, int _ItemIndex, FVector2D _Scale, FVector2D _Location, int ItemCount)
{
    FVector2D DefaultLocation = AllSlots[_SlotIndex.X][_SlotIndex.Y]->GetActorLocation();
    AllSlots[_SlotIndex.X][_SlotIndex.Y]->SetSprite(_SpriteName, _ItemIndex);
    AllSlots[_SlotIndex.X][_SlotIndex.Y]->SetName(_ItemName);
    AllSlots[_SlotIndex.X][_SlotIndex.Y]->SetActorLocation(DefaultLocation + _Location);
    AllSlots[_SlotIndex.X][_SlotIndex.Y]->SetScale(_Scale);
    AllSlots[_SlotIndex.X][_SlotIndex.Y]->SetSlotItemCount(ItemCount);
    if (ItemCount > 1)
    {
        AllSlots[_SlotIndex.X][_SlotIndex.Y]->CountText();
    }
    AllSlots[_SlotIndex.X][_SlotIndex.Y]->SaveItemInfo(_SpriteName, _ItemIndex, _Scale);
    AllSlots[_SlotIndex.X][_SlotIndex.Y]->SaveItemInfo(_SpriteName, _ItemIndex, _Scale);
}


void APlayerUI::AddItem(AItem* _Item)
{
    bool IsOver = _Item->ItemTypeCheck(_Item->GetItemType());
    BGMPlayer = UEngineSound::Play("AddItem.wav");

    _Item->Destroy();
    SlotCheck(_Item, _Item->GetItemName(), _Item->GetItemSpriteName(), _Item->GetItemIndex(), IsOver);
}



void APlayerUI::SlotCheck(AItem* _Item, std::string _ItemName, std::string _SpriteName, int _Index, bool IsOver)
{
    FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

    bool HasItem = false;
    int HasItemY = 0;
    int HasItemX = 0;

    for (int y = 0; y < 3; y++)
    {
        for (int i = 0; i < AllSlots[y].size(); i++)
        {
            std::string SlotSpriteName = AllSlots[y][i]->GetName();

            if (SlotSpriteName == _ItemName)
            {
                HasItem = true;
                HasItemY = y;
                HasItemX = i;
            }
        }
    }

    if (true == HasItem)
    {
        SlotItemText(HasItemY, HasItemX);
        return;
    }

    for (int y = 0; y < 3; y++)
    {
        for (int i = 0; i < AllSlots[y].size(); i++)
        {
            std::string SlotSpriteName = AllSlots[y][i]->GetName();
            FVector2D Location = AllSlots[y][i]->GetActorLocation();
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

                AllSlots[y][i]->SetName(_ItemName);
                AllSlots[y][i]->SetActorLocation(Location);
                AllSlots[y][i]->SetSprite(_SpriteName, _Index);
                AllSlots[y][i]->SetScale({ 14 * 3.5f, 14 * 3.5f });
                AllSlots[y][i]->SaveItemInfo(_SpriteName, _Index, { 14 * 3.5f, 14 * 3.5f });


                return;
            }

            else if (false == IsEmptySlot && SlotSpriteName != _ItemName)
            {
                continue;
            }

            else if (SlotSpriteName == _ItemName)
            {
                if (true == IsOver)
                {
                    SlotItemText(y, i);
                    return;

                }
                else if (false == IsOver)
                {
                    continue;

                }
            }
        }
    }
}

void APlayerUI::SlotItemText(int _Y, int _X)
{
    int CurItemCount = AllSlots[_Y][_X]->GetSlotItemCount();
    ++CurItemCount;
    AllSlots[_Y][_X]->SetSlotItemCount(CurItemCount);


    if (nullptr != AllSlots[_Y][_X]->GetText())
    {
        AllSlots[_Y][_X]->CountTextDestroy();
    }

    AllSlots[_Y][_X]->CountText();

    if (_Y >= 1)
    {
        if (nullptr != AllSlots[_Y][_X]->GetText())
        {
            AllSlots[_Y][_X]->GetText()->SetActive(false);
        }
    }
}

void APlayerUI::SlotItemChange()
{
    FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

    for (size_t y = 0; y < 3; y++)
    {
        for (size_t i = 0; i < 12; i++)
        {

            if (AllSlots[y][i]->GetIsSelectedItem() == 1 && false == IsChoose)
            {
                std::string SelectedName = AllSlots[y][i]->GetSelectedItemName();
                std::string SelectedSpriteName = AllSlots[y][i]->GetSelectedItemSpriteName();
                int SelectedIndex = AllSlots[y][i]->GetSelectedItemIndex();
                int ItemCount = AllSlots[y][i]->GetSlotItemCount();
                FVector2D ItemScale = AllSlots[y][i]->GetSelecteItemScale();

                SelectedItem = GetWorld()->SpawnActor<ASelectedItem>();
                SelectedItem->SetSprite(SelectedSpriteName, SelectedIndex, 3.0f);
                SelectedItem->SetSelectedItemSpriteName(SelectedSpriteName);
                SelectedItem->SetSelectedItemName(SelectedName);
                SelectedItem->SetSelectedItemIndex(SelectedIndex);
                SelectedItem->SetSelectedItemCount(ItemCount);
                SelectedItem->SetSelectedScale(ItemScale);

                AllSlots[y][i]->SetName("EmptySlot");
                AllSlots[y][i]->SetSprite("Slot.png", 0);
                AllSlots[y][i]->SetScale({ 16 * 3.5f, 16 * 3.5f });
                AllSlots[y][i]->SaveItemInfo("Slot.png", 0, { 16 * 3.5f, 16 * 3.5f });
                AllSlots[y][i]->SetSlotItemCount(0);
                if (ItemCount > 1)
                {
                    AllSlots[y][i]->CountTextDestroy();
                }

                IsChoose = true;
                AllSlots[y][i]->SetIsSelectedItem(0);

            }

            if (AllSlots[y][i]->GetIsSelectedItem() == 2 && false == IsChoose)
            {
                AllSlots[y][i]->SetIsSelectedItem(0);
            }

            if (AllSlots[y][i]->GetIsSelectedItem() == 2 && true == IsChoose)
            {
                IsChoose = false;
                std::string SelectedName = SelectedItem->GetSelectedItemName();
                std::string SelectedSpriteName = SelectedItem->GetSelectedItemSpriteName();
                FVector2D SelectedScale = SelectedItem->GetSelectedScale();
                int SelectedIndex = SelectedItem->GetSelectedItemIndex();
                int ItemCount = SelectedItem->GetSelectedItemCount();

                AllSlots[y][i]->SetSprite(SelectedSpriteName, SelectedIndex);
                AllSlots[y][i]->SetScale({ 14 * 3.5f,14 * 3.5f });
                AllSlots[y][i]->SetName(SelectedName);
                AllSlots[y][i]->SaveItemInfo(SelectedSpriteName, SelectedIndex, SelectedScale);
                AllSlots[y][i]->SetSlotItemCount(ItemCount);
                //AllSlots[y][i]->CountTextDestroy();

                if (ItemCount > 1)
                {

                    AllSlots[y][i]->CountText();
                }

                AllSlots[y][i]->SetIsSelectedItem(0);

                SelectedItem->Destroy();
                SelectedItem = nullptr;

            }

            if (true == AllSlots[y][i]->IsEqualItem && true == IsChoose)
            {
                std::string a = AllSlots[y][i]->GetName();
                std::string b = SelectedItem->GetName();
                if (AllSlots[y][i]->GetName() == SelectedItem->GetName())
                {

                    IsChoose = false;
                    std::string SelectedName = SelectedItem->GetSelectedItemName();
                    std::string SelectedSpriteName = SelectedItem->GetSelectedItemSpriteName();
                    FVector2D SelectedScale = SelectedItem->GetSelectedScale();
                    int SelectedIndex = SelectedItem->GetSelectedItemIndex();

                    int Plus = AllSlots[y][i]->GetSlotItemCount() + SelectedItem->GetSelectedItemCount();

                    AllSlots[y][i]->SetSprite(SelectedSpriteName, SelectedIndex);
                    AllSlots[y][i]->SetScale({ 14 * 3.5f,14 * 3.5f });
                    AllSlots[y][i]->SetName(SelectedName);
                    AllSlots[y][i]->SaveItemInfo(SelectedSpriteName, SelectedIndex, SelectedScale);
                    AllSlots[y][i]->SetSlotItemCount(Plus);

                    if (Plus > 1)
                    {
                        AllSlots[y][i]->CountTextDestroy();
                        AllSlots[y][i]->CountText();
                    }

                    AllSlots[y][i]->SetIsSelectedItem(0);
                    SelectedItem->SetSelectedItemCount(0);
                    BuyItemCount = 0;
                    SelectedItem->Destroy();
                    SelectedItem = nullptr;

                }
            }
        }
    }
}

void APlayerUI::BuyStoreItem()
{
    FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
    APlayer* Player = GetWorld()->GetPawn<APlayer>();

    if (PlayerManager::GetInst().GetGold() == 0)
    {
        return;
    }

    for (size_t i = 0; i < 9; i++)
    {
        if (AllStoreColumns[i]->GetIsSelectedItem() == 1 && false == IsChoose)
        {
            SellItem->SetPrice(AllStoreColumns[i]->GetName());
            int ItemPrice = SellItem->GetPrice();


            if (PlayerManager::GetInst().GetGold() >= ItemPrice)
            {
                std::string SelectedName = AllStoreColumns[i]->GetSelectedItemName();
                std::string SelectedSpriteName = AllStoreColumns[i]->GetSelectedItemSpriteName();
                int SelectedIndex = AllStoreColumns[i]->GetSelectedItemIndex();
                int ItemCount = AllStoreColumns[i]->GetSlotItemCount();
                FVector2D ItemScale = AllStoreColumns[i]->GetSelecteItemScale();

                SelectedItem = GetWorld()->SpawnActor<ASelectedItem>();
                SelectedItem->SetSprite(SelectedSpriteName, SelectedIndex, 3.0f);
                SelectedItem->SetSelectedItemSpriteName(SelectedSpriteName);
                SelectedItem->SetSelectedItemName(SelectedName);
                SelectedItem->SetSelectedItemIndex(SelectedIndex);
                SelectedItem->SetSelectedItemCount(ItemCount);
                SelectedItem->SetSelectedScale(ItemScale);
                SelectedItem->SetName(SelectedName);
                BuyItemCount = 1;
                SelectedItem->SetPrice(SelectedItem->GetName());

                int Price = SelectedItem->GetPrice();
                int CurGold = PlayerManager::GetInst().GetGold();
                int Purchase = CurGold - Price;

                PlayerManager::GetInst().SetGold(Purchase);

                if (ItemCount > 1)
                {
                    AllStoreColumns[i]->CountTextDestroy();
                }

                IsChoose = true;
                AllStoreColumns[i]->SetIsSelectedItem(0);
            }


        }

        if (AllStoreColumns[i]->GetIsSelectedItem() == 1 && SelectedItem != nullptr)
        {
            SellItem->SetPrice(AllStoreColumns[i]->GetName());
            int ItemPrice = SellItem->GetPrice();

            if (PlayerManager::GetInst().GetGold() >= ItemPrice)
            {
                std::string StoreName = AllStoreColumns[i]->GetName();
                std::string ItemName = SelectedItem->GetName();

                if (AllStoreColumns[i]->GetName() == SelectedItem->GetName())
                {
                    //BuyItemCount = SelectedItem->GetSelectedItemCount();
                    BuyItemCount += 1;
                    //SelectedItem->CountText();

                }
                SelectedItem->SetPrice(SelectedItem->GetName());
                int Price = SelectedItem->GetPrice();
                int CurGold = PlayerManager::GetInst().GetGold();
                int Purchase = CurGold - Price;
                PlayerManager::GetInst().SetGold(Purchase);
                CurText->SetActive(true);
                SelectedItem->SetSelectedItemCount(BuyItemCount);
                AllStoreColumns[i]->SetIsSelectedItem(0);
            }

        }

    }

}


void APlayerUI::SellStoreItem()
{
    EItemType Type = SellItem->SetItemType(AllSlots[SellSlotYNum][SellSlotXNum]->GetName());
    APlayer* Player = GetWorld()->GetPawn<APlayer>();

    if (true == SellClickCheck())
    {
        if (true == UEngineInput::GetInst().IsDown(VK_RBUTTON) && true == SellItem->ItemTypeCheck(Type))
        {
            int Count = AllSlots[SellSlotYNum][SellSlotXNum]->GetSlotItemCount();
            if (Count == 0)
            {
                return;
            }
            Count -= 1;


            if (Type == EItemType::Seed)
            {
                SellItem->SetPrice(AllSlots[SellSlotYNum][SellSlotXNum]->GetName());
                int Price = (SellItem->GetPrice()) / 2;
                int CurGold = PlayerManager::GetInst().GetGold();
                int Sell = CurGold + Price;
                PlayerManager::GetInst().SetGold(Sell);
            }

            if (Type == EItemType::Crop)
            {
                std::string Name = AllSlots[SellSlotYNum][SellSlotXNum]->GetName();
                SellItem->SetPrice(AllSlots[SellSlotYNum][SellSlotXNum]->GetName());
                int Price = (SellItem->GetPrice());
                int CurGold = PlayerManager::GetInst().GetGold();
                int Sell = CurGold + Price;
                PlayerManager::GetInst().SetGold(Sell);
            }

            if (Count == 0)
            {
                AllSlots[SellSlotYNum][SellSlotXNum]->SetSprite("Slot.png", 0);
                AllSlots[SellSlotYNum][SellSlotXNum]->SetScale({ 16 * 3.5f , 16 * 3.5f });
                AllSlots[SellSlotYNum][SellSlotXNum]->SetName("EmptySlot");
                AllSlots[SellSlotYNum][SellSlotXNum]->SaveItemInfo("Slot.png", 0, { 16 * 3.5f, 16 * 3.5f });

            }

            AllSlots[SellSlotYNum][SellSlotXNum]->SetSlotItemCount(Count);
            AllSlots[SellSlotYNum][SellSlotXNum]->CountTextDestroy();


            if (Count > 1)
            {
                AllSlots[SellSlotYNum][SellSlotXNum]->CountText();
            }

        }

    }


}

bool APlayerUI::SellClickCheck()
{
    for (int y = 0; y < 3; y++)
    {
        for (int i = 0; i < 12; i++)
        {
            if (true == AllSlots[y][i]->IsSell)
            {
                SellSlotYNum = y;
                SellSlotXNum = i;
                return true;
            }
        }
    }
    return false;
}


void APlayerUI::ItemExplainText()
{
    FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

    if (true == IsInventoryEnter)
    {
        std::string Name = Cursor->GetSlotName();
        if (Name != "EmptySlot")
        {
            ExplainNameText->SetActive(true);
            TextBoxTop->SetActive(true);
            TextBoxMid->SetActive(true);
            TextBoxBot->SetActive(true);
            Text->SetActive(true);
            Text->SetText(Name);
            TextBoxScale = ItemExplain(Name);

            Text2->SetActive(true);
            Text3->SetActive(true);
        }
    }


    if (false == IsInventoryEnter)
    {
        ExplainNameText->SetActive(false);
        TextBoxTop->SetActive(false);
        TextBoxMid->SetActive(false);
        TextBoxBot->SetActive(false);
        Text->SetActive(false);
        Text2->SetActive(false);
        Text3->SetActive(false);
    }
}

float APlayerUI::ItemExplain(std::string _Name)
{

    if (_Name == "Axe")
    {
        Text2Explain = "Tool";
        Text3Explain = "Used to chop wood";
    }
    else if (_Name == "Hoe")
    {
        Text2Explain = "Tool";
        Text3Explain = "Used to dig and till soil";
    }
    else if (_Name == "ParsnipSeed")
    {
        Text2Explain = "Seed";
        Text3Explain = "Plant these in the spring.";
    }
    else if (_Name == "BeanStarter")
    {
        Text2Explain = "Seed";
        Text3Explain = "Plant these in the spring. Keeps producing after that. Grows on a trellis.";
    }
    else if (_Name == "CauliflowerSeed")
    {
        Text2Explain = "Seed";
        Text3Explain = "Plant these in the spring. Takes a few days to produce a large cauliflower.";
    }
    else if (_Name == "PotatoSeed")
    {
        Text2Explain = "Seed";
        Text3Explain = "Plant these in the spring. Has a chance of yielding multiple potatoes at harvest.";
    }
    else if (_Name == "KaleSeed")
    {
        Text2Explain = "Seed";
        Text3Explain = "Plant these in the spring.";
    }
    else if (_Name == "RhubarbSeed")
    {
        Text2Explain = "Seed";
        Text3Explain = "Plant these in the spring.";
    }
    else if (_Name == "WateringCan")
    {
        Text2Explain = "Tool";
        Text3Explain = "Used to water crops. It can be refilled at any water source.";
    }
    else if (_Name == "Parsnip")
    {
        Text2Explain = "Crop";
        Text3Explain = "A spring tuber closely related to the carrot. It has an earthy taste and is full of nutrients.";
    }
    else if (_Name == "Cauliflower")
    {
        Text2Explain = "Crop";
        Text3Explain = "Valuable, but slow-growing. Despite its pale color, the florets are packed with nutrients. Cauliflower can become a Giant Crop.";
    }
    else if (_Name == "GreenBean")
    {
        Text2Explain = "Crop";
        Text3Explain = "A juicy little bean with a cool, crisp snap. This crop uses a trellis, and continues to produce after maturity.";
    }
    else if (_Name == "Kale")
    {
        Text2Explain = "Crop";
        Text3Explain = "The waxy leaves are great in soups and stir fries.";
    }
    else if (_Name == "Potato")
    {
        Text2Explain = "Crop";
        Text3Explain = "A widely cultivated tuber.";
    }
    else if (_Name == "Rhubarb")
    {
        Text2Explain = "Crop";
        Text3Explain = "The stalks are extremely tart, but make a great dessert when sweetened.";
    }

    Text2->SetText(Text2Explain);
    Text3->SetText(Text3Explain);

    float Scale = ExplianBoxScaleY + 25 * Text3->GetTextOverCount();

    TextBoxMid->SetComponentScale({ TextBoxMid->GetScale().X, Scale });
    return Scale;
}


void APlayerUI::UseItem()
{
    int Count = AllSlots[0][CurSlotNum]->GetSlotItemCount();
    Count -= 1;
    if (Count == 0)
    {
        AllSlots[0][CurSlotNum]->SetSprite("Slot.png", 0);
        AllSlots[0][CurSlotNum]->SetScale({ 16 * 3.5f , 16 * 3.5f });
        AllSlots[0][CurSlotNum]->SetName("EmptySlot");
        AllSlots[0][CurSlotNum]->SaveItemInfo("Slot.png", 0, { 16 * 3.5f, 16 * 3.5f });

        return;

    }

    AllSlots[0][CurSlotNum]->SetSlotItemCount(Count);
    AllSlots[0][CurSlotNum]->CountTextDestroy();
    if (Count > 1)
    {
        AllSlots[0][CurSlotNum]->CountText();
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

    for (int i = 0; i < 9; i++)
    {
        if (true == UEngineInput::GetInst().IsDown(i + Key))
        {
            BGMPlayer = UEngineSound::Play("toolSwap.wav");
            CurSlotNum = i;
            CurSlot->SetActorLocation(AllSlots[0][i]->GetActorLocation());
            return;
        }
    }

    if (true == UEngineInput::GetInst().IsDown('0'))
    {
        BGMPlayer = UEngineSound::Play("toolSwap.wav");

        CurSlotNum = 9;
        CurSlot->SetActorLocation(AllSlots[0][9]->GetActorLocation());
    }
    if (true == UEngineInput::GetInst().IsDown(VK_OEM_MINUS))
    {
        BGMPlayer = UEngineSound::Play("toolSwap.wav");

        CurSlotNum = 10;
        CurSlot->SetActorLocation(AllSlots[0][10]->GetActorLocation());
    }
    if (true == UEngineInput::GetInst().IsDown(VK_OEM_PLUS))
    {
        BGMPlayer = UEngineSound::Play("toolSwap.wav");

        CurSlotNum = 11;
        CurSlot->SetActorLocation(AllSlots[0][11]->GetActorLocation());
    }
}

bool APlayerUI::CulcolumsCheck()
{
    for (int i = 0; i < 4; i++)
    {
        bool IsCulColumns = AllStoreColumns[StartIndex + i]->GetIsStay();

        if (false == IsCulColumns)
        {
            continue;
        }
        else if (true == IsCulColumns)
        {
            return true;
        }
    }
    return false;
}

void APlayerUI::Copy(APlayerUI* _Value)
{
    APlayer* Player = GetWorld()->GetPawn<APlayer>();

    for (size_t y = 0; y < AllSlots.size(); y++)
    {
        for (size_t x = 0; x < AllSlots[y].size(); x++)
        {
            AllSlots[y][x]->Copy(_Value->AllSlots[y][x]);
            AllSlots[y][x]->SetActive(_Value->AllSlots[y][x]->GetActive());
            if (nullptr != _Value->AllSlots[y][x]->GetText())
            {
                AllSlots[y][x]->GetText()->SetActive(_Value->AllSlots[y][x]->GetText()->GetActive());
                AllSlots[y][x]->GetText()->SetActorLocation(_Value->AllSlots[y][x]->GetText()->GetActorLocation());

            }
            AllSlots[y][x]->SetActorLocation(_Value->AllSlots[y][x]->GetActorLocation());

        }
    }
    CurSlot->Copy(_Value->CurSlot);
    CurSlotNum = _Value->CurSlotNum;
    CurItem->Copy(_Value->CurItem);
    Min = _Value->Min;
    Week = _Value->Week;
    Day = _Value->Day;

    MinTime->Copy(_Value->MinTime);
    APText->Copy(_Value->APText);

    WeekText->Copy(_Value->WeekText);
    //DayText->Copy(_Value->DayText);
    HourTime->Copy(_Value->HourTime);

    Loc0 = _Value->Loc0;
    Loc0_2 = _Value->Loc0_2;
    Loc1 = _Value->Loc1;
    Loc1_2 = _Value->Loc1_2;

    IsOverDays =  _Value->IsOverDays;
    IsOpenIven = _Value->IsOpenIven;
    IsOpenStore = _Value->IsOpenStore;
    Inventory->SetActive(_Value->Inventory->GetActive());
    StoreInven->SetActive(_Value->StoreInven->GetActive());
    InvenPlayer->SetActive(_Value->InvenPlayer->GetActive());
    InventoryBar->SetActive(_Value->InventoryBar->GetActive());
    CurSlot->SetActive(_Value->CurSlot->GetActive());
}