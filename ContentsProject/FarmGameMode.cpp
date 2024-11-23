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
    FarmTileMap->SetTileIndex("HouseTile", HousePoint, { -5, -45 }, { 541.5f, 541.5f }, 0);

    for (int i = 0; i < 10; i++)
    {
        FIntPoint TreePoint = FarmTileMap->LocationToIndex({ 3790.0f + (70 * i), 1200.0f });
        FarmTileMap->SetTileIndex("TreeTile", TreePoint, { 0, -110 }, { 144, 240 }, 0, false, 0);

    }

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

    if (false == Player->IsPlayerMove && false == Player->GetIsEnter())
    {
        PutTile(_DeltaTime);
        TileDestroyLocation();
    }

    GetFarmTileSpriteName(Player->GetActorLocation());
    GetCropTileSpriteName(Player->GetActorLocation());

}


void AFarmGameMode::PutTile(float _DeltaTime)
{
    APlayer* Player = GetWorld()->GetPawn<APlayer>();

    FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
    FVector2D CameraPos = GetWorld()->GetCameraPos();
    FVector2D MouseLocation = MousePos + CameraPos;

    FIntPoint MousePoint = FarmTileMap->LocationToIndex(MouseLocation);

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
            FVector2D PlayerLocation = PlayerDirToTileMap(FarmTileMap);

            if (Player->IsMouseInPlayerPos == true && GetFarmTileSpriteName(MouseLocation) == "NONE")
            {
                FarmTileMap->SetTileLocation("Dirt.png", MouseLocation, 0);
            }
            else if (GetFarmTileSpriteName({ PlayerLocation.X, PlayerLocation.Y }) == "NONE")
            {

                FarmTileMap->SetTileLocation("Dirt.png", { PlayerLocation.X, PlayerLocation.Y }, 0);
            }
        }

        if ("WateringCan" == CurSlotName)
        {
            FVector2D PlayerLocation = PlayerDirToTileMap(FarmTileMap);

            if (Player->IsMouseInPlayerPos == true && GetFarmTileSpriteName(MouseLocation) == "DIRT.PNG")
            {
                FarmTileMap->SetTileLocation("WetDirt.png", MouseLocation, 0);
            }
            else if (GetFarmTileSpriteName({ PlayerLocation.X, PlayerLocation.Y }) == "DIRT.PNG")
            {
                FarmTileMap->SetTileLocation("WetDirt.png", { PlayerLocation.X, PlayerLocation.Y }, 0);
            }
        }

        if (GetCropTileSpriteName(MouseLocation) != "PARSNIP.PNG" && (GetFarmTileSpriteName(MouseLocation) == "DIRT.PNG" || GetFarmTileSpriteName(MouseLocation) == "WETDIRT.PNG") && true == Player->IsMouseInPlayerPos)
        {
            if ("ParsnipSeed" == CurSlotName)
            {
                CropTileMap->SetTileIndex("parsnip.png", MousePoint, { -3, -20 }, { 70, 70 }, 0, true, 4);
                UseItem();
            }
            if ("BeanStarter" == CurSlotName)
            {
                CropTileMap->SetTileIndex("GreenBean.png", MousePoint, { 0, -50 }, { 70, 138 }, 0, true, 6);
                UseItem();
            }

        }
    }

    // Test코드 - Home키 누르면 땅과 다 자란 식물 마우스 위치에 생성
    if (true == UEngineInput::GetInst().IsDown(VK_HOME))
    {
        FarmTileMap->SetTileLocation("Dirt.png", MouseLocation, 0);
        CropTileMap->SetTileIndex("parsnip.png", MousePoint, { -3, -20 }, { 70, 70 }, 4, true, 4);
    }

}

