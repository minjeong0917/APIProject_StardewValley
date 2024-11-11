#include "PreCompile.h"
#include "FarmGameMode.h"

// Engine
#include <EngineCore/Level.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>

// contents
#include "FarmMap.h"
#include "Player.h"
#include "Clock.h"
#include "Gold.h"





AFarmGameMode::AFarmGameMode()
{
}

AFarmGameMode::~AFarmGameMode()
{
}

void AFarmGameMode::BeginPlay()
{
    APlayer* Player = GetWorld()->GetPawn<APlayer>();
    Player->SetBackImage("Farm.png");

    FarmTileMap = GetWorld()->SpawnActor<ATileMap>();
    FarmTileMap->Create({ 69,56 }, { 70, 70 });

    CropTileMap = GetWorld()->SpawnActor<ATileMap>();
    CropTileMap->Create({ 69,56 }, { 70, 70 });

    Player->SetTileMap(FarmTileMap);
    Player->SetTileMap(CropTileMap);

    AFarmMap* GroundTileMap = GetWorld()->SpawnActor<AFarmMap>();

    Player->SetActorLocation({ 3700, 1050 });


    UIImageRender();

}

void AFarmGameMode::Tick(float _DeltaTime)
{
    Super::Tick(_DeltaTime);
    APlayer* Player = GetWorld()->GetPawn<APlayer>();
    Player->SetColImage("farm_col.png");

    TileChange();

    if (false == Player->IsPlayerMove)
    {
        PutTile(_DeltaTime);

    }

    GetTileSpriteName(Player->GetActorLocation());

    FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
    Cursor->SetActorLocation({ MousePos.X+10, MousePos.Y+15 });

    int Min =  MinTime->SetMinute(_DeltaTime);
    HourTime->SetHour(Min);


    if (true == UEngineInput::GetInst().IsDown(VK_MULTIPLY))
    {
        MinTime->Speed += 100;
    }

}

void AFarmGameMode::UIImageRender()
{
    APlayer* Player = GetWorld()->GetPawn<APlayer>();
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
    Gold->SetValue(Player->GetGold());

    // Cursor
    Cursor = GetWorld()->SpawnActor<ACursor>();

    // Time
    MinTime = GetWorld()->SpawnActor<ATime>();
    MinTime->SetActorLocation({ Size.iX() - 100 , 138 });
    MinTime->SetTextSpriteName("Time.png");

    HourTime = GetWorld()->SpawnActor<ATime>();
    HourTime->SetActorLocation({ Size.iX() - 145 , 138});
    HourTime->SetTextSpriteName("Time.png");

}

