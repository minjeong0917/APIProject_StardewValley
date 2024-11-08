#include "PreCompile.h"
#include "Player.h"

#include "TileMap.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EnginePlatform/EngineInput.h>
#include <EnginePlatform/EngineWinImage.h>

#include <EngineCore/EngineCoreDebug.h>

void APlayer::RunSoundPlay()
{

}

APlayer::APlayer()
{
    {
        SpriteRenderer = CreateDefaultSubObject<USpriteRenderer>();
        SpriteRenderer->SetSprite("Farmer_Right.png");
        SpriteRenderer->SetSprite("Farmer_Right.png");
        SpriteRenderer->SetSprite("Farmer_Left.png");
        SpriteRenderer->SetComponentScale({ 166.4f, 332.8f });

        PlayerAnimation();
        SpriteRenderer->ChangeAnimation("Idle_front");

    }
    DebugOn();


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
    //SpriteRenderer->SetPivotType(PivotType::Center);
    SpriteRenderer->SetPivot({ 0.0, 7.0f });
}


void APlayer::Tick(float _DeltaTime)
{
    Super::Tick(_DeltaTime);

    SpriteRenderer->SetOrder(GetActorLocation().Y);

    LevelChangeCheck();
    DebugCheck(_DeltaTime);
    PlayerMove(_DeltaTime);

    BackImgCollisionCheck(PlayerMoveDir() * _DeltaTime * Speed);

    if (nullptr != TileMap)
    {
        TileMapCollisionCheck(PlayerMoveDir() * _DeltaTime * Speed);
        TileDestroy();
    }

    PlayerAnimationPlay();
    CameraCheck();


}

void APlayer::LevelChangeCheck()
{
    if (true == UEngineInput::GetInst().IsDown('R'))
    {
        UEngineAPICore::GetCore()->OpenLevel("Title");
    }
    if (true == UEngineInput::GetInst().IsDown('T'))
    {
        UEngineAPICore::GetCore()->OpenLevel("Town");
    }

}

void APlayer::DebugCheck(float _DeltaTime)
{
    UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
    UEngineDebug::CoreOutPutString("PlayerPos : " + GetActorLocation().ToString());

    if (true == UEngineInput::GetInst().IsDown(VK_F1))
    {
        UEngineDebug::SwitchIsDebug();
    }

    if (true == UEngineInput::GetInst().IsDown(VK_F2))
    {
        UEngineDebug::SwitchIsDebug();
    }
}

