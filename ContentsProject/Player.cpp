#include "PreCompile.h"
#include "Player.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EnginePlatform/EngineInput.h>


void APlayer::RunSoundPlay()
{

}

APlayer::APlayer()
{
	SetActorLocation({ 1000, 1000 });

	{
		SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
		SpriteRenderer->SetSprite("Farmer_Right.png");
		SpriteRenderer->SetSprite("Farmer_Left.png");

		SpriteRenderer->SetComponentScale({ 166.4f, 332.8f });

		SpriteRenderer->CreateAnimation("Walk_Front", "Farmer_Right.png", { 1, 0, 2, 0 }, { 0.1f, 0.1f, 0.1f, 0.1f });
		SpriteRenderer->CreateAnimation("Idle_front", "Farmer_Right.png", 0, 0, 0.1f);
		SpriteRenderer->CreateAnimation("Walk_Back", "Farmer_Right.png", { 12, 11, 13, 11 }, { 0.1f, 0.1f, 0.1f, 0.1f });
		SpriteRenderer->CreateAnimation("Idle_Back", "Farmer_Right.png", 11, 11, 0.1f);

		SpriteRenderer->CreateAnimation("Walk_Right", "Farmer_Right.png", { 7, 8 }, { 0.1f, 0.1f });
		SpriteRenderer->CreateAnimation("Idle_Right", "Farmer_Right.png", 6,6, 0.1f);
		SpriteRenderer->CreateAnimation("Walk_Left", "Farmer_Left.png", { 7, 8 }, { 0.1f, 0.1f });
		SpriteRenderer->CreateAnimation("Idle_Left", "Farmer_Left.png", 6, 6, 0.1f);

		SpriteRenderer->ChangeAnimation("Idle_front");
	}

	{
	}


}

APlayer::~APlayer()
{
}


void APlayer::BeginPlay()
{
	Super::BeginPlay();

	// 카메라 피벗 위치 설정
	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	GetWorld()->SetCameraPivot(Size.Half() * -1.0f);


}


void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));

	UEngineDebug::CoreOutPutString("PlayerPos : " + GetActorLocation().ToString());

	if (true == UEngineInput::GetInst().IsDown('R'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Title");
	}
	if (true == UEngineInput::GetInst().IsDown('T'))
	{
		UEngineAPICore::GetCore()->OpenLevel("Town");
	}

	if (true == UEngineInput::GetInst().IsDown(VK_F1))
	{
		 UEngineDebug::SwitchIsDebug();
	}

	// 오른쪽 이동
	if (true == UEngineInput::GetInst().IsPress('D'))
	{
		SpriteRenderer->ChangeAnimation("Walk_Right");
		AddActorLocation(FVector2D::RIGHT * _DeltaTime * Speed);
	}
	else if (true == UEngineInput::GetInst().IsUp('D'))
	{
		SpriteRenderer->ChangeAnimation("Idle_Right");
	}

	// 왼쪽 이동
	if (true == UEngineInput::GetInst().IsPress('A'))
	{
		SpriteRenderer->ChangeAnimation("Walk_Left");
		AddActorLocation(FVector2D::LEFT * _DeltaTime * Speed);
	}
	else if (true == UEngineInput::GetInst().IsUp('A'))
	{
		SpriteRenderer->ChangeAnimation("Idle_Left");
	}

	// 아래쪽 이동
	if (true == UEngineInput::GetInst().IsPress('S'))
	{
		SpriteRenderer->ChangeAnimation("Walk_Front");
		AddActorLocation(FVector2D::DOWN * _DeltaTime * Speed);
	}
	else if (true == UEngineInput::GetInst().IsUp('S'))
	{
		SpriteRenderer->ChangeAnimation("Idle_front");
	}

	// 위쪽 이동
	if (true == UEngineInput::GetInst().IsPress('W'))
	{
		SpriteRenderer->ChangeAnimation("Walk_Back");
		AddActorLocation(FVector2D::UP * _DeltaTime * Speed);
	}
	else if (true == UEngineInput::GetInst().IsUp('W'))
	{
		SpriteRenderer->ChangeAnimation("Idle_Back");
	}

}

void APlayer::LevelChangeStart()
{
	Super::LevelChangeStart();
}

void APlayer::LevelChangeEnd()
{
	Super::LevelChangeEnd();
}