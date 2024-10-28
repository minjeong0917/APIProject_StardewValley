#pragma once
#include <EngineCore/Actor.h>

class ATools : public AActor
{
public:
	// constrcuter destructer
	ATools();
	~ATools();

	// delete Function
	ATools(const ATools& _Other) = delete;
	ATools(ATools&& _Other) noexcept = delete;
	ATools& operator=(const ATools& _Other) = delete;
	ATools& operator=(ATools&& _Other) noexcept = delete;

protected:
	void Tick(float _DeltaTime) override;

private:

};

