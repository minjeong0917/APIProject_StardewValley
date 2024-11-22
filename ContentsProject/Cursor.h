#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/2DCollision.h>
#include "Slot.h"

// Ό³Έν :
class ACursor : public AActor
{
public:
	// constrcuter destructer
	ACursor();
	~ACursor();

	// delete Function
	ACursor(const ACursor& _Other) = delete;
	ACursor(ACursor&& _Other) noexcept = delete;
	ACursor& operator=(const ACursor& _Other) = delete;
	ACursor& operator=(ACursor&& _Other) noexcept = delete;

	void CollisionEnter(AActor* _ColActor);
	void CollisionEnd(AActor* _ColActor);
	void CollisionStay(AActor* _ColActor);

	bool GetIsEnter()
	{
		return IsEnter;
	}

	std::string GetSlotName()
	{
		return SlotName;
	}
protected:

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	class USpriteRenderer* CursorSpriteRenderer = nullptr;
	U2DCollision* CollisionComponent = nullptr;
	bool IsEnter = false;
	std::string SlotName = "NONE";
};


