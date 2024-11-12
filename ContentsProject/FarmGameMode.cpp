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


}

void AFarmGameMode::Tick(float _DeltaTime)
{
    Super::Tick(_DeltaTime);
    APlayer* Player = GetWorld()->GetPawn<APlayer>();
    Player->SetColImage("farm_col.png");

    if (true == UEngineInput::GetInst().IsDown(VK_MULTIPLY))
    {
        speed += 100;
    }
    else if (true == UEngineInput::GetInst().IsDown(VK_DIVIDE))
    {

        if (speed >= 0)
        {
            speed -= 100;
        }
    }

    CropTileMap->CropCheck(_DeltaTime * speed * 10);
    TileChange();

    if (false == Player->IsPlayerMove)
    {
        PutTile(_DeltaTime);
    }

    GetTileSpriteName(Player->GetActorLocation());

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

    if (DirectionAbsX <= 70 && DirectionAbsY <= 70 && DirectionAbsX >= 0 && DirectionAbsY >= 0)
    {
        IsMouseInPlayerPos = true;
    }


    float TilePosX = MousePos.X - FarmTileMap->GetActorLocation().X;
    float TilePosY = MousePos.Y - FarmTileMap->GetActorLocation().Y + 53;
    FIntPoint Point = FarmTileMap->LocationToIndex({ TilePosX, TilePosY });
    FIntPoint Point2 = FarmTileMap->LocationToIndex({ MousePosX, MousePosY });


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
                CropTileMap->SetTileIndex("parsnip.png", Point2, { -3, -20 }, { 70, 70 }, 0, true, 5);
            }

            break;
        default:
            break;
        }
    }

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
