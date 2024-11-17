#include "PreCompile.h"
#include "TitleGameMode.h"

#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include "ContentsEnum.h"

#include "TitleLogo.h"

ATitleGameMode::ATitleGameMode()
{
	{
		USpriteRenderer* SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetOrder(ERenderOrder::BACKGROUND);
		SpriteRenderer->SetSprite("TitleBackGround.png");
		FVector2D MapScale = SpriteRenderer->SetSpriteScale(2.0f);
		SpriteRenderer->SetComponentLocation(MapScale.Half());
	}
}

ATitleGameMode::~ATitleGameMode()
{
}


void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();
	//ATitleLogo* Logo = GetWorld()->SpawnActor<ATitleLogo>();
	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	GetWorld()->SetCameraPivot(Size.Half() * -1.0f);
}


void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Farm");
	}
	CameraMove(_DeltaTime);
}

void ATitleGameMode::CameraMove(float _DeltaTime)
{
	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

	GetWorld()->SetCameraToMainPawn(false);
	//GetWorld()->SetCameraPos();

	FVector2D CameraPos = GetWorld()->GetCameraPos();


}