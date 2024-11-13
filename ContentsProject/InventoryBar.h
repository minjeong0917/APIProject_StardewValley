#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
// ���� :
class AInventoryBar : public AActor
{
public:
	// constrcuter destructer
	AInventoryBar();
	~AInventoryBar();

	// delete Function
	AInventoryBar(const AInventoryBar& _Other) = delete;
	AInventoryBar(AInventoryBar&& _Other) noexcept = delete;
	AInventoryBar& operator=(const AInventoryBar& _Other) = delete;
	AInventoryBar& operator=(AInventoryBar&& _Other) noexcept = delete;

protected:

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	class USpriteRenderer* InvenBarSpriteRenderer = nullptr;

};

