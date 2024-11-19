#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
#include "ContentsEnum.h"
enum class EItemType
{
	
	Wood,
	Crop,
	DUPivot,
	EmptySlot,
	Tools,
};

// Ό³Έν :
class AItem : public AActor
{
public:
	// constrcuter destructer
	AItem();
	virtual ~AItem();

	// delete Function
	AItem(const AItem& _Other) = delete;
	AItem(AItem&& _Other) noexcept = delete;
	AItem& operator=(const AItem& _Other) = delete;
	AItem& operator=(AItem&& _Other) noexcept = delete;

	void ItemSetSprite(std::string _SprtieName, int _SpriteIndex, float _Scale);
	void SetForce();
	bool ItemTypeCheck(EItemType _ItemType);
	EItemType SetItemType(std::string _ItemName);
	void SetOrder(ERenderOrder _Order);
	void GainItemInfo(std::string _ItemName, std::string _SpriteName, int _ItemIndex, float _ItemScale);
	void SetCameraEffect(bool _IsCamera = true);

	int GetItemIndex()
	{
		return GainItemIndex;
	}

	std::string GetItemSpriteName()
	{
		return GainItemSpriteName;
	}
	std::string GetItemName()
	{
		return GainItemName;
	}

	EItemType GetItemType()
	{
		return Item;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void GainItem(float _DeltaTime);
	void Force(float _DeltaTime);
	void DestroyItem();

	class USpriteRenderer* ItemSpriteRenderer = nullptr;

	FVector2D ForceDir;
	float Speed = 0.0f;
	float CurSpeed = 0.0f;
	float SlowSpeed = 200.0f;
	float Time = 0;

	FVector2D UpForceDir;
	float UpForce = 300.0f;
	float CurUpForce = 300.0f;
	float UpSlowSpeed = 1000.0f;

	bool IsIn = false;
	int JumpCount = 0;

	int GainItemIndex = 0;
	float GainItemScale = 0;
	std::string GainItemSpriteName = "NONE";
	std::string GainItemName = "NONE";

	EItemType Item = EItemType::DUPivot;
	//int ItemCount = 0;
};