void AFarmGameMode::TileDestroyLocation()
{
    APlayer* Player = GetWorld()->GetPawn<APlayer>();

    FVector2D MousePos = UEngineAPICore::GetCore()->GetMainWindow().GetMousePos();
    FVector2D CameraPos = GetWorld()->GetCameraPos();
    FVector2D MouseLocation = MousePos + CameraPos;

    FIntPoint FarmMousePoint = FarmTileMap->LocationToIndex(MouseLocation);
    FIntPoint CropMousePoint = CropTileMap->LocationToIndex(MouseLocation);
    FVector2D TileLocation = PlayerDirToTileMap(FarmTileMap);


    FIntPoint FarmCurTileLocation = FarmTileMap->LocationToIndex(TileLocation);
    FIntPoint CropCurTileLocation = CropTileMap->LocationToIndex(TileLocation);

    UEngineDebug::CoreOutPutString(GetFarmTileSpriteName(TileLocation));
    UEngineDebug::CoreOutPutString(GetCropTileSpriteName(TileLocation));

    std::string CurSlotName = Player->CurSlotCheck();

    if (true == UEngineInput::GetInst().IsDown(VK_LBUTTON))
    {
        if (CurSlotName == "Axe")
        {
            if (GetFarmTileSpriteName(MouseLocation) == "TREETILE"   && Player->IsMouseInPlayerPos == true)
            {

                TileDestroy(FarmTileMap, FarmMousePoint);
                ItemDrop("Wood", "Items.png", MouseLocation, Player->GetActorLocation(), 941, 3.0f);

                
            }
            else if (GetFarmTileSpriteName(TileLocation) == "TREETILE")
            {
                TileDestroy(FarmTileMap, FarmCurTileLocation);
                ItemDrop("Wood", "Items.png", TileLocation, Player->GetActorLocation(), 941, 3.0f);
            }
        }


        if (GetCropTileSpriteName(MouseLocation) == "PARSNIP.PNG")
        {

            Tile* Tile = CropTileMap->GetTileRef(CropMousePoint);
            if (Tile->SpriteIndex == Tile->MaxSpriteIndex) // 다 자라야 캐지도록
            {
                TileDestroy(CropTileMap, CropMousePoint);
                // Tree Item Drop
                ItemDrop("parsnip", "Items.png", MouseLocation, Player->GetActorLocation(), 32, 3.0f);
            }
        }

    }
}

FVector2D AFarmGameMode::PlayerDirToTileMap(ATileMap* _TileMap)
{
    APlayer* Player = GetWorld()->GetPawn<APlayer>();

    float PlayerLocationX = Player->GetActorLocation().X;
    float PlayerLocationY = Player->GetActorLocation().Y - 10;

    FVector2D TileLocation = { PlayerLocationX, PlayerLocationY };

    switch (Player->PlayerDir)
    {
    case EPlayerDir::Left:
        TileLocation += {-_TileMap->GetTileSize().X, 0.0};
        break;
    case EPlayerDir::Right:
        TileLocation += {_TileMap->GetTileSize().X, 0.0};
        break;
    case EPlayerDir::Up:
        TileLocation += {0.0, -_TileMap->GetTileSize().Y};
        break;
    case EPlayerDir::Down:
        TileLocation += {0.0, _TileMap->GetTileSize().Y};
        break;
    default:
        break;
    }

    return TileLocation;
}

void AFarmGameMode::TileDestroy(ATileMap* _TileMap, FIntPoint _Location)
{
    APlayer* Player = GetWorld()->GetPawn<APlayer>();

    Tile* Tile = _TileMap->GetTileRef(_Location);
    if (nullptr != Tile->SpriteRenderer)
    {
        Tile->SpriteRenderer->Destroy();
        Tile->SpriteRenderer = nullptr;
        _TileMap->TileDestroy(_Location);

        // 플레이어의 TreeTile 포인터 초기화
        Player->TreeTile = nullptr;
        Player->PreviousTreeTile = nullptr;
    }
}

void AFarmGameMode::UseItem()
{
    APlayer* Player = GetWorld()->GetPawn<APlayer>();
    Player->UseItem();
}

void AFarmGameMode::ItemDrop(std::string _ItemName, std::string _SpriteName, FVector2D _ItemLocatioln, FVector2D _PlayerPos, int _ItemIndex, float _ItemScale)
{
    Item = GetWorld()->SpawnActor<AItem>();
    Item->ItemSetSprite(_SpriteName, _ItemIndex, _ItemScale);
    Item->SetActorLocation(_ItemLocatioln);
    Item->SetOrder(ERenderOrder::UI);
    Item->SetForce();
    Item->SetItemType(_ItemName);
    Item->GainItemInfo(_ItemName, _SpriteName, _ItemIndex, _ItemScale);
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


