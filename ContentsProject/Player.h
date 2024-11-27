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
#include "Slot.h"
#include "PlayerUI.h"
#include "SelectedItem.h"
// Ό³Έν :
class APlayer : public AActor
{
public:
	//friend class AFarmGameMode;
	//friend class APlayerUI;
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
	void SetGold(int _Value)
	{
		PlayerGold = _Value;
	}

	EPlayerDir PlayerDir = EPlayerDir::Down;

	bool IsPlayerMove = false;
	bool IsOpenIven = false;
	bool IsMouseInPlayerPos = false;

	Tile* TreeTile = nullptr;
	Tile* PreviousTreeTile = nullptr;

	void AddItem(class AItem* _Item);
	int GetCurSlotNum();
	std::string CurSlotCheck();

	void PlayerAnimationTimer(float _DeltaTime, float _Duration);
	void SetAnimationDuration(float _Duration);
	void UseItem();


	std::string GetSelectedItemName()
	{
		return SelectedItemName;
	}

	std::string GetSelectedItemSpriteName()
	{
		return SelectedItemSpriteName;
	}

	int GetSelectedItemIndex()
	{
		return SelectedItemIndex;
	}

	bool GetIsEnter()
	{
		return IsEnter;
	}
	bool IsButtonClick = false;

protected:

private:
	bool IsAnimationPlay = false;
	std::string TileLocationName();
	void TileAlphaCheck(std::string _TileName);

	float Speed = 220.0f;
	int MySpriteIndex = 0;
	bool IsEnter = false;

	class USpriteRenderer* SpriteRenderer;
	class UEngineWinImage* ColImage = nullptr;
	class UEngineWinImage* BackImage = nullptr;
	class ATileMap* FarmTileMap = nullptr;
	class AFarmGameMode* FarmGameMode = nullptr;
	class APlayerUI* PlayerUI = nullptr;

	bool ColorCheck = false;

	bool TileCheck = true;
	int PlayerGold = 200;

	USoundPlayer BGMPlayer;


	float AnimationDuration = 0.0f;
	float AnimationTimer = 0.0f;

	std::string SelectedItemName = "NONE";
	std::string SelectedItemSpriteName = "NONE";
	int SelectedItemIndex = 0;

	static APlayer* PrevPlayer;
};

