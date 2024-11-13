#include "PreCompile.h"
#include "Player.h"

#include "TileMap.h"

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EnginePlatform/EngineInput.h>
#include <EnginePlatform/EngineWinImage.h>

#include <EngineCore/EngineCoreDebug.h>

#include "Clock.h"
#include "Gold.h"
#include "Text.h"
#include "InventoryBar.h"




#include"FarmGameMode.h"

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
        SpriteRenderer->SetComponentScale({ 220, 440 });
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
    FarmGameMode = GetWorld()->GetGameMode<AFarmGameMode>();

    if (nullptr != FarmGameMode)
    {
        FarmTileMap = FarmGameMode->GetFarmTilMap();

    }

    // 카메라 피벗 위치 설정
    FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
    GetWorld()->SetCameraPivot(Size.Half() * -1.0f);

    SpriteRenderer->SetPivot({ 0.0, 7.0f });
    UIImageRender();
}


void APlayer::Tick(float _DeltaTime)
{
    Super::Tick(_DeltaTime);

    SpriteRenderer->SetOrder(GetActorLocation().Y);

    LevelChangeCheck();
    DebugCheck(_DeltaTime);
    PlayerMove(_DeltaTime);

    BackImgCollisionCheck(PlayerMoveDir() * _DeltaTime * Speed);

    PlayerAnimationPlay();
    if (nullptr != FarmTileMap)
    {
        TileMapCollisionCheck(PlayerMoveDir() * _DeltaTime * Speed);
        TileDestroy();

        std::string Name = TileLocationName();
        TileAlphaCheck(Name);
    }

    CameraCheck();

    FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
    Cursor->SetActorLocation({ MousePos.X + 10, MousePos.Y + 15 });

    int Min = MinTime->SetMinute(_DeltaTime);
    HourTime->SetHour(Min);




}
std::string APlayer::TileLocationName()
{
    FVector2D PlayerLocation = GetActorLocation();
    std::string TileName;

    int searchRangeY = 150;
    for (int offsetY = 0; offsetY <= searchRangeY; ++offsetY)
    {
        FVector2D TileLocation = { PlayerLocation.X, PlayerLocation.Y + 30+ offsetY };
        TileName = FarmGameMode->GetTileSpriteName(TileLocation);

        if (TileName == "TREETILE")
        {
            TreeTile = FarmTileMap->GetTileRef(TileLocation);
            return TileName;
        }
    }

    return "NONE";
}

