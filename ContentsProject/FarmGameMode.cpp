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

    Player->SetTileMap(FarmTileMap);

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
        PutTile();
    }
    GetTileSpriteName(Player->GetActorLocation());

    FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
    Cursor->SetActorLocation({ MousePos.X+10, MousePos.Y+15 });


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

    Cursor = GetWorld()->SpawnActor<ACursor>();

}



void AFarmGameMode::PutTile()
{
    APlayer* Player = GetWorld()->GetPawn<APlayer>();
    float PlayerLocationX = Player->GetActorLocation().X;
    float PlayerLocationY = Player->GetActorLocation().Y - 10;

    FVector2D PlayerLocation = { PlayerLocationX,PlayerLocationY };

    FIntPoint HousePoint = FarmTileMap->LocationToIndex({ 3790.0f, 770.0f });
    FarmTileMap->SetTileIndex("HouseTile", HousePoint, { -5, -45 }, { 541.5f, 541.5f }, 0);


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

    float TilePosX = PlayerLocation.X - FarmTileMap->GetActorLocation().X;
    float TilePosY = PlayerLocation.Y - FarmTileMap->GetActorLocation().Y + 53;
    FIntPoint Point = FarmTileMap->LocationToIndex({ TilePosX, TilePosY });

    if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON))
    {
        switch (TileImages)
        {
        case ETileImage::Dirt:
            FarmTileMap->SetTileLocation("Dirt.png", { PlayerLocation.X, PlayerLocation.Y }, 0);
            break;

        case ETileImage::Tree001:
            FarmTileMap->SetTileIndex("TreeTile", Point, { 0, -110 }, { 144, 240 }, 0, false);
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
void AFarmGameMode::GetTileSpriteName(FVector2D Location)
{
    Tile* TileRef = FarmTileMap->GetTileRef(Location);
    if (TileRef)
    {
        std::string SpriteName = TileRef->GetSpriteName();
        UEngineDebug::CoreOutPutString("TileName: " + SpriteName);
    }
    else
    {
        UEngineDebug::CoreOutPutString("타일이 없습니다.");
    }
}
