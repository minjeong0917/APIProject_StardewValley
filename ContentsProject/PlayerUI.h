#pragma once
#include "Player.h"
#include <EngineCore/Actor.h>

#include "Cursor.h"
#include "Time.h"
#include "TileMap.h"
#include "Inventory.h"
#include "InventoryBar.h"
#include "Slot.h"

// Ό³Έν :
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
	void SlotCheck(std::string _SpriteName, int _Index);

protected:
	void BeginPlay();

	void Tick(float _DeltaTime);

private:
	ACursor* Cursor = nullptr;
	ATime* MinTime = nullptr;
	ATime* HourTime = nullptr;
	ASlot* Slot_1 = nullptr;
	AInventory* Inventory = nullptr;
	AInventoryBar* InventoryBar = nullptr;

	std::vector<ASlot*> AllSlots;
	bool IsEmptySlot = true;
};

