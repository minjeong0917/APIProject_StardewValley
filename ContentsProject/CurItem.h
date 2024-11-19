#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ActorComponent.h>
#include <EngineCore/ImageManager.h>
#include "Item.h"

// Ό³Έν :
class ACurItem : public AActor
{
public:
	// constrcuter destructer
	ACurItem();
	~ACurItem();

	// delete Function
	ACurItem(const ACurItem& _Other) = delete;
	ACurItem(ACurItem&& _Other) noexcept = delete;
	ACurItem& operator=(const ACurItem& _Other) = delete;
	ACurItem& operator=(ACurItem&& _Other) noexcept = delete;
	void SetSprite(std::string _SprtieName, int _SpriteIndex, float _Scale);
	bool ItemTypeCheck(EItemType _ItemType);
	EItemType SetItemType(std::string _ItemName);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	class USpriteRenderer* CurItemSpriteRenderer = nullptr;
	EItemType ItemType = EItemType::DUPivot;

};

