#include "PreCompile.h"
#include "Player.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>

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
		SpriteRenderer->SetComponentScale({ 166.4f, 332.8f });

		SpriteRenderer->CreateAnimation("Walk_Front", "Farmer_Right.png", { 1, 0, 2, 0 }, { 0.1f, 0.1f, 0.1f, 0.1f });
		SpriteRenderer->CreateAnimation("Idle_front", "Farmer_Right.png", 0, 0, 0.1f);
		SpriteRenderer->CreateAnimation("Walk_Right", "Farmer_Right.png", { 7, 8 }, { 0.1f, 0.1f });
		SpriteRenderer->CreateAnimation("Idle_Right", "Farmer_Right.png", 6,6, 0.1f);

		SpriteRenderer->ChangeAnimation("Idle_front");
	}


}

APlayer::~APlayer()
{
}


void APlayer::BeginPlay()
{
	Super::BeginPlay();

	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	GetWorld()->SetCameraPivot(Size.Half() * -1.0f);


}


void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == UEngineInput::GetInst().IsPress('D'))
	{
		SpriteRenderer->ChangeAnimation("Walk_Right");
		AddActorLocation(FVector2D::RIGHT * _DeltaTime * Speed);
	}
	else if (true == UEngineInput::GetInst().IsUp('D'))
	{
		SpriteRenderer->ChangeAnimation("Idle_Right");
	}

	if (true == UEngineInput::GetInst().IsPress('A'))
	{
		SpriteRenderer->ChangeAnimation("Walk_Right");
		AddActorLocation(FVector2D::LEFT * _DeltaTime * Speed);
	}

	if (true == UEngineInput::GetInst().IsPress('S'))
	{
		SpriteRenderer->ChangeAnimation("Walk_Front");
		AddActorLocation(FVector2D::DOWN * _DeltaTime * Speed);
	}
	else if (true == UEngineInput::GetInst().IsUp('S'))
	{
		SpriteRenderer->ChangeAnimation("Idle_front");
	}

	if (true == UEngineInput::GetInst().IsPress('W'))
	{
		SpriteRenderer->ChangeAnimation("Walk_Right");
		AddActorLocation(FVector2D::UP * _DeltaTime * Speed);
	}


}