FVector2D APlayer::PlayerMoveDir()
{

    // F2 : 플레이어 속도 증가
    if (true == UEngineInput::GetInst().IsDown(VK_ADD))
    {
        Speed += 100;
    }

    FVector2D Vector = FVector2D::ZERO;

    // 대각선 이동
    if (true == UEngineInput::GetInst().IsPress('D') && true == UEngineInput::GetInst().IsPress('W'))
    {
        SpriteRenderer->ChangeAnimation("Run_Right");
        IsPlayerMove = true;
        Vector += FVector2D::RIGHT;
        Vector += FVector2D::UP;

    }
    else if (true == UEngineInput::GetInst().IsPress('D') && true == UEngineInput::GetInst().IsPress('S'))
    {
        SpriteRenderer->ChangeAnimation("Run_Right");
        IsPlayerMove = true;
        Vector += FVector2D::RIGHT;
        Vector += FVector2D::DOWN;
    }
    else if (true == UEngineInput::GetInst().IsPress('A') && true == UEngineInput::GetInst().IsPress('W'))
    {
        SpriteRenderer->ChangeAnimation("Run_Left");
        IsPlayerMove = true;
        Vector += FVector2D::LEFT;
        Vector += FVector2D::UP;

    }
    else if (true == UEngineInput::GetInst().IsPress('A') && true == UEngineInput::GetInst().IsPress('S'))
    {
        SpriteRenderer->ChangeAnimation("Run_Left");
        IsPlayerMove = true;
        Vector += FVector2D::LEFT;
        Vector += FVector2D::DOWN;
    }
    else
    {
        // 상하좌우 이동
        if (true == UEngineInput::GetInst().IsPress('D'))
        {
            SpriteRenderer->ChangeAnimation("Run_Right");
            IsPlayerMove = true;
            Vector = FVector2D::RIGHT;

        }
        else if (true == UEngineInput::GetInst().IsPress('A'))
        {
            SpriteRenderer->ChangeAnimation("Run_Left");
            IsPlayerMove = true;
            Vector = FVector2D::LEFT;
        }
        else if (true == UEngineInput::GetInst().IsPress('S'))
        {
            SpriteRenderer->ChangeAnimation("Run_Front");
            IsPlayerMove = true;
            Vector = FVector2D::DOWN;

        }
        else if (true == UEngineInput::GetInst().IsPress('W'))
        {
            SpriteRenderer->ChangeAnimation("Run_Back");
            IsPlayerMove = true;
            Vector = FVector2D::UP;

        }

        // 정지
        if (true == UEngineInput::GetInst().IsUp('D'))
        {
            SpriteRenderer->ChangeAnimation("Idle_Right");
            PlayerDir = EPlayerDir::Right;
            IsPlayerMove = false;

        }
        else if (true == UEngineInput::GetInst().IsUp('A'))
        {
            SpriteRenderer->ChangeAnimation("Idle_Left");
            IsPlayerMove = false;
            PlayerDir = EPlayerDir::Left;

        }
        // 아래쪽 이동
        else if (true == UEngineInput::GetInst().IsUp('S'))
        {
            SpriteRenderer->ChangeAnimation("Idle_front");
            IsPlayerMove = false;
            PlayerDir = EPlayerDir::Down;

        }
        // 위쪽 이동
        else if (true == UEngineInput::GetInst().IsUp('W'))
        {
            SpriteRenderer->ChangeAnimation("Idle_Back");
            IsPlayerMove = false;
            PlayerDir = EPlayerDir::Up;
        }
    }

    Vector.Normalize();

    return Vector;
}


void APlayer::PlayerMove(float _DeltaTime)
{
    if (true == ColorCheck && true == TileCheck)
    {
        AddActorLocation(PlayerMoveDir() * _DeltaTime * Speed);
    }
}


void APlayer::BackImgCollisionCheck(FVector2D _Vector)
{

    FVector2D NextPos = GetActorLocation() + _Vector;
    if (nullptr != ColImage)
    {
        UColor Color = ColImage->GetColor(NextPos, UColor::BLACK);
        if (Color == UColor::WHITE)
        {
            ColorCheck = true;
        }
        if (Color == (255,0,0))
        {
            UEngineAPICore::GetCore()->OpenLevel("Town");

        }
    }
    }



void APlayer::TileDestroy()
{
    FVector2D PlayerVector = GetActorLocation();
    switch (PlayerDir)
    {
    case EPlayerDir::Left:
        PlayerVector += {-50, 0};
        break;
    case EPlayerDir::Right:
        PlayerVector += {50, 0};

        break;
    case EPlayerDir::Up:
        PlayerVector += {0, -50};
        break;
    case EPlayerDir::Down:
        PlayerVector += {0, 50};
        break;
    default:
        break;
    }

    if (true == UEngineInput::GetInst().IsPress(VK_RBUTTON))
    {
        Tile* Tile = TileMap->GetTileRef(PlayerVector);

        if (nullptr != Tile->SpriteRenderer)
        {
            Tile->SpriteRenderer->Destroy();
            Tile->SpriteRenderer = nullptr;
        }
    }
}


