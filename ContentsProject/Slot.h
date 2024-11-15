#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
#include <EngineCore/2DCollision.h>
#include <vector>
//#include "Item.h"

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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	U2DCollision* CollisionComponent = nullptr;
	class USpriteRenderer* SlotSpriteRenderer = nullptr;
	std::vector<std::string> ItemName;
};

