#pragma once
#include <EngineCore/Actor.h>

#include <EngineCore/2DCollision.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"
#include "Slot.h"

// Ό³Έν :
class AStoreColumn : public ASlot
{
public:
	// constrcuter destructer
	AStoreColumn();
	~AStoreColumn();

	// delete Function
	AStoreColumn(const AStoreColumn& _Other) = delete;
	AStoreColumn(AStoreColumn&& _Other) noexcept = delete;
	AStoreColumn& operator=(const AStoreColumn& _Other) = delete;
	AStoreColumn& operator=(AStoreColumn&& _Other) noexcept = delete;

	void SaveItemInfo(std::string _SpriteName, int _Index, float _Scale);

	int GetShopItemIndex()
	{
		return ItemIndex;
	}

	std::string GetShopItemSpriteName()
	{
		return ItemSpriteName;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	U2DCollision* CollisionComponent = nullptr;
	USpriteRenderer* ColumnSpriteRenderer = nullptr;

	int ItemIndex = 0;
	std::string ItemSpriteName = "NONE";
	float ItemScale = 0.0f;
};

