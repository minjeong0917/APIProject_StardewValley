#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>

enum class EItemType
{
	Wood,
	DUPivot,
	Weapon,
};

// Ό³Έν :
class AItem : public AActor
{
public:
	// constrcuter destructer
	AItem();
	~AItem();

	// delete Function
	AItem(const AItem& _Other) = delete;
	AItem(AItem&& _Other) noexcept = delete;
	AItem& operator=(const AItem& _Other) = delete;
	AItem& operator=(AItem&& _Other) noexcept = delete;

	void SetSprite(std::string _SprtieName, int _SpriteIndex, float _Scale);
	void SetForce();
	void GainItem(float _DeltaTime);
	void ItemTypeCheck(EItemType _ItemType);
	void SetItemType(std::string _ItemName);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
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


	EItemType Item = EItemType::DUPivot;

	int ItemCount = 0;
};