void AFarmGameMode::PutTile(float _DeltaTime)
{
    APlayer* Player = GetWorld()->GetPawn<APlayer>();
    float PlayerLocationX = Player->GetActorLocation().X;
    float PlayerLocationY = Player->GetActorLocation().Y - 10;

    FVector2D PlayerLocation = { PlayerLocationX,PlayerLocationY };

    // house
    FIntPoint HousePoint = FarmTileMap->LocationToIndex({ 3790.0f, 770.0f });
    FarmTileMap->SetTileIndex("HouseTile", HousePoint, { -5, -45 }, { 541.5f, 541.5f }, 0);



    FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();

    FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
    float MousePosX = MousePos.X + PlayerLocation.X - Size.Half().X;
    float MousePosY = MousePos.Y + PlayerLocation.Y - Size.Half().Y;

    FVector2D Direction = { MousePosX - PlayerLocation.X, MousePosY - PlayerLocation.Y };

    float DirectionAbsX = std::abs(Direction.X);
    float DirectionAbsY = std::abs(Direction.Y);

    bool IsMouseInPlayerPos = false;

    if (DirectionAbsX <= 110 && DirectionAbsY <= 110 && DirectionAbsX >= 0 && DirectionAbsY >= 0)
    {
        IsMouseInPlayerPos = true;
    }


    float TilePosX = MousePos.X - FarmTileMap->GetActorLocation().X;
    float TilePosY = MousePos.Y - FarmTileMap->GetActorLocation().Y + 53;
    FIntPoint Point = FarmTileMap->LocationToIndex({ TilePosX, TilePosY });
    FIntPoint Point2 = FarmTileMap->LocationToIndex({ MousePosX, MousePosY });
    UEngineDebug::CoreOutPutString(std::to_string(MousePosX));
    UEngineDebug::CoreOutPutString(std::to_string(MousePosY));


    if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON))
    {
        switch (TileImages)
        {
        case ETileImage::Dirt:
            if (IsMouseInPlayerPos)
            {
                if (DirectionAbsX > DirectionAbsY) {
                    if (Direction.X > 0) {
                        Player->PlayerDir = EPlayerDir::Right;
                    }
                    else {
                        Player->PlayerDir = EPlayerDir::Left;
                    }
                }
                else {
                    if (Direction.Y > 0) {
                        Player->PlayerDir = EPlayerDir::Down;
                    }
                    else {
                        Player->PlayerDir = EPlayerDir::Up;
                    }
                }

                FarmTileMap->SetTileLocation("Dirt.png", { MousePosX, MousePosY }, 0);
            }
            else
            {
                switch (Player->PlayerDir)
                {
                case EPlayerDir::Left:
                    PlayerLocation += {-FarmTileMap->GetTileSize().X, 0.0};
                    break;
                case EPlayerDir::Right:
                    PlayerLocation += {FarmTileMap->GetTileSize().X, 0.0};

                    break;
                case EPlayerDir::Up:
                    PlayerLocation += {0.0, -FarmTileMap->GetTileSize().Y};
                    break;
                case EPlayerDir::Down:
                    PlayerLocation += {0.0, FarmTileMap->GetTileSize().Y};
                    break;
                default:
                    break;
                }

                FarmTileMap->SetTileLocation("Dirt.png", { PlayerLocation.X, PlayerLocation.Y }, 0);
            }

            break;

        case ETileImage::Tree001:
            FarmTileMap->SetTileIndex("TreeTile", Point, { 0, -110 }, { 144, 240 }, 0, false);
            break;

        case ETileImage::Crops:
            if (GetTileSpriteName({ MousePosX ,MousePosY }) == "DIRT.PNG" && true == IsMouseInPlayerPos)
            {
                CropTileMap->SetTileIndex("parsnip.png", Point2, { -3, -20 }, { 70, 70 }, 0);
            }

            break;
        default:
            break;
        }
    }

}


bool AFarmGameMode::CropsTime(float _Deltatime)
{
    float Time = 0;
    int hour = 0;
    int Speed = MinTime->Speed;

    Time += _Deltatime * Speed;
    int Min = static_cast<int>(Time / 10);
    IsNextDay = false;

    if (Min >= 60)
    {
        Min = 0;
        Time = 0;
        ++hour;
    }
    if (24 == hour)
    {
        IsNextDay = true;
        return IsNextDay;
    }
    return IsNextDay;
}


void AFarmGameMode::TileChange()
{
    std::string TileImageName;

    switch (TileImages)
    {
    case ETileImage::Dirt:
        TileImageName = "Dirt";
        break;
    case ETileImage::Tree001:
        TileImageName = "Tree001";
        break;
    case ETileImage::Crops:
        TileImageName = "parsnip";
        break;
    default:
        TileImageName = "Unknown";
        break;
    }

    UEngineDebug::CoreOutPutString("CurTile : " + TileImageName);
    int curTileImg = static_cast<int>(TileImages);

    if (true == UEngineInput::GetInst().IsDown(VK_RIGHT))
    {

        TileImages = static_cast<ETileImage>(curTileImg + 1);
        if (TileImages >= ETileImage::End)
        {
            TileImages = ETileImage::Dirt;
        }
        return;
    }

    if (true == UEngineInput::GetInst().IsDown(VK_LEFT))
    {
        TileImages = static_cast<ETileImage>(curTileImg - 1);
        if (TileImages < ETileImage::Dirt)
        {
            TileImages = ETileImage::Dirt;
        }
        return;
    }
}

std::string AFarmGameMode::GetTileSpriteName(FVector2D Location)
{
    Tile* TileRef = FarmTileMap->GetTileRef(Location);
    if (TileRef)
    {
        std::string SpriteName = TileRef->GetSpriteName();
        UEngineDebug::CoreOutPutString("TileName: " + SpriteName);
        return SpriteName;
    }
    else
    {
        UEngineDebug::CoreOutPutString("타일이 없습니다.");
        return "NONE";

    }
}
