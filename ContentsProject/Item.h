#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
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

protected:

private:
	class USpriteRenderer* ItemSpriteRenderer = nullptr;

};