void APlayer::TileAlphaCheck(std::string _TileName)
{
    if (nullptr != TreeTile)
    {
        if (_TileName == "TREETILE")
        {
            if (PreviousTreeTile != TreeTile)
            {
                if (PreviousTreeTile != nullptr)
                {
                    PreviousTreeTile->TileSpriteAlpha(1.0f);
                }

                TreeTile->TileSpriteAlpha(0.2f);

                PreviousTreeTile = TreeTile;
            }
        }
        else
        {
            if (PreviousTreeTile != nullptr)
            {
                PreviousTreeTile->TileSpriteAlpha(1.0f);
                PreviousTreeTile = nullptr;
            }
        }
    }
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
    FVector2D Vector = FVector2D::ZERO;
    AFarmGameMode* Farm = GetWorld()->GetGameMode<AFarmGameMode>();

    // F2 : 플레이어 속도 증가
    if (true == UEngineInput::GetInst().IsDown(VK_ADD))
    {
        Speed += 100;
    }

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
        else if (true == UEngineInput::GetInst().IsUp('S'))
        {

            SpriteRenderer->ChangeAnimation("Idle_front");
            IsPlayerMove = false;
            PlayerDir = EPlayerDir::Down;

        }
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
    ColorCheck = false;
    FVector2D NextPos = GetActorLocation() + _Vector;
    if (nullptr != ColImage)
    {
        UColor Color = ColImage->GetColor(NextPos, UColor::BLACK);
        if (Color == UColor::WHITE)
        {
            ColorCheck = true;
        }
        else if (Color.R == 255 && Color.G == 0 && Color.B == 0)
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
        Tile* Tile = FarmTileMap->GetTileRef(PlayerVector);

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

    FVector2D TileMapSize = FarmTileMap->GetTileSize();
    FVector2D NextPos = GetActorLocation() + _Vector;

    //NextPos.X /= TileMapSize.X; -> 타일의 위치 알 수 있음!
    Tile* TilePtr = FarmTileMap->GetTileRef(NextPos);

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
    AFarmGameMode* Farm = GetWorld()->GetGameMode<AFarmGameMode>();

    if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON))
    {
        switch (PlayerDir)
        {
        case EPlayerDir::Left:
            SpriteRenderer->ChangeAnimation("Dig_Left", true);
            break;
        case EPlayerDir::Right:
            SpriteRenderer->ChangeAnimation("Dig_Right", true);
            break;
        case EPlayerDir::Up:
            SpriteRenderer->ChangeAnimation("Dig_Back", true);
            break;
        case EPlayerDir::Down:
            SpriteRenderer->ChangeAnimation("Dig_Front", true);
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
    SpriteRenderer->CreateAnimation("Idle_front_once", "Farmer_Right.png", { 0, 15,0 }, { 1.0f,0.1f,1.0f },false);

    // 뒤
    SpriteRenderer->CreateAnimation("Run_Back", "Farmer_Right.png", { 11, 12, 20, 12, 11, 13, 21, 13 }, { 0.1f, 0.1f, 0.1f, 0.1f , 0.1f , 0.1f , 0.1f , 0.1f });
    SpriteRenderer->CreateAnimation("Idle_Back", "Farmer_Right.png", 11, 11, 0.1f);

    // 오른쪽
    SpriteRenderer->CreateAnimation("Run_Right", "Farmer_Right.png", { 19, 16, 6, 73, 10, 6 }, { 0.15f, 0.1f, 0.1f, 0.15f , 0.1f, 0.1f });
    SpriteRenderer->CreateAnimation("Idle_Right", "Farmer_Right.png", 6, 6, 0.1f);

    // 왼쪽
    SpriteRenderer->CreateAnimation("Run_Left", "Farmer_Left.png", { 19, 16, 6, 73, 10, 6 }, { 0.15f, 0.1f, 0.1f, 0.15f , 0.1f, 0.1f });
    SpriteRenderer->CreateAnimation("Idle_Left", "Farmer_Left.png", 6, 6, 0.1f);


    SpriteRenderer->CreateAnimation("Dig_Right", "Farmer_Right.png", { 80, 93, 80, 81, 82, 83, 6 }, { 0.05f, 0.05f, 0.05f, 0.05f , 0.2f, 0.05f, 0.05f }, false);
    SpriteRenderer->CreateAnimation("Dig_Left", "Farmer_Left.png", { 80, 93, 80, 81, 82, 83,6 }, { 0.05f, 0.05f, 0.05f, 0.05f , 0.2f, 0.05f, 0.05f }, false);
    SpriteRenderer->CreateAnimation("Dig_Front", "Farmer_Right.png", { 47,48,90,91,0 }, { 0.05f , 0.05f, 0.05f , 0.25f, 0.05f }, false);
    SpriteRenderer->CreateAnimation("Dig_Back", "Farmer_Right.png", { 77,76,43,11 }, { 0.1f , 0.1f,  0.2f, 0.05f }, false);


    SpriteRenderer->CreateAnimation("Item_font", "Farmer_Right_2.png", { 27,15,27,28,2,28 }, { 0.1f , 0.1f, 0.1f, 0.1f, 0.1f, 0.1f });
    SpriteRenderer->CreateAnimation("Item_Idle_front", "Farmer_Right_2.png", { 0,0 },  0.1f, true);



}

void APlayer::UIImageRender()
{

    FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

    // Clock
    AClock* Clock = GetWorld()->SpawnActor<AClock>();
    Clock->SetActorLocation({ Size.iX() - 154, 128 });

    // Gold
    AGold* Gold = GetWorld()->SpawnActor<AGold>();

    Gold->SetActorLocation({ Size.iX() - 54 , 218 });
    Gold->SetTextSpriteName("Gold3.png");
    Gold->SetOrder(ERenderOrder::UIFont);
    Gold->SetTextScale({ 22, 33 });
    Gold->SetValue(PlayerGold);

    // Text
    AText* Text = GetWorld()->SpawnActor<AText>();
    Text->SetSprite("apm.png", 0, 1.0f);
    Text->SetActorLocation({ Size.iX() - 130, 138 });

    // Cursor
    Cursor = GetWorld()->SpawnActor<ACursor>();

    // Time
    MinTime = GetWorld()->SpawnActor<ATime>();
    MinTime->SetActorLocation({ Size.iX() - 98 , 138 });
    MinTime->SetTextSpriteName("Time.png");

    HourTime = GetWorld()->SpawnActor<ATime>();
    HourTime->SetActorLocation({ Size.iX() - 145 , 138 });
    HourTime->SetTextSpriteName("Time.png");

    // InventoryBar
    AInventoryBar* InventoryBar = GetWorld()->SpawnActor<AInventoryBar>();
    InventoryBar->SetActorLocation({ Size.Half().iX(), Size.iY() - 80 });
}
