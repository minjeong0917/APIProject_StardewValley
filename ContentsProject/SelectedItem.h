#pragma once

#include "Item.h"
#include <EngineCore/ImageManager.h>

// Ό³Έν :
class ASelectedItem : public AItem
{
public:
	// constrcuter destructer
	ASelectedItem();
	~ASelectedItem();

	// delete Function
	ASelectedItem(const ASelectedItem& _Other) = delete;
	ASelectedItem(ASelectedItem&& _Other) noexcept = delete;
	ASelectedItem& operator=(const ASelectedItem& _Other) = delete;
	ASelectedItem& operator=(ASelectedItem&& _Other) noexcept = delete;
	void SetSprite(std::string _SprtieName, int _SpriteIndex, float _Scale);



protected:

private:
	class USpriteRenderer* ItemSpriteRenderer = nullptr;

};

