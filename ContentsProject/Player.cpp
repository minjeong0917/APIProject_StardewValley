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
	SetActorLocation({ 2500, 1000 });

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


}

APlayer::~APlayer()
{
}


void APlayer::BeginPlay()
{
	Super::BeginPlay();

	// ī�޶� �ǹ� ��ġ ����
	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
	GetWorld()->SetCameraPivot(Size.Half() * -1.0f);


}


void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	CameraCheck(_DeltaTime);

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

	// ������ �̵�
	if (true == UEngineInput::GetInst().IsPress('D'))
	{
		SpriteRenderer->ChangeAnimation("Walk_Right");
		AddActorLocation(FVector2D::RIGHT * _DeltaTime * Speed);
	}
	else if (true == UEngineInput::GetInst().IsUp('D'))
	{
		SpriteRenderer->ChangeAnimation("Idle_Right");
	}

	// ���� �̵�
	if (true == UEngineInput::GetInst().IsPress('A'))
	{
		SpriteRenderer->ChangeAnimation("Walk_Left");
		AddActorLocation(FVector2D::LEFT * _DeltaTime * Speed);
	}
	else if (true == UEngineInput::GetInst().IsUp('A'))
	{
		SpriteRenderer->ChangeAnimation("Idle_Left");
	}

	// �Ʒ��� �̵�
	if (true == UEngineInput::GetInst().IsPress('S'))
	{
		SpriteRenderer->ChangeAnimation("Walk_Front");
		AddActorLocation(FVector2D::DOWN * _DeltaTime * Speed);
	}
	else if (true == UEngineInput::GetInst().IsUp('S'))
	{
		SpriteRenderer->ChangeAnimation("Idle_front");
	}

	// ���� �̵�
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

void APlayer::CameraCheck(float _DeltaTime)
{
	FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
    FVector2D CameraPos = GetWorld()->GetCameraPos();
	float PlayerXPosMin = GetActorLocation().X - Size.Half().X;
	float PlayerYPosMin = GetActorLocation().Y - Size.Half().Y;
	float PlayerXPosMax = GetActorLocation().X + Size.Half().X;
	float PlayerYPosMax = GetActorLocation().Y + Size.Half().Y;


	// ī�޶� X��ġ�� 0 ���� �۴ٸ� CamerPivot�� Player �ӵ��� ���� ���������� �̵�
    if (CameraPos.X < 0)
    {
		FVector2D CurCameraPivot = GetWorld()->GetCameraPivot() + FVector2D::RIGHT * _DeltaTime * Speed;
		GetWorld()->SetCameraPivot(CurCameraPivot);
	}
	// �÷��̾� X��ġ�� ȭ�� ���ݺ��� ���ʿ� �ִٸ� CamerPivot�� Player �ӵ��� ���� �������� �̵�
	else if (PlayerXPosMin < 0)
	{
		FVector2D CurCameraPivot = GetWorld()->GetCameraPivot() + FVector2D::LEFT * _DeltaTime * Speed;
		GetWorld()->SetCameraPivot(CurCameraPivot);
	}


	if (CameraPos.Y < 0)
	{
		FVector2D CurCameraPivot = GetWorld()->GetCameraPivot() + FVector2D::DOWN * _DeltaTime * Speed;
		GetWorld()->SetCameraPivot(CurCameraPivot);
	}
	else if (PlayerYPosMin < 0)
	{
		FVector2D CurCameraPivot = GetWorld()->GetCameraPivot() + FVector2D::UP * _DeltaTime * Speed;
		GetWorld()->SetCameraPivot(CurCameraPivot);
	}

	if (CameraPos.X + Size.X > 3200)
	{
		FVector2D CurCameraPivot = GetWorld()->GetCameraPivot() + FVector2D::LEFT * _DeltaTime * Speed;
		GetWorld()->SetCameraPivot(CurCameraPivot);
	}
	else if (PlayerXPosMax > 3200)
	{
		FVector2D CurCameraPivot = GetWorld()->GetCameraPivot() + FVector2D::RIGHT * _DeltaTime * Speed;
		GetWorld()->SetCameraPivot(CurCameraPivot);
	}

	if (CameraPos.Y + Size.Y > 2600)
	{
		FVector2D CurCameraPivot = GetWorld()->GetCameraPivot() + FVector2D::UP * _DeltaTime * Speed;
		GetWorld()->SetCameraPivot(CurCameraPivot);
	}
	else if (PlayerYPosMax > 2600)
	{
		FVector2D CurCameraPivot = GetWorld()->GetCameraPivot() + FVector2D::DOWN * _DeltaTime * Speed;
		GetWorld()->SetCameraPivot(CurCameraPivot);
	}

}