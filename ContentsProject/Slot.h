#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
#include <EngineCore/2DCollision.h>
#include <EngineCore/SpriteRenderer.h>
#include "Gold.h"

#include "SelectedItem.h"

#include "ContentsEnum.h"

// Ό³Έν :
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
	//void SetColisionLocation(FVector2D _Location);
	void SetScale(FVector2D _Scale);
	void SetOrder(ERenderOrder _RenderOder);
	void CollisionDestroy();

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


	void SaveItemInfo(std::string _SpriteName, int _Index, FVector2D _Scale);


	int GetItemIndex()
	{
		return ItemIndex;
	}
	std::string GetItemSpriteName()
	{
		return ItemSpriteName;
	}

	FVector2D GetItemScale()
	{
		return ItemScale;
	}
	void SetTextLocation(FVector2D _Location);

	void CollisionStay(AActor* _ColActor);
	void CollisionEnd(AActor* _ColActor);
	void CollisionEnter(AActor* _ColActor);
	void CountTextLocation(FVector2D _Loc);


	int GetIsSelectedItem()
	{
		return IsSelectedItem;
	}
	
	void SetIsSelectedItem(int _Value)
	{
		IsSelectedItem = _Value;
	}

	std::string GetSelectedItemName()
	{
		return SelectedItemName;
	}

	std::string GetSelectedItemSpriteName()
	{
		return SelectedItemSpriteName;
	}

	int GetSelectedItemIndex()
	{
		return SelectedItemIndex;
	}

	FVector2D GetSelecteItemScale()
	{
		return SelecteItemScale;
	}

	void SetSelecteItemScale(FVector2D _SelecteItemScale)
	{
		SelecteItemScale = _SelecteItemScale;
	}

	void CountTextDestroy();
	bool GetIsStay()
	{
		return IsStay;
	}
	void SetCollisionComponentScale(FVector2D Scale);
	bool IsEqualItem = false;
	bool IsSell = false;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	int SlotItemCount = 1;
	bool IsStay = false;

	U2DCollision* CollisionComponent = nullptr;
	USpriteRenderer* SlotSpriteRenderer = nullptr;
	AGold* Text = nullptr;
	ASelectedItem* Price = nullptr;
	int ItemIndex = 0;
	std::string ItemSpriteName = "NONE";
	FVector2D ItemScale = {0,0};

	int IsSelectedItem = 0;

	std::string SelectedItemName = "NONE";
	std::string SelectedItemSpriteName = "NONE";
	int SelectedItemIndex = 0;
	FVector2D SelecteItemScale = { 0,0 };
};

