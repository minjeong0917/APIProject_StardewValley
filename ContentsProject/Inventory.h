#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
// ���� :
class AInventory : public AActor
{
public:
	// constrcuter destructer
	AInventory();
	~AInventory();

	// delete Function
	AInventory(const AInventory& _Other) = delete;
	AInventory(AInventory&& _Other) noexcept = delete;
	AInventory& operator=(const AInventory& _Other) = delete;
	AInventory& operator=(AInventory&& _Other) noexcept = delete;
	void SetSprite(std::string _SpriteName, int _Index);
	void SetComponentScale(FVector2D _Scale);

protected:

private:
	class USpriteRenderer* InvenSpriteRenderer = nullptr;

};

