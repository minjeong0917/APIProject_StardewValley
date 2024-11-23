#pragma once
#include "Player.h"
#include <EngineCore/Actor.h>

#include "Cursor.h"
#include "Time.h"
#include "TileMap.h"
#include "Inventory.h"
#include "InventoryBar.h"
#include "Slot.h"
#include "Text.h"
#include "Gold.h"
#include "CurItem.h"
#include "UI.h"
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

protected:
    void BeginPlay();

    void Tick(float _DeltaTime);

private:
    void SlotItemText(int _Y, int _X);
    void ItemExplainText();
    int ItemExplain(std::string _Name);
    void SlotItemTextLocation(int X, int Y);
    void ToolsAnimationCheck();
    void ToolsAnimationTimer(float _DeltaTime, float _Duration);
    void SetAnimationDuration(float _Duration);
    void InventoryCheck();
    void SlotItemChange();
    void ToolsAnimationDir(std::string _AnimationName, float _time);

    bool TypeCheck = false;
    bool IsInventoryEnter = false;
    bool IsAnimationPlay = false;

    int IsOpenIven = 0;
    ACursor* Cursor = nullptr;
    AUI* InvenPlayer = nullptr;
    APlayerToolsAnimation* ToolsAnimation = nullptr;

    AUI* ExplainNameText = nullptr;
    AUI* TextBoxTop = nullptr;
    AUI* TextBoxMid = nullptr;
    AUI* TextBoxBot = nullptr;

    AUI* Tools = nullptr;


    ATime* MinTime = nullptr;
    ATime* HourTime = nullptr;

    AText* APText = nullptr;
    AText* WeekText = nullptr;

    AGold* Text = nullptr;
    AGold* Text2 = nullptr;
    AGold* Text3 = nullptr;

    std::string Text2Explain = "NONE";
    std::string Text3Explain = "NONE";


    AGold* DayText = nullptr;

    AInventory* Inventory = nullptr;
    AInventoryBar* InventoryBar = nullptr;

    std::vector<std::vector<ASlot*>> AllSlots;

    ASlot* CurSlot = nullptr;
    ACurItem* CurItem = nullptr;
    AGold* CurText = nullptr;

    class ASelectedItem* SelectedItem = nullptr;

    bool IsEmptySlot = true;
    int CurSlotNum = 1;
    FVector2D TextLocation = { 0,0 };
    bool IsSelected = false;

    float AnimationDuration = 0.0f;
    float AnimationTimer = 0.0f;
    float ExplianBoxScaleY = 0;
    int TextBoxScale = 0;
    bool IsChoose = false;
};

