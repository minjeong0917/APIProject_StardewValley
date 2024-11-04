#include "PreCompile.h"
#include "Player.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EnginePlatform/EngineInput.h>
#include <EnginePlatform/EngineWinImage.h>

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

        // 앞
        SpriteRenderer->CreateAnimation("Run_Front", "Farmer_Right.png", { 0, 1, 17, 1, 15, 2, 18, 2 }, { 0.1f, 0.1f, 0.1f, 0.1f , 0.1f , 0.1f , 0.1f , 0.1f });
        SpriteRenderer->CreateAnimation("Idle_front", "Farmer_Right.png", 0, 0, 0.1f);

        // 뒤
        SpriteRenderer->CreateAnimation("Run_Back", "Farmer_Right.png", { 11, 12, 20, 12, 11, 13, 21, 13 }, { 0.1f, 0.1f, 0.1f, 0.1f , 0.1f , 0.1f , 0.1f , 0.1f });
        SpriteRenderer->CreateAnimation("Idle_Back", "Farmer_Right.png", 11, 11, 0.1f);

        // 오른쪽
        SpriteRenderer->CreateAnimation("Run_Right", "Farmer_Right.png", { 19, 16, 6, 73, 10, 6 }, { 0.15f, 0.1f, 0.1f, 0.15f , 0.1f, 0.1f });
        SpriteRenderer->CreateAnimation("Idle_Right", "Farmer_Right.png", 6, 6, 0.1f);

        // 왼쪽
        SpriteRenderer->CreateAnimation("Run_Left", "Farmer_Left.png", { 19, 16, 6, 73, 10, 6 }, { 0.15f, 0.1f, 0.1f, 0.15f , 0.1f, 0.1f });
        SpriteRenderer->CreateAnimation("Idle_Left", "Farmer_Left.png", 6, 6, 0.1f);

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
    UEngineDebug::CoreOutPutString("Pos : " + GetWorld()->GetCameraPivot().ToString());


    PlayerMove(_DeltaTime);
    CameraCheck(_DeltaTime);

}

void APlayer::PlayerMove(float _DeltaTime)
{
    if (true == UEngineInput::GetInst().IsDown('R'))
    {
        UEngineAPICore::GetCore()->OpenLevel("Title");
    }
    if (true == UEngineInput::GetInst().IsDown('T'))
    {
        UEngineAPICore::GetCore()->OpenLevel("Town");
    }
    if (true == UEngineInput::GetInst().IsDown('M'))
    {
        UEngineAPICore::GetCore()->OpenLevel("Tile");
    }

    if (true == UEngineInput::GetInst().IsDown(VK_F2))
    {
        Speed += 100;
    }

    if (true == UEngineInput::GetInst().IsDown(VK_F1))
    {
        UEngineDebug::SwitchIsDebug();
    }

    // 오른쪽 이동
    if (true == UEngineInput::GetInst().IsPress('D'))
    {
        SpriteRenderer->ChangeAnimation("Run_Right");
        AddActorLocation(FVector2D::RIGHT * _DeltaTime * Speed);
    }
    else if (true == UEngineInput::GetInst().IsUp('D'))
    {
        SpriteRenderer->ChangeAnimation("Idle_Right");
    }

    // 왼쪽 이동
    if (true == UEngineInput::GetInst().IsPress('A'))
    {
        SpriteRenderer->ChangeAnimation("Run_Left");
        AddActorLocation(FVector2D::LEFT * _DeltaTime * Speed);
    }
    else if (true == UEngineInput::GetInst().IsUp('A'))
    {
        SpriteRenderer->ChangeAnimation("Idle_Left");
    }

    // 아래쪽 이동
    if (true == UEngineInput::GetInst().IsPress('S'))
    {
        SpriteRenderer->ChangeAnimation("Run_Front");
        AddActorLocation(FVector2D::DOWN * _DeltaTime * Speed);
    }
    else if (true == UEngineInput::GetInst().IsUp('S'))
    {
        SpriteRenderer->ChangeAnimation("Idle_front");
    }

    // 위쪽 이동
    if (true == UEngineInput::GetInst().IsPress('W'))
    {
        SpriteRenderer->ChangeAnimation("Run_Back");
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

    GetWorld()->SetCameraToMainPawn(false);
    GetWorld()->SetCameraPos({ GetActorLocation() - Size.Half()});

    FVector2D CameraPos = GetWorld()->GetCameraPos();

    if (CameraPos.X <= 0.0f)
    {
        CameraPos.X = 0.0f;
    }

    if (CameraPos.X + Size.X  >= 3200.0f )
    {
        CameraPos.X = 3200.0f - Size.X;
    }

    if (CameraPos.Y <= 0.0f)
    {
        CameraPos.Y = 0.0f;
    }

    if (CameraPos.Y + Size.Y >= 2600.0f)
    {
        CameraPos.Y = 2600.0f - Size.Y;
    }

    GetWorld()->SetCameraPos(CameraPos);

}

