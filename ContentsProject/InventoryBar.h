#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
#include "Slot.h"
#include <list>

// Ό³Έν :
class AInventoryBar : public AActor
{
public:
	// constrcuter destructer
	AInventoryBar();
	~AInventoryBar();

	// delete Function
	AInventoryBar(const AInventoryBar& _Other) = delete;
	AInventoryBar(AInventoryBar&& _Other) noexcept = delete;
	AInventoryBar& operator=(const AInventoryBar& _Other) = delete;
	AInventoryBar& operator=(AInventoryBar&& _Other) noexcept = delete;

protected:

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	class USpriteRenderer* InvenBarSpriteRenderer = nullptr;
	std::vector<ASlot*> AllSlots;

};

