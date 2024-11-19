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
#include "PlayerUI.h"


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

    CropTileMap = GetWorld()->SpawnActor<ATileMap>();
    CropTileMap->Create({ 69,56 }, { 70, 70 });

    FarmTileMap = GetWorld()->SpawnActor<ATileMap>();
    FarmTileMap->Create({ 69,56 }, { 70, 70 });

    Player->SetTileMap(FarmTileMap);
    Player->SetTileMap(CropTileMap);

    AFarmMap* GroundTileMap = GetWorld()->SpawnActor<AFarmMap>();

    Player->SetActorLocation({ 3700, 1050 });

    float PlayerLocationX = Player->GetActorLocation().X;
    float PlayerLocationY = Player->GetActorLocation().Y - 10;
    FVector2D PlayerLocation = { PlayerLocationX,PlayerLocationY };

    // house
    FIntPoint HousePoint = FarmTileMap->LocationToIndex({ 3790.0f, 770.0f });
    FIntPoint TreePoint = FarmTileMap->LocationToIndex({ 3790.0f, 1200.0f });
    FIntPoint TreePoint1 = FarmTileMap->LocationToIndex({ 3860.0f, 1200.0f });
    FIntPoint TreePoint2 = FarmTileMap->LocationToIndex({ 3930.0f, 1200.0f });
    FarmTileMap->SetTileIndex("HouseTile", HousePoint, { -5, -45 }, { 541.5f, 541.5f }, 0);
    FarmTileMap->SetTileIndex("TreeTile", TreePoint, { 0, -110 }, { 144, 240 }, 0, false, 0);
    FarmTileMap->SetTileIndex("TreeTile", TreePoint1, { 0, -110 }, { 144, 240 }, 0, false, 0);
    FarmTileMap->SetTileIndex("TreeTile", TreePoint2, { 0, -110 }, { 144, 240 }, 0, false, 0);
}

void AFarmGameMode::Tick(float _DeltaTime)
{
    Super::Tick(_DeltaTime);
    APlayer* Player = GetWorld()->GetPawn<APlayer>();
    Player->SetColImage("farm_col.png");

    if (true == UEngineInput::GetInst().IsDown('P'))
    {
        speed += 100;
    }
    else if (true == UEngineInput::GetInst().IsDown('M'))
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
        TileDestroy();
    }

    GetFarmTileSpriteName(Player->GetActorLocation());
    GetCropTileSpriteName(Player->GetActorLocation());

}


void AFarmGameMode::PutTile(float _DeltaTime)
{
    APlayer* Player = GetWorld()->GetPawn<APlayer>();
    float PlayerLocationX = Player->GetActorLocation().X;
    float PlayerLocationY = Player->GetActorLocation().Y - 10;

    FVector2D PlayerLocation = { PlayerLocationX,PlayerLocationY };
    FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
    FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();

    FVector2D CameraPos = GetWorld()->GetCameraPos();
    float MousePosX = MousePos.X + CameraPos.X;
    float MousePosY = MousePos.Y + CameraPos.Y;

    float TilePosX = MousePos.X - FarmTileMap->GetActorLocation().X;
    float TilePosY = MousePos.Y - FarmTileMap->GetActorLocation().Y + 53;

    FIntPoint Point = FarmTileMap->LocationToIndex({ TilePosX, TilePosY });
    FIntPoint MousePoint = FarmTileMap->LocationToIndex({ MousePosX, MousePosY });

    if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON))
    {
        switch (TileImages)
        {
        case ETileImage::Dirt:
          
            break;

        case ETileImage::Tree001:
            FarmTileMap->SetTileIndex("TreeTile", MousePoint, { 0, -110 }, { 144, 240 }, 0, false, 0);
            break;

        case ETileImage::Crops:


            break;
        default:
            break;
        }
        std::string CurSlotName = Player->CurSlotCheck();

        if ("Hoe" == CurSlotName)
        {
            if (Player->IsMouseInPlayerPos == true)
            {
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
        }


        if (GetFarmTileSpriteName({ MousePosX ,MousePosY }) == "DIRT.PNG" && true == Player->IsMouseInPlayerPos && "Seeds" == CurSlotName)
        {
            CropTileMap->SetTileIndex("parsnip.png", MousePoint, { -3, -20 }, { 70, 70 }, 0, true, 4);
        }
    }

    // Test코드 - Home키 누르면 땅과 다 자란 식물 마우스 위치에 생성
    if (true == UEngineInput::GetInst().IsDown(VK_HOME))
    {
        FarmTileMap->SetTileLocation("Dirt.png", { MousePosX, MousePosY }, 0);
        CropTileMap->SetTileIndex("parsnip.png", MousePoint, { -3, -20 }, { 70, 70 }, 4, true, 4);
    }
    
}

