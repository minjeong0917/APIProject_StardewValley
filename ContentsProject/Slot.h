#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
#include <EngineCore/2DCollision.h>
#include <EngineCore/SpriteRenderer.h>


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
	void SetColisionLocation(FVector2D _Location);
	void SetScale(FVector2D _Scale);
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
	FVector2D GeScale()
	{
		return SlotSpriteRenderer->GetComponentScale();
	}
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	int SlotItemCount = 1;
	U2DCollision* CollisionComponent = nullptr;
	USpriteRenderer* SlotSpriteRenderer = nullptr;
};

