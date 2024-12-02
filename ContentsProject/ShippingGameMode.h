#pragma once
#include <EngineCore/GameMode.h>
#include <EngineCore/SpriteRenderer.h>


#include "UI.h"
#include "Cursor.h"
#include "PlayerUI.h"
#include "Player.h"

// Ό³Έν :
class AShippingGameMode : public AGameMode
{
public:
	// constrcuter destructer
	AShippingGameMode();
	~AShippingGameMode();

	// delete Function
	AShippingGameMode(const AShippingGameMode& _Other) = delete;
	AShippingGameMode(AShippingGameMode&& _Other) noexcept = delete;
	AShippingGameMode& operator=(const AShippingGameMode& _Other) = delete;
	AShippingGameMode& operator=(AShippingGameMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;

	void Tick(float _DeltaTime) override;
private:
	USpriteRenderer* SpriteRenderer = nullptr;
	ACursor* Cursor = nullptr;
	USoundPlayer BGMPlayer;
	AUI* FarmingBox = nullptr;
	AUI* FaragingBox = nullptr;
	AUI* FishingBox = nullptr;
	AUI* MiningBox = nullptr;
	AUI* OtherBox = nullptr;
	AUI* TotalBox = nullptr;
	AUI* OKButton = nullptr;

	AGold* FarmingText = nullptr;
	AGold* FaragingText = nullptr;
	AGold* FishingText = nullptr;
	AGold* MiningText = nullptr;
	AGold* OtherText = nullptr;
	AGold* TotalText = nullptr;

	AGold* FarmingGold = nullptr;
	AGold* FaragingGold = nullptr;
	AGold* FishingGold = nullptr;
	AGold* MiningGold = nullptr;
	AGold* OtherGold = nullptr;
	AGold* TotalGold = nullptr;
	int Count = 0;
	int Count1 = 0;
	int Count2 = 0;
	int Count3 = 0;
	int Count4 = 0;
	int Count5 = 0;

	float Time = 0;
	bool IsPlayOnce = false;

};