void AFarmGameMode::TileDestroy()
{
    APlayer* Player = GetWorld()->GetPawn<APlayer>();
    float PlayerLocationX = Player->GetActorLocation().X;
    float PlayerLocationY = Player->GetActorLocation().Y - 10;

    FVector2D Size = UEngineAPICore::GetCore()->GetMainWindow().GetWindowSize();
    FVector2D TileLocation = { PlayerLocationX, PlayerLocationY };

    FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
    FVector2D CameraPos = GetWorld()->GetCameraPos();
    float MousePosX = MousePos.X + CameraPos.X;
    float MousePosY = MousePos.Y + CameraPos.Y;

    FIntPoint FarmMousePoint = FarmTileMap->LocationToIndex({ MousePosX, MousePosY });
    FIntPoint CropMousePoint = CropTileMap->LocationToIndex({ MousePosX, MousePosY});

    switch (Player->PlayerDir)
    {
    case EPlayerDir::Left:
        TileLocation += {-FarmTileMap->GetTileSize().Half().X, 0.0};
        break;
    case EPlayerDir::Right:
        TileLocation += {FarmTileMap->GetTileSize().Half().X, 0.0};
        break;
    case EPlayerDir::Up:
        TileLocation += {0.0, -FarmTileMap->GetTileSize().Half().Y};
        break;
    case EPlayerDir::Down:
        TileLocation += {0.0, FarmTileMap->GetTileSize().Half().Y};
        break;
    default:
        break;
    }

    FIntPoint FarmCurTileLocation = FarmTileMap->LocationToIndex({ TileLocation.X, TileLocation.Y });
    FIntPoint CropCurTileLocation = CropTileMap->LocationToIndex({ TileLocation.X, TileLocation.Y });
    UEngineDebug::CoreOutPutString(GetFarmTileSpriteName(TileLocation));
    UEngineDebug::CoreOutPutString(GetCropTileSpriteName(TileLocation));

    if (true == UEngineInput::GetInst().IsDown(VK_RBUTTON))
    {
        if ( GetFarmTileSpriteName(TileLocation) == "TREETILE")
        {

            Tile* Tile = FarmTileMap->GetTileRef(FarmCurTileLocation);

            if (nullptr != Tile->SpriteRenderer)
            {
                Tile->SpriteRenderer->Destroy();
                Tile->SpriteRenderer = nullptr;
                FarmTileMap->TileDestroy(FarmCurTileLocation);

                // 플레이어의 TreeTile 포인터 초기화
                Player->TreeTile = nullptr;
                Player->PreviousTreeTile = nullptr;
            }

            // Tree Item Drop
            ItemDrop("Wood","Items.png", TileLocation, Player->GetActorLocation(), 941, 3.0f);
        }
        if (GetCropTileSpriteName(TileLocation) == "PARSNIP.PNG")
        {

            Tile* Tile = CropTileMap->GetTileRef(CropCurTileLocation);

            if (nullptr != Tile->SpriteRenderer)
            {
                Tile->SpriteRenderer->Destroy();
                Tile->SpriteRenderer = nullptr;
                CropTileMap->TileDestroy(CropCurTileLocation);

                // 플레이어의 TreeTile 포인터 초기화
                Player->TreeTile = nullptr;
                Player->PreviousTreeTile = nullptr;
            }

            // Tree Item Drop
            ItemDrop("parsnip", "Items.png", TileLocation, Player->GetActorLocation(), 32, 3.0f);
        }
    }
}

void AFarmGameMode::ItemDrop(std::string _ItemName, std::string _SpriteName, FVector2D _ItemLocatioln, FVector2D _PlayerPos, int _ItemIndex, float _ItemScale)
{
    Item = GetWorld()->SpawnActor<AItem>();
    Item->ItemSetSprite(_SpriteName, _ItemIndex, _ItemScale);
    Item->SetActorLocation(_ItemLocatioln);
    Item->SetOrder(ERenderOrder::UI);
    Item->SetForce();
    Item->SetItemType(_ItemName);
    Item->GainItemInfo(_ItemName,_SpriteName, _ItemIndex, _ItemScale);
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

std::string AFarmGameMode::GetFarmTileSpriteName(FVector2D Location)
{
    Tile* TileRef = FarmTileMap->GetTileRef(Location);
    if (TileRef)
    {
        std::string SpriteName = TileRef->GetSpriteName();

        return SpriteName;
    }
    else
    {
        return "NONE";

    }
    
}
std::string AFarmGameMode::GetCropTileSpriteName(FVector2D Location)
{
    Tile* TileRef = CropTileMap->GetTileRef(Location);
    if (TileRef)
    {
        std::string SpriteName = TileRef->GetSpriteName();

        return SpriteName;
    }
    else
    {
        return "NONE";

    }

}


