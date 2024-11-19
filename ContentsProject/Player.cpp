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
#include "Item.h"

#include "FarmGameMode.h"



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
    PlayerUI = GetWorld()->SpawnActor<APlayerUI>();

    BGMPlayer = UEngineSound::Play("Spring.wav");
    FarmGameMode = GetWorld()->GetGameMode<AFarmGameMode>();

    if (nullptr != FarmGameMode)
    {
        FarmTileMap = FarmGameMode->GetFarmTilMap();

    }

    // 카메라 피벗 위치 설정
    FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
    GetWorld()->SetCameraPivot(Size.Half() * -1.0f);

    SpriteRenderer->SetPivot({ 0.0, 7.0f });
}


void APlayer::Tick(float _DeltaTime)
{


    Super::Tick(_DeltaTime);

    SpriteRenderer->SetOrder(GetActorLocation().Y);

    LevelChangeCheck();
    DebugCheck(_DeltaTime);


    BackImgCollisionCheck(PlayerMoveDir() * _DeltaTime * Speed);


    if (nullptr != FarmTileMap)
    {
        TileMapCollisionCheck(PlayerMoveDir() * _DeltaTime * Speed);

        std::string Name = TileLocationName();
        TileAlphaCheck(Name);
    }

    CameraCheck();

    PlayerAnimationTimer(_DeltaTime, AnimationDuration);
    if (IsAnimationPlay == false)
    {
        PlayerAnimationPlay();
        PlayerMove(_DeltaTime);

    }



}
std::string APlayer::TileLocationName()
{
    FVector2D PlayerLocation = GetActorLocation();
    std::string TileName;

    int searchRangeY = 150;
    for (int offsetY = 0; offsetY <= searchRangeY; ++offsetY)
    {
        FVector2D TileLocation = { PlayerLocation.X, PlayerLocation.Y + 30+ offsetY };
        TileName = FarmGameMode->GetFarmTileSpriteName(TileLocation);

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
    if (nullptr != TreeTile && TreeTile->SpriteRenderer != nullptr)
    {
        if (_TileName == "TREETILE")
        {
            if (PreviousTreeTile != TreeTile)
            {
                // 이전 TreeTile이 유효한지 확인
                if (PreviousTreeTile != nullptr && PreviousTreeTile->SpriteRenderer != nullptr)
                {
                    PreviousTreeTile->TileSpriteAlpha(1.0f);
                }

                TreeTile->TileSpriteAlpha(0.3f);
                PreviousTreeTile = TreeTile;
            }
        }
        else
        {
            // 이전 TreeTile이 유효한지 확인
            if (PreviousTreeTile != nullptr && PreviousTreeTile->SpriteRenderer != nullptr)
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
    FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
    FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
    FVector2D PlayerLocation = GetActorLocation();

    float MousePosX = MousePos.X + Size.Half().X;
    float MousePosY = MousePos.Y + Size.Half().Y;
    UEngineDebug::CoreOutPutString("FPS : " + std::to_string(1.0f / _DeltaTime));
    UEngineDebug::CoreOutPutString("PlayerPos : " + GetActorLocation().ToString());


    if (true == UEngineInput::GetInst().IsDown(VK_F1))
    {
        UEngineDebug::SwitchIsDebug();
    }

    if (true == UEngineInput::GetInst().IsDown(VK_F2))
    {
        // static썼다. 
        UEngineAPICore::GetCore()->ResetLevel<AFarmGameMode, APlayer>("Play");
        UEngineAPICore::GetCore()->OpenLevel("Play");
    }
    if (true == UEngineInput::GetInst().IsDown(VK_F3))
    {
        BGMPlayer.OnOffSwtich();
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
        IsPlayerMove = true;
        Vector += FVector2D::RIGHT;
        Vector += FVector2D::UP;

    }
    else if (true == UEngineInput::GetInst().IsPress('D') && true == UEngineInput::GetInst().IsPress('S'))
    {
        IsPlayerMove = true;
        Vector += FVector2D::RIGHT;
        Vector += FVector2D::DOWN;
    }
    else if (true == UEngineInput::GetInst().IsPress('A') && true == UEngineInput::GetInst().IsPress('W'))
    {
        IsPlayerMove = true;
        Vector += FVector2D::LEFT;
        Vector += FVector2D::UP;

    }
    else if (true == UEngineInput::GetInst().IsPress('A') && true == UEngineInput::GetInst().IsPress('S'))
    {
        IsPlayerMove = true;
        Vector += FVector2D::LEFT;
        Vector += FVector2D::DOWN;
    }
    else
    {
        // 상하좌우 이동
        if (true == UEngineInput::GetInst().IsPress('D'))
        {

            IsPlayerMove = true;
            Vector = FVector2D::RIGHT;

        }
        else if (true == UEngineInput::GetInst().IsPress('A'))
        {
            IsPlayerMove = true;
            Vector = FVector2D::LEFT;
        }
        else if (true == UEngineInput::GetInst().IsPress('S'))
        {
            IsPlayerMove = true;
            Vector = FVector2D::DOWN;

        }
        else if (true == UEngineInput::GetInst().IsPress('W'))
        {
            IsPlayerMove = true;
            Vector = FVector2D::UP;

        }

        // 정지
        if (true == UEngineInput::GetInst().IsUp('D'))
        {
            
            PlayerDir = EPlayerDir::Right;
            IsPlayerMove = false;

        }
        else if (true == UEngineInput::GetInst().IsUp('A'))
        {
            IsPlayerMove = false;
            PlayerDir = EPlayerDir::Left;

        }
        else if (true == UEngineInput::GetInst().IsUp('S'))
        {

            IsPlayerMove = false;
            PlayerDir = EPlayerDir::Down;

        }
        else if (true == UEngineInput::GetInst().IsUp('W'))
        {
            IsPlayerMove = false;
            PlayerDir = EPlayerDir::Up;
        }
    }

    Vector.Normalize();

    return Vector;
}

void APlayer::AddItem(AItem* _Item)
{
    PlayerUI->AddItem(_Item);
}


void APlayer::PlayerMove(float _DeltaTime)
{
    if (true == ColorCheck && true == TileCheck && false == IsOpenIven)
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


    FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
    FVector2D CameraPos = GetWorld()->GetCameraPos();
    float MousePosX = MousePos.X + CameraPos.X;
    float MousePosY = MousePos.Y + CameraPos.Y;

    FVector2D Direction = { MousePosX - GetActorLocation().X, MousePosY - GetActorLocation().Y};
    float DirectionAbsX = std::abs(Direction.X);
    float DirectionAbsY = std::abs(Direction.Y);


    IsMouseInPlayerPos = false;

    if (DirectionAbsX <= 70 && DirectionAbsY <= 70 && DirectionAbsX >= 0 && DirectionAbsY >= 0)
    {
        IsMouseInPlayerPos = true;
    }


    if (false == IsPlayerMove && false == IsAnimationPlay)
    {
        if (PlayerUI->TypeCheck)
        {
            switch (PlayerDir)
            {
            case EPlayerDir::Left:
                SpriteRenderer->ChangeAnimation("Item_Idle_Left", true);

            break;
            case EPlayerDir::Right:

                SpriteRenderer->ChangeAnimation("Item_Idle_Right", true);


                break;
            case EPlayerDir::Up:
                    SpriteRenderer->ChangeAnimation("Item_Idle_Back", true);

                break;
            case EPlayerDir::Down:

                    SpriteRenderer->ChangeAnimation("Item_Idle_front", true);

                break;
            default:
                break;
            }
        }
         
        else 
        {
            switch (PlayerDir)
            {
            case EPlayerDir::Left:


                SpriteRenderer->ChangeAnimation("Idle_Left", true);

                break;
            case EPlayerDir::Right:


                SpriteRenderer->ChangeAnimation("Idle_Right", true);

                break;
            case EPlayerDir::Up:

                SpriteRenderer->ChangeAnimation("Idle_Back");

                break;
            case EPlayerDir::Down:


                SpriteRenderer->ChangeAnimation("Idle_front");
                break;
            default:
                break;
            }
        }

    }

    if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON) && false == IsPlayerMove && CurSlotCheck() == "Hoe")
    {
        if (IsMouseInPlayerPos)
        {
            if (DirectionAbsX > DirectionAbsY) {
                if (Direction.X > 0) {
                    PlayerDir = EPlayerDir::Right;
                }
                else {
                    PlayerDir = EPlayerDir::Left;
                }
            }
            else {
                if (Direction.Y > 0) {
                    PlayerDir = EPlayerDir::Down;
                }
                else {
                    PlayerDir = EPlayerDir::Up;
                }
            }

        }
        switch (PlayerDir)
        {
        case EPlayerDir::Left:
            SpriteRenderer->ChangeAnimation("Dig_Left", true);
            IsAnimationPlay = true;
            SetAnimationDuration(0.5f);
            break;
        case EPlayerDir::Right:
            SpriteRenderer->ChangeAnimation("Dig_Right", true);
            IsAnimationPlay = true;
            SetAnimationDuration(0.5f);
            break;
        case EPlayerDir::Up:
            SpriteRenderer->ChangeAnimation("Dig_Back", true);
            IsAnimationPlay = true;
            SetAnimationDuration(0.5f);
            break;
        case EPlayerDir::Down:
            SpriteRenderer->ChangeAnimation("Dig_Front", true);
            IsAnimationPlay = true;
            SetAnimationDuration(0.5f);


            break;
        default:
            break;
        }
    }


    if (PlayerUI->TypeCheck)
    {
        if (true == UEngineInput::GetInst().IsPress('D') && true == UEngineInput::GetInst().IsPress('W'))
        {
            SpriteRenderer->ChangeAnimation("Item_Run_Right");
        }
        else if (true == UEngineInput::GetInst().IsPress('D') && true == UEngineInput::GetInst().IsPress('S'))
        {
            SpriteRenderer->ChangeAnimation("Item_Run_Right");
        }
        else if (true == UEngineInput::GetInst().IsPress('A') && true == UEngineInput::GetInst().IsPress('W'))
        {
            SpriteRenderer->ChangeAnimation("Item_Run_Left");
        }
        else if (true == UEngineInput::GetInst().IsPress('A') && true == UEngineInput::GetInst().IsPress('S'))
        {
            SpriteRenderer->ChangeAnimation("Item_Run_Left");
        }
        else
        {
            // 상하좌우 이동
            if (true == UEngineInput::GetInst().IsPress('D'))
            {

                SpriteRenderer->ChangeAnimation("Item_Run_Right");


            }
            else if (true == UEngineInput::GetInst().IsPress('A'))
            {
                SpriteRenderer->ChangeAnimation("Item_Run_Left");

            }
            else if (true == UEngineInput::GetInst().IsPress('S'))
            {
                    SpriteRenderer->ChangeAnimation("Item_Run_front");


            }
            else if (true == UEngineInput::GetInst().IsPress('W'))
            {
                SpriteRenderer->ChangeAnimation("Item_Run_Back");


            }

        }
    }
    // 아무것도 안들고 뛰기
    else
    {
        if (true == UEngineInput::GetInst().IsPress('D') && true == UEngineInput::GetInst().IsPress('W'))
        {
            SpriteRenderer->ChangeAnimation("Run_Right");


        }
        else if (true == UEngineInput::GetInst().IsPress('D') && true == UEngineInput::GetInst().IsPress('S'))
        {
            SpriteRenderer->ChangeAnimation("Run_Right");

        }
        else if (true == UEngineInput::GetInst().IsPress('A') && true == UEngineInput::GetInst().IsPress('W'))
        {
            SpriteRenderer->ChangeAnimation("Run_Left");


        }
        else if (true == UEngineInput::GetInst().IsPress('A') && true == UEngineInput::GetInst().IsPress('S'))
        {
            SpriteRenderer->ChangeAnimation("Run_Left");

        }
        else
        {
            // 상하좌우 이동
            if (true == UEngineInput::GetInst().IsPress('D'))
            {

                SpriteRenderer->ChangeAnimation("Run_Right");


            }
            else if (true == UEngineInput::GetInst().IsPress('A'))
            {
                SpriteRenderer->ChangeAnimation("Run_Left");

            }
            else if (true == UEngineInput::GetInst().IsPress('S'))
            {

                SpriteRenderer->ChangeAnimation("Run_Front");
                
            }
            else if (true == UEngineInput::GetInst().IsPress('W'))
            {
                SpriteRenderer->ChangeAnimation("Run_Back");
            }
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


    SpriteRenderer->CreateAnimation("Item_Run_front", "Farmer_Right_2.png", { 27,15,27,28,2,28 }, { 0.1f , 0.1f, 0.1f, 0.1f, 0.1f, 0.1f });
    SpriteRenderer->CreateAnimation("Item_Idle_front", "Farmer_Right_2.png", { 0,0 },  0.1f, true);

    SpriteRenderer->CreateAnimation("Item_Run_Back", "Farmer_Right_2.png", { 16,10,16,17,11,17 }, { 0.1f , 0.1f, 0.1f, 0.1f, 0.1f, 0.1f });
    SpriteRenderer->CreateAnimation("Item_Idle_Back", "Farmer_Right_2.png", {9,9 }, 0.1f, true);

    SpriteRenderer->CreateAnimation("Item_Run_Right", "Farmer_Right_2.png", { 3,5,4,29,8,4 }, { 0.1f , 0.1f, 0.1f, 0.1f, 0.1f, 0.1f });
    SpriteRenderer->CreateAnimation("Item_Idle_Right", "Farmer_Right_2.png", { 4,4 }, 0.1f, true);

    SpriteRenderer->CreateAnimation("Item_Run_Left", "Farmer_Left_2.png", { 3,5,4,29,8,4 }, { 0.1f , 0.1f, 0.1f, 0.1f, 0.1f, 0.1f });
    SpriteRenderer->CreateAnimation("Item_Idle_Left", "Farmer_Left_2.png", { 4,4 }, 0.1f, true);


}

void APlayer::SetAnimationDuration(float _Duration)
{
    AnimationDuration = _Duration;

}

void APlayer::PlayerAnimationTimer(float _DeltaTime, float _Duration)
{

    if (IsAnimationPlay)
    {
        AnimationTimer += _DeltaTime;
        if (AnimationTimer >= _Duration)
        {
            IsAnimationPlay = false;
            AnimationTimer = 0.0f;
        }
    }
}


int APlayer::GetCurSlotNum()
{
    int CurSlotNum = PlayerUI->GetCulSlotNum();
    return CurSlotNum;
}

std::string APlayer::CurSlotCheck()
{
    return PlayerUI->CurSlotItemName();
}