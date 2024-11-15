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
class PlayerUI : public AActor
{
public:
	// constrcuter destructer
	PlayerUI();
	~PlayerUI();

	// delete Function
	PlayerUI(const PlayerUI& _Other) = delete;
	PlayerUI(PlayerUI&& _Other) noexcept = delete;
	PlayerUI& operator=(const PlayerUI& _Other) = delete;
	PlayerUI& operator=(PlayerUI&& _Other) noexcept = delete;
	void UIImageRender();

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
};

