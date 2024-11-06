#include "PreCompile.h"
#include "Player.h"
#include "ContentsEnum.h"
#include "TileMap.h"

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
    //SpriteRenderer->SetPivotType(PivotType::Bot);
}


void APlayer::Tick(float _DeltaTime)
{
    Super::Tick(_DeltaTime);

    LevelChangeCheck();
    DebugCheck(_DeltaTime);
    PlayerMove(_DeltaTime);
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
    if (true == UEngineInput::GetInst().IsDown('M'))
    {
        UEngineAPICore::GetCore()->OpenLevel("Tile");
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
}

void APlayer::PlayerMove(float _DeltaTime)
{

    // F2 : 플레이어 속도 증가
    if (true == UEngineInput::GetInst().IsDown(VK_F2))
    {
        Speed += 100;
    }



    FVector2D Vector = FVector2D::ZERO;



    // 오른쪽 이동
    if (true == UEngineInput::GetInst().IsPress('D'))
    {
        SpriteRenderer->ChangeAnimation("Run_Right");
        Vector += FVector2D::RIGHT;

    }
    else if (true == UEngineInput::GetInst().IsUp('D'))
    {
        SpriteRenderer->ChangeAnimation("Idle_Right");
    }

    // 왼쪽 이동
    if (true == UEngineInput::GetInst().IsPress('A'))
    {
        SpriteRenderer->ChangeAnimation("Run_Left");
        Vector += FVector2D::LEFT;
    }
    else if (true == UEngineInput::GetInst().IsUp('A'))
    {
        SpriteRenderer->ChangeAnimation("Idle_Left");
    }

    // 아래쪽 이동
    if (true == UEngineInput::GetInst().IsPress('S'))
    {
        SpriteRenderer->ChangeAnimation("Run_Front");
        Vector += FVector2D::DOWN;

    }
    else if (true == UEngineInput::GetInst().IsUp('S'))
    {
        SpriteRenderer->ChangeAnimation("Idle_front");
    }

    // 위쪽 이동
    if (true == UEngineInput::GetInst().IsPress('W'))
    {
        SpriteRenderer->ChangeAnimation("Run_Back");
        Vector += FVector2D::UP;

    }
    else if (true == UEngineInput::GetInst().IsUp('W'))
    {
        SpriteRenderer->ChangeAnimation("Idle_Back");
    }

    if (nullptr != ColImage)
    {
        ColorCheck = false;

        // 픽셀충돌에서 제일 중요한건 애초에 박히지 않는것이다.
        FVector2D NextPos = GetActorLocation() + Vector * _DeltaTime * Speed;

        UColor Color = ColImage->GetColor(NextPos, UColor::BLACK);
        if (Color == UColor::WHITE)
        {
            ColorCheck = true;
        }

        FVector2D TileMapSize = TileMap->GetTileSize();

        TileCheck = false;

        Tile* TilePtr = TileMap->GetTileRef(NextPos);

        if (TilePtr->IsMove)
        {
            TileCheck = true;
        }

        //NextPos.X /= TileMapSize.X;



        if (true == ColorCheck && true == TileCheck)
        {
            AddActorLocation(Vector * _DeltaTime * Speed);
        }
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

    SpriteRenderer->SetOrder(GetActorLocation().Y);

    GetWorld()->SetCameraToMainPawn(false);
    GetWorld()->SetCameraPos({ GetActorLocation() - Size.Half()});

    float ImageXSize = BackImage->GetImageScale().X;
    float ImageYSize = BackImage->GetImageScale().Y;
    
    FVector2D CameraPos = GetWorld()->GetCameraPos();

    if (CameraPos.X <= 0.0f)
    {
        CameraPos.X = 0.0f;
    }

    if (CameraPos.X + Size.X  >= ImageXSize)
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

