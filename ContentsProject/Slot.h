#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
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

protected:

private:
	class USpriteRenderer* SlotSpriteRenderer = nullptr;
	std::vector<std::string> ItemName;
};

