#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
#include <EngineCore/2DCollision.h>
#include <EngineCore/SpriteRenderer.h>
#include "Gold.h"
#include "Item.h"

#include "ContentsEnum.h"

// ���� :
class ASlot : public AActor
{
public:
	// constrcuter destructer
	ASlot();
	~ASlot();

	// delete Function
	ASlot(const ASlot& _Other) = delete;
	ASlot(ASlot&& _Other) noexcept = delete;
	ASlot& operator=(const ASlot& _Other) = delete;
	ASlot& operator=(ASlot&& _Other) noexcept = delete;
	void SetSprite(std::string _SprtieName, int _SpriteIndex);
	void SetComponentLocation(FVector2D _Location);
	void SetColisionLocation(FVector2D _Location);
	void SetScale(FVector2D _Scale);
	void SetOrder(ERenderOrder _RenderOder);

	void SetSlotItemCount(int _Value)
	{
		SlotItemCount = _Value;
	}
	int GetSlotItemCount()
	{
		return SlotItemCount;
	}
	FVector2D GetLocation()
	{
		return SlotSpriteRenderer->GetComponentLocation();
	}
	FVector2D GetScale()
	{
		return SlotSpriteRenderer->GetComponentScale();
	}
	void CountText();

	AGold* GetText()
	{
		return Text;
	}

	void ItemInfoSave(AItem* _Item);

	EItemType GetItemType()
	{
		return ItemType;
	}

	std::string GetItemSpriteName()
	{
		return ItemSpriteName;
	}

	int GetItemIndex()
	{
		return ItemIndex;
	}
	
	bool GetItemTypeCheck()
	{
		return IsItem;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	int SlotItemCount = 1;
	U2DCollision* CollisionComponent = nullptr;
	USpriteRenderer* SlotSpriteRenderer = nullptr;
	AGold* Text = nullptr;
	AItem* Item = nullptr;

	EItemType ItemType = EItemType::DUPivot;
	std::string ItemSpriteName = "NONE";
	bool IsItem = false;
	int ItemIndex = 0;

};

