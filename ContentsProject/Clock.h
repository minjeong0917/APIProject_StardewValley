#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>

// Ό³Έν :
class AClock : public AActor
{
public:
	// constrcuter destructer
	AClock();
	~AClock();

	// delete Function
	AClock(const AClock& _Other) = delete;
	AClock(AClock&& _Other) noexcept = delete;
	AClock& operator=(const AClock& _Other) = delete;
	AClock& operator=(AClock&& _Other) noexcept = delete;
	void SetActive(bool _Active);

protected:

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	class USpriteRenderer* ClockSpriteRenderer = nullptr;

};

