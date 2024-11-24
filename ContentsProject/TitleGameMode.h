#pragma once
#include <EngineCore/GameMode.h>
#include <EngineCore/SpriteRenderer.h>
#include "TitleLogo.h"
#include "UI.h"
#include "TitleButton.h"
#include "Cursor.h"


class ATitleGameMode : public AGameMode
{
public:
	// constrcuter destructer
	ATitleGameMode();
	~ATitleGameMode();

	// delete Function
	ATitleGameMode(const ATitleGameMode& _Other) = delete;
	ATitleGameMode(ATitleGameMode&& _Other) noexcept = delete;
	ATitleGameMode& operator=(const ATitleGameMode& _Other) = delete;
	ATitleGameMode& operator=(ATitleGameMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;

	void Tick(float _DeltaTime) override;
	void CameraMove(float _DeltaTime);
	void UIMove(ATitleLogo* _ATitleLogo, float _DeltaTime, FVector2D Pos);


private:
	USpriteRenderer* SpriteRenderer = nullptr;
	ATitleLogo* Logo = nullptr;
	ATitleLogo* LogoAnimation = nullptr;
	ATitleLogo* Tree = nullptr;
	ATitleLogo* Mountain_1 = nullptr;
	ATitleLogo* Mountain_2 = nullptr;
	ATitleButton* NewButton = nullptr;

	ACursor* Cursor = nullptr;

	float Speed = 150.0f;
	FVector2D CameraPos = { 0,0 };
	FVector2D TreePos = { 0,0 };
	FVector2D Mountain1Pos = { 0,0 };
	FVector2D Mountain2Pos = { 0,0 };
	bool IsArrive = false;

};

