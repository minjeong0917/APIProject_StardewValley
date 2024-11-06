#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>

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

	void RunSoundPlay();

	void LevelChangeStart();
	void LevelChangeEnd();
	void SetColImage(std::string_view _ColImageName);
	void SetBackImage(std::string_view _BackImageName);


	void LevelChangeCheck();
	void DebugCheck(float _DeltaTime);
	void PlayerMove(float _DeltaTime);
	void CameraCheck();

	void SetTileMap(class ATileMap* _TileMap)
	{
		TileMap = _TileMap;
	}
	
protected:

private:

	float Speed = 200.0f;
	int MySpriteIndex = 0;
	class USpriteRenderer* SpriteRenderer;
	class UEngineWinImage* ColImage = nullptr;
	class UEngineWinImage* BackImage = nullptr;

	class ATileMap* TileMap = nullptr;

	bool ColorCheck = false;
	bool TileCheck = false;
};

