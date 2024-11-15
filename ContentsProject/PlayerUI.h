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

// ���� :
class APlayerUI : public AActor
{
public:

	// constrcuter destructer
	APlayerUI();
	~APlayerUI();

	// delete Function
	APlayerUI(const APlayerUI& _Other) = delete;
	APlayerUI(APlayerUI&& _Other) noexcept = delete;
	APlayerUI& operator=(const APlayerUI& _Other) = delete;
	APlayerUI& operator=(APlayerUI&& _Other) noexcept = delete;
	void UIImageRender();
	//void SlotCheck(std::string _SpriteName, int _Index);

	void AddItem(class AItem* _Item);


protected:
	void BeginPlay();

	void Tick(float _DeltaTime);

private:
	ACursor* Cursor = nullptr;
	ATime* MinTime = nullptr;
	ATime* HourTime = nullptr;
	AText* APText = nullptr;
	AText* DayText = nullptr;
	AInventory* Inventory = nullptr;
	AInventoryBar* InventoryBar = nullptr;

	std::vector<ASlot*> AllSlots;
	// std::vector<ASlot*> AllSlots;
	bool IsEmptySlot = true;


};

