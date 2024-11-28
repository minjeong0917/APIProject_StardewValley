#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>
class AFarmMap : public AActor
{
public:
	// constrcuter destructer
	AFarmMap();
	~AFarmMap();

	// delete Function
	AFarmMap(const AFarmMap& _Other) = delete;
	AFarmMap(AFarmMap&& _Other) noexcept = delete;
	AFarmMap& operator=(const AFarmMap& _Other) = delete;
	AFarmMap& operator=(AFarmMap&& _Other) noexcept = delete;
	void SetSprite(std::string _SpriteName);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	USpriteRenderer* SpriteRenderer = nullptr;
};

