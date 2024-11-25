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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	U2DCollision* CollisionComponent = nullptr;
	USpriteRenderer* ColumnSpriteRenderer = nullptr;
};