void APlayer::TileMapCollisionCheck(FVector2D _Vector)
{
    TileCheck = false;

    FVector2D TileMapSize = TileMap->GetTileSize();
    FVector2D NextPos = GetActorLocation() + _Vector;

    //NextPos.X /= TileMapSize.X; -> 타일의 위치 알 수 있음!
    Tile* TilePtr = TileMap->GetTileRef(NextPos);

    if (TilePtr->IsMove)
    {
        TileCheck = true;
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

void APlayer::SetColImage(std::string_view _ColImageName)
{
    ColImage = UImageManager::GetInst().FindImage(_ColImageName);
}

void APlayer::SetBackImage(std::string_view _BackImageName)
{
    BackImage = UImageManager::GetInst().FindImage(_BackImageName);
}

void APlayer::CameraCheck()
{
    FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

    GetWorld()->SetCameraToMainPawn(false);
    GetWorld()->SetCameraPos({ GetActorLocation() - Size.Half() });

    float ImageXSize = BackImage->GetImageScale().X;
    float ImageYSize = BackImage->GetImageScale().Y;

    FVector2D CameraPos = GetWorld()->GetCameraPos();

    if (CameraPos.X <= 0.0f)
    {
        CameraPos.X = 0.0f;
    }

    if (CameraPos.X + Size.X >= ImageXSize)
    {
        CameraPos.X = ImageXSize - Size.X;
    }

    if (CameraPos.Y <= 0.0f)
    {
        CameraPos.Y = 0.0f;
    }

    if (CameraPos.Y + Size.Y >= ImageYSize)
    {
        CameraPos.Y = ImageYSize - Size.Y;
    }

    GetWorld()->SetCameraPos(CameraPos);

}

void APlayer::PlayerAnimationPlay()
{

    if (true == UEngineInput::GetInst().IsPress(VK_LBUTTON))
    {
        switch (PlayerDir)
        {
        case EPlayerDir::Left:
            SpriteRenderer->ChangeAnimation("Dig_Left");
            break;
        case EPlayerDir::Right:
            SpriteRenderer->ChangeAnimation("Dig_Right");
            break;
        case EPlayerDir::Up:
            break;
        case EPlayerDir::Down:
            SpriteRenderer->ChangeAnimation("Dig_Front");
            break;
        default:
            break;
        }
    }
}

void APlayer::PlayerAnimation()
{
    // 앞
    SpriteRenderer->CreateAnimation("Run_Front", "Farmer_Right.png", { 0, 1, 17, 1, 15, 2, 18, 2 }, { 0.1f, 0.1f, 0.1f, 0.1f , 0.1f , 0.1f , 0.1f , 0.1f });
    SpriteRenderer->CreateAnimation("Idle_front", "Farmer_Right.png", { 0, 15,0 }, { 1.0f,0.1f,1.0f });

    // 뒤
    SpriteRenderer->CreateAnimation("Run_Back", "Farmer_Right.png", { 11, 12, 20, 12, 11, 13, 21, 13 }, { 0.1f, 0.1f, 0.1f, 0.1f , 0.1f , 0.1f , 0.1f , 0.1f });
    SpriteRenderer->CreateAnimation("Idle_Back", "Farmer_Right.png", 11, 11, 0.1f);

    // 오른쪽
    SpriteRenderer->CreateAnimation("Run_Right", "Farmer_Right.png", { 19, 16, 6, 73, 10, 6 }, { 0.15f, 0.1f, 0.1f, 0.15f , 0.1f, 0.1f });
    SpriteRenderer->CreateAnimation("Idle_Right", "Farmer_Right.png", 6, 6, 0.1f);

    // 왼쪽
    SpriteRenderer->CreateAnimation("Run_Left", "Farmer_Left.png", { 19, 16, 6, 73, 10, 6 }, { 0.15f, 0.1f, 0.1f, 0.15f , 0.1f, 0.1f });
    SpriteRenderer->CreateAnimation("Idle_Left", "Farmer_Left.png", 6, 6, 0.1f);


    SpriteRenderer->CreateAnimation("Dig_Right", "Farmer_Right.png", { 80, 93, 80, 81, 82, 83,6 }, { 0.05f, 0.05f, 0.05f, 0.05f , 0.2f, 0.2f, 0.05f }, false);
    SpriteRenderer->CreateAnimation("Dig_Left", "Farmer_Left.png", { 80, 93, 80, 81, 82, 83,6 }, { 0.05f, 0.05f, 0.05f, 0.05f , 0.2f, 0.2f, 0.05f }, false);
    SpriteRenderer->CreateAnimation("Dig_Front", "Farmer_Right.png", { 22,23,24,25,0 }, { 0.1f , 0.1f, 0.1f, 0.15f, 0.05f }, false);


}