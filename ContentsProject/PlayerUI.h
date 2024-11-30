#pragma once
#include "Player.h"
#include <EngineCore/Actor.h>
#include <EnginePlatform/EngineSound.h>

#include "Cursor.h"
#include "Time.h"
#include "TileMap.h"
#include "Inventory.h"
#include "InventoryBar.h"
#include "Slot.h"
#include "Text.h"
#include "Gold.h"
#include "CurItem.h"
#include "SelectedItem.h"
#include "UI.h"
#include "Fade.h"

#include "PlayerToolsAnimation.h"

// Ό³Έν :
class APlayerUI : public AActor
{
public:
    friend class APlayer;
    // constrcuter destructer
    APlayerUI();
    ~APlayerUI();

    // delete Function
    APlayerUI(const APlayerUI& _Other) = delete;
    APlayerUI(APlayerUI&& _Other) noexcept = delete;
    APlayerUI& operator=(const APlayerUI& _Other) = delete;
    APlayerUI& operator=(APlayerUI&& _Other) noexcept = delete;
    void UIImageRender();
    void SlotCheck(AItem* _Item, std::string _ItemName, std::string _SpriteName, int _Index, bool IsOver);
    void SetCurSlot();
    void DefaultItem(FIntPoint _SlotIndex, std::string _SpriteName, std::string _ItemName, int _ItemIndex, FVector2D _Scale, FVector2D _Location = { 0,0 }, int ItemCount = 1);
    void AddItem(class AItem* _Item);

    int GetCulSlotNum()
    {
        return CurSlotNum;
    }
    std::string CurSlotItemName();

    void CurSlotItemSpawn();
    void UseItem();
    bool GetIsInventoryEnter()
    {
        return IsInventoryEnter;
    }

    int GetMin()
    {
        return Min;
    }
    bool IsBedIn = false;
protected:
    void BeginPlay();

    void Tick(float _DeltaTime);
    class UTimeEvent TimeEventer;

private:

    USoundPlayer BGMPlayer;
    void SlotItemText(int _Y, int _X);
    void ItemExplainText();
    float ItemExplain(std::string _Name);
    void SlotItemTextLocation(int X, int Y);
    void ToolsAnimationCheck();
    void ToolsAnimationTimer(float _DeltaTime, float _Duration);
    void SetAnimationDuration(float _Duration);
    void InventoryCheck();
    void StoreInvenCheck();
    void BuyStoreItem();

    void SlotItemChange();
    void ToolsAnimationDir(std::string _AnimationName, float _time);

    void ShopItemLists();
    void SellStoreItem();
    bool SellClickCheck();
    void SleepCheck();

    int Min = 0;
    int Week = 0;
    int Day = 0;
    int ItemCount = 0;
    bool TypeCheck = false;
    bool IsInventoryEnter = false;
    bool IsAnimationPlay = false;
    bool IsPlayerSleep = false;
    float Sleeptime = 0;

    FVector2D Loc0 = { 0,0 };
    FVector2D Loc0_2 = { 0,0 };

    FVector2D Loc1 = { 0,0 };
    FVector2D Loc1_2 = { 0,0 };
    int IsOpenIven = 0;
    int IsOpenStore = 0;
    ACursor* Cursor = nullptr;
    AUI* InvenPlayer = nullptr;
    APlayerToolsAnimation* ToolsAnimation = nullptr;

    AUI* ExplainNameText = nullptr;
    AUI* TextBoxTop = nullptr;
    AUI* TextBoxMid = nullptr;
    AUI* TextBoxBot = nullptr;
    AUI* StoreBox = nullptr;
    AUI* Tools = nullptr;
    AUI* StoreExitButton = nullptr;
    AUI* UpArrow = nullptr;
    AUI* DownArrow = nullptr;
    AUI* ClockHand = nullptr;

    AUI* BedTextBox = nullptr;
    AUI* YesTextBox = nullptr;
    AUI* NoTextBox = nullptr;

    AGold* BedText = nullptr;


    AFade* Fade = nullptr;
    AFade* Night = nullptr;

    ATime* MinTime = nullptr;
    ATime* HourTime = nullptr;

    AText* APText = nullptr;
    AText* WeekText = nullptr;

    AGold* Text = nullptr;
    AGold* Text2 = nullptr;
    AGold* Text3 = nullptr;

    AGold* StoreGoldText = nullptr;

    static std::string Text2Explain;
    static std::string Text3Explain;


    AGold* DayText = nullptr;

    AInventory* Inventory = nullptr;
    AInventory* StoreInven = nullptr;
    AInventoryBar* InventoryBar = nullptr;

    std::vector<std::vector<ASlot*>> AllSlots;
    std::vector<ASlot*> AllStoreColumns;
    std::vector<AGold*> AllStoreItemName;
    std::vector<AGold*> AllStoreItemPrice;
    std::vector<ASelectedItem*>AllStoreItem;

    ASlot* CulStoreColumn = nullptr;
    int CulStoreColumnNum = 1;
    bool CulcolumsCheck();


    ASlot* CurSlot = nullptr;
    ACurItem* CurItem = nullptr;
    AGold* CurText = nullptr;

    AGold* Gold = nullptr;

    ASelectedItem* SelectedItem = nullptr;
    ASelectedItem* SellItem = nullptr;


    bool IsEmptySlot = true;
    int CurSlotNum = 1;
    int SellSlotYNum = 0;
    int SellSlotXNum = 0;
    float NightTime = 0;
    FVector2D TextLocation = { 0,0 };
    bool IsSelected = false;

    int StartIndex = 0;
    int BuyItemCount = 0;
    float AnimationDuration = 0.0f;
    float AnimationTimer = 0.0f;
    float ExplianBoxScaleY = 0;
    float TextBoxScale = 0;
    bool IsChoose = false;
    bool IsShopChoose = false;

    void Copy(APlayerUI* _Slot);
};

