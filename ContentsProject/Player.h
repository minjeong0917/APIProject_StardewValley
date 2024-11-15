#pragma once
#include <EnginePlatform/EngineSound.h>
#include <EngineCore/Actor.h>
#include <EngineCore/ImageManager.h>
#include "ContentsEnum.h"
#include "Cursor.h"
#include "Time.h"
#include "TileMap.h"
#include "Inventory.h"
#include "InventoryBar.h"
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

	void CameraCheck();

	void SetTileMap(class ATileMap* _TileMap)
	{
		FarmTileMap = _TileMap;
	}

	int GetGold()
	{
		return PlayerGold;
	}
	void UIImageRender();


	EPlayerDir PlayerDir = EPlayerDir::Down;
	bool IsPlayerMove = false;
	bool IsMouseInPlayerPos = false;
	Tile* TreeTile = nullptr;
	Tile* PreviousTreeTile = nullptr;
protected:

private:
	std::string TileLocationName();
	void TileAlphaCheck(std::string _TileName);
	float Speed = 220.0f;
	int MySpriteIndex = 0;
	class USpriteRenderer* SpriteRenderer;
	class UEngineWinImage* ColImage = nullptr;
	class UEngineWinImage* BackImage = nullptr;
	class ATileMap* FarmTileMap = nullptr;
	class AFarmGameMode* FarmGameMode = nullptr;

	bool ColorCheck = false;
	int IsOpenIven = 0;
	bool TileCheck = true;
	int PlayerGold = 789;

	ACursor* Cursor = nullptr;
	ATime* MinTime = nullptr;
	ATime* HourTime = nullptr;

	AInventory* Inventory = nullptr;
	AInventoryBar* InventoryBar = nullptr;
	USoundPlayer BGMPlayer;
};

