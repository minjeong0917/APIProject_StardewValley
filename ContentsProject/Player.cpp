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

        SpriteRenderer->CreateAnimation("Walk_Front", "Farmer_Right.png", { 1, 0, 2, 0 }, { 0.1f, 0.1f, 0.1f, 0.1f });
        SpriteRenderer->CreateAnimation("Idle_front", "Farmer_Right.png", 0, 0, 0.1f);
        SpriteRenderer->CreateAnimation("Walk_Back", "Farmer_Right.png", { 12, 11, 13, 11 }, { 0.1f, 0.1f, 0.1f, 0.1f });
        SpriteRenderer->CreateAnimation("Idle_Back", "Farmer_Right.png", 11, 11, 0.1f);

        SpriteRenderer->CreateAnimation("Walk_Right", "Farmer_Right.png", { 7, 8 }, { 0.1f, 0.1f });
        SpriteRenderer->CreateAnimation("Idle_Right", "Farmer_Right.png", 6, 6, 0.1f);
        SpriteRenderer->CreateAnimation("Walk_Left", "Farmer_Left.png", { 7, 8 }, { 0.1f, 0.1f });
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

    if (true == UEngineInput::GetInst().IsDown(VK_F1))
    {
        UEngineDebug::SwitchIsDebug();
    }

    // 오른쪽 이동
    if (true == UEngineInput::GetInst().IsPress('D'))
    {
        SpriteRenderer->ChangeAnimation("Walk_Right");
        AddActorLocation(FVector2D::RIGHT * _DeltaTime * Speed);
        IsXMove = true;
    }
    else if (true == UEngineInput::GetInst().IsUp('D'))
    {
        SpriteRenderer->ChangeAnimation("Idle_Right");
        IsXMove = false;
    }

    // 왼쪽 이동
    if (true == UEngineInput::GetInst().IsPress('A'))
    {
        SpriteRenderer->ChangeAnimation("Walk_Left");
        AddActorLocation(FVector2D::LEFT * _DeltaTime * Speed);
        IsXMove = true;
    }
    else if (true == UEngineInput::GetInst().IsUp('A'))
    {
        SpriteRenderer->ChangeAnimation("Idle_Left");
        IsXMove = false;
    }

    // 아래쪽 이동
    if (true == UEngineInput::GetInst().IsPress('S'))
    {
        SpriteRenderer->ChangeAnimation("Walk_Front");
        AddActorLocation(FVector2D::DOWN * _DeltaTime * Speed);
        IsYMove = true;
    }
    else if (true == UEngineInput::GetInst().IsUp('S'))
    {
        SpriteRenderer->ChangeAnimation("Idle_front");
        IsYMove = false;
    }

    // 위쪽 이동
    if (true == UEngineInput::GetInst().IsPress('W'))
    {
        SpriteRenderer->ChangeAnimation("Walk_Back");
        AddActorLocation(FVector2D::UP * _DeltaTime * Speed);
        IsYMove = true;
    }
    else if (true == UEngineInput::GetInst().IsUp('W'))
    {
        SpriteRenderer->ChangeAnimation("Idle_Back");
        IsYMove = false;
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

    float CameraXPos = CameraPos.X + Size.X;
    float CameraYPos = CameraPos.Y + Size.Y;

    FVector2D RightCameraPivot = GetWorld()->GetCameraPivot() + FVector2D::RIGHT * _DeltaTime * Speed;
    FVector2D LeftCameraPivot = GetWorld()->GetCameraPivot() + FVector2D::LEFT * _DeltaTime * Speed;
    FVector2D DownCameraPivot = GetWorld()->GetCameraPivot() + FVector2D::DOWN * _DeltaTime * Speed;
    FVector2D UpCameraPivot = GetWorld()->GetCameraPivot() + FVector2D::UP * _DeltaTime * Speed;


    // X축 제한
    if (true == IsXMove)
    {
        // 카메라 X위치가 0 보다 작다면 CamerPivot을 Player 속도에 맞춰 오른쪽으로 이동
        if (CameraPos.X < 0)
        {
            GetWorld()->SetCameraPivot(RightCameraPivot);
        }
        else if (PlayerXPosMin < 0)
        {
            GetWorld()->SetCameraPivot(LeftCameraPivot);
        }

        if (PlayerXPosMax >= 3200.0f && CameraXPos < 3200.0f)
        {
            GetWorld()->SetCameraPivot(RightCameraPivot);
        }
        else if (CameraXPos >= 3200.0f)
        {
            GetWorld()->SetCameraPivot(LeftCameraPivot);
        }
    }
    // Y축 제한
    if (true == IsYMove)
    {
        if (CameraPos.Y < 0)
        {
            GetWorld()->SetCameraPivot(DownCameraPivot);
        }
        else if (PlayerYPosMin < 0)
        {
            GetWorld()->SetCameraPivot(UpCameraPivot);
        }

        if (PlayerYPosMax >= 2600.0f && CameraYPos < 2600.0f)
        {
            GetWorld()->SetCameraPivot(DownCameraPivot);
        }
        else if (CameraYPos >= 2600.0f)
        {
            GetWorld()->SetCameraPivot(UpCameraPivot);
        }
    }
}