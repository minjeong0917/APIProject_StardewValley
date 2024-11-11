#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
#include "ContentsEnum.h"

// Ό³Έν :
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
	void PlayerAnimation();
	void PlayerAnimationPlay();
	void RunSoundPlay();

	void LevelChangeStart();
	void LevelChangeEnd();
	void SetColImage(std::string_view _ColImageName);
	void SetBackImage(std::string_view _BackImageName);


	void LevelChangeCheck();
	void DebugCheck(float _DeltaTime);

	FVector2D PlayerMoveDir();

	void PlayerMove(float _DeltaTime);
	void BackImgCollisionCheck(FVector2D _Vector);
	void TileMapCollisionCheck(FVector2D _Vector);
	void TileDestroy();

	void CameraCheck();

	void SetTileMap(class ATileMap* _TileMap)
	{
		TileMap = _TileMap;
	}

	int GetGold()
	{
		return Gold;
	}

	EPlayerDir PlayerDir = EPlayerDir::Down;
	bool IsPlayerMove = false;

protected:

private:

	float Speed = 220.0f;
	int MySpriteIndex = 0;
	class USpriteRenderer* SpriteRenderer;
	class UEngineWinImage* ColImage = nullptr;
	class UEngineWinImage* BackImage = nullptr;
	class ATileMap* TileMap = nullptr;
	bool ColorCheck = false;
	bool TileCheck = true;
	int Gold = 789;
};

