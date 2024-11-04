#pragma once
#include <EngineCore/Actor.h>

// ���� :
class APlayer : public AActor
{
public:
	// constrcuter destructer
	APlayer();
	~APlayer();

	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void RunSoundPlay();

	void LevelChangeStart();
	void LevelChangeEnd();

	void PlayerMove(float _DeltaTime);
	void CameraCheck(float _DeltaTime);

protected:

private:

	float Speed = 150.0f;
	int MySpriteIndex = 0;

	bool IsXMove = false;
	bool IsYMove = false;


	class USpriteRenderer* SpriteRenderer;


};

