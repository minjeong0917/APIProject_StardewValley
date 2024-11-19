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
	void DefaultItem(FIntPoint _SlotIndex, std::string _SpriteName, std::string _ItemName, int _ItemIndex, FVector2D _Scale, FVector2D _Location = {0,0});

	void AddItem(class AItem* _Item);

	int GetCulSlotNum()
	{
		return CurSlotNum;
	}
	std::string CurSlotItemName();
	//bool CurSlotItemTypeCheck(AItem* _Item);

	void CurSlotItemSpawn();


protected:
	void BeginPlay();

	void Tick(float _DeltaTime);

private:
	bool TypeCheck = false;
	int IsOpenIven = 0;
	ACursor* Cursor = nullptr;

	ATime* MinTime = nullptr;
	ATime* HourTime = nullptr;

	AText* APText = nullptr;
	AText* WeekText = nullptr;
	AGold* DayText = nullptr;

	AInventory* Inventory = nullptr;
	AInventoryBar* InventoryBar = nullptr;

	std::vector<std::vector<ASlot*>> AllSlots;

	ASlot* CurSlot = nullptr;
	ACurItem* CurItem = nullptr;

	bool IsEmptySlot = true;

	AGold* CurText = nullptr;
	int CurSlotNum = 1;
};

