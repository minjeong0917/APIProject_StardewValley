#pragma once
#include <EngineCore/GameMode.h>


// Ό³Έν :
class ATownGameMode : public AGameMode
{
public:
	// constrcuter destructer
	ATownGameMode();
	~ATownGameMode();

	// delete Function
	ATownGameMode(const ATownGameMode& _Other) = delete;
	ATownGameMode(ATownGameMode&& _Other) noexcept = delete;
	ATownGameMode& operator=(const ATownGameMode& _Other) = delete;
	ATownGameMode& operator=(ATownGameMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;

	void Tick(float _DeltaTime) override;
private:

};

