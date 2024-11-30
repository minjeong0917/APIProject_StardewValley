#include "PreCompile.h"
#include "FarmGameMode.h"

// Engine
#include <EngineCore/Level.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineAPICore.h>
#include <EngineCore/EngineCoreDebug.h>
#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineRandom.h>

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

    GroundTileMap = GetWorld()->SpawnActor<AFarmMap>();

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
        FarmTileMap->SetTileIndex("TREE001.PNG", TreePoint, { 0, -110 }, { 144, 240 }, 0, false, 0, 10);

    }
}



void AFarmGameMode::Tick(float _DeltaTime)
{
    if (true == UEngineInput::GetInst().IsDown(VK_SPACE))
    {
        UEngineAPICore::GetCore()->OpenLevel("Town");
    }
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

    //CropTileMap->CropCheck(_DeltaTime * speed * 10);
    TileCropCheck(_DeltaTime * speed * 10, { 0,0 });

    TileChange();

    if (false == Player->IsPlayerMove && false == Player->GetIsEnter())
    {
        PutTile(_DeltaTime);
        TileDestroyLocation(_DeltaTime);
    }

    GetFarmTileSpriteName(Player->GetActorLocation());
    GetCropTileSpriteName(Player->GetActorLocation());

    if (IsTreeHit == true)
    {
        TreeMove(_DeltaTime);
    }


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
            //FarmTileMap->SetTileIndex("TREE001.PNG", MousePoint, { 0, -110 }, { 144, 240 }, 0, false, 0, 10);
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
                BGMPlayer = UEngineSound::Play("hoeHit.wav");
            }
            else if (GetFarmTileSpriteName({ PlayerLocation.X, PlayerLocation.Y }) == "NONE")
            {

                FarmTileMap->SetTileLocation("Dirt.png", { PlayerLocation.X, PlayerLocation.Y }, 0);
                BGMPlayer = UEngineSound::Play("hoeHit.wav");
            }
        }

        if ("WateringCan" == CurSlotName)
        {
            FVector2D PlayerLocation = PlayerDirToTileMap(FarmTileMap);

            if (Player->IsMouseInPlayerPos == true && GetFarmTileSpriteName(MouseLocation) == "DIRT.PNG")
            {
                BGMPlayer = UEngineSound::Play("WateringCan.wav");

                FarmTileMap->SetTileLocation("WetDirt.png", MouseLocation, 0);
            }
            else if (GetFarmTileSpriteName({ PlayerLocation.X, PlayerLocation.Y }) == "DIRT.PNG")
            {
                FarmTileMap->SetTileLocation("WetDirt.png", { PlayerLocation.X, PlayerLocation.Y }, 0);
            }
        }

        if ((GetCropTileSpriteName(MouseLocation) != "PARSNIP.PNG" || 
            GetCropTileSpriteName(MouseLocation) != "GREENBEAN.PNG" ||
            GetCropTileSpriteName(MouseLocation) != "PARSNIP.PNG" || 
            GetCropTileSpriteName(MouseLocation) != "CAULIFLOWER.PNG" || 
            GetCropTileSpriteName(MouseLocation) != "POTATO.PNG" || 
            GetCropTileSpriteName(MouseLocation) != "KALE.PNG" ||
            GetCropTileSpriteName(MouseLocation) != "RHUBARB.PNG" ||
            GetCropTileSpriteName(MouseLocation) != "GARLIC.PNG")&&
            (GetFarmTileSpriteName(MouseLocation) == "DIRT.PNG" || GetFarmTileSpriteName(MouseLocation) == "WETDIRT.PNG")
            && true == Player->IsMouseInPlayerPos)
        {
            if ("ParsnipSeed" == CurSlotName)
            {
                CropTileMap->SetTileIndex("parsnip.png", MousePoint, { -3, -20 }, { 70, 70 }, 0, true, 4);
                UseItem();
                CropTilePoint.push_back(MousePoint);

            }
            if ("BeanStarter" == CurSlotName)
            {
                CropTileMap->SetTileIndex("GreenBean.png", MousePoint, { 0, -50 }, { 70, 138 }, 0, true, 6);
                UseItem();
                CropTilePoint.push_back(MousePoint);

            }
            if ("CauliflowerSeed" == CurSlotName)
            {
                CropTileMap->SetTileIndex("Cauliflower.png", MousePoint, { 0, 0 }, { 70, 70 }, 0, true, 5);
                UseItem();
                CropTilePoint.push_back(MousePoint);
            }
            if ("PotatoSeed" == CurSlotName)
            {
                CropTileMap->SetTileIndex("Potato.png", MousePoint, { 0, -20 }, { 70, 70 }, 0, true, 5);
                UseItem();
                CropTilePoint.push_back(MousePoint);

            }
            if ("KaleSeed" == CurSlotName)
            {
                CropTileMap->SetTileIndex("Kale.png", MousePoint, { 0, -15 }, { 70, 70 }, 0, true, 4);
                UseItem();
                CropTilePoint.push_back(MousePoint);

            }
            if ("RhubarbSeed" == CurSlotName)
            {
                CropTileMap->SetTileIndex("Rhubarb.png", MousePoint, { 0, -20 }, { 70, 70 }, 0, true, 5);
                UseItem();
                CropTilePoint.push_back(MousePoint);

            }
            if ("GarlicSeed" == CurSlotName)
            {
                CropTileMap->SetTileIndex("Garlic.png", MousePoint, { -3, -20 }, { 70, 70 }, 0, true, 4);
                UseItem();
                CropTilePoint.push_back(MousePoint);

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

void AFarmGameMode::TileCropCheck(float _DeltaTime, FIntPoint _Index)
{
    APlayer* Player = GetWorld()->GetPawn<APlayer>();

    for (size_t i = 0; i < CropTilePoint.size(); i++)
    {

        std::string Name = CropTileMap->GetTileSpriteName(CropTilePoint[i]);

        int Index = CropTileMap->GetTileIndex(CropTilePoint[i]);
        int MaxIndex = CropTileMap->GetTileMaxIndex(CropTilePoint[i]);


        float CurTime = CropTileMap->GetTileCurTime(CropTilePoint[i]);
        float Time = CropTileMap->GetTileTime(CropTilePoint[i]);
        if (FarmTileMap->GetTileSpriteName(CropTilePoint[i]) == "WETDIRT.PNG")
        {
            CurTime += _DeltaTime;
            if (true == Player->PlayerUI->IsOverDays)
            {
                CurTime = Time+1;
                
            }
        }

        CropTileMap->SetTileCurTime(CropTilePoint[i], CurTime);



        if (CurTime > Time)
        {
            if (Index == MaxIndex)
            {
                return;
            }

            ++Index;
            CropTileMap->SetTileIndex(CropTilePoint[i], Index);
            CropTileMap->SetTileSprite(CropTilePoint[i], Name, Index);
            CropTileMap->SetTileCurTime(CropTilePoint[i], 0);
            FarmTileMap->SetTileSprite(CropTilePoint[i], "DIRT.PNG", 0);
        }
    }
    if (Player->PlayerUI->IsOverDays == true)
    {
        Player->PlayerUI->IsOverDays = false;
    }
}

void AFarmGameMode::TileDestroyLocation(float _DeltaTime)
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
            if (GetFarmTileSpriteName(MouseLocation) == "TREE001.PNG"   && Player->IsMouseInPlayerPos == true && GetFarmTileSpriteName(TileLocation) == "TREE001.PNG" && TreeTime == 0)
            {

                BGMPlayer = UEngineSound::Play("Axe.wav");


                int TreeCount = FarmTileMap->GetTreeTileCount(FarmCurTileLocation);
                TreeCount -= 1;
                if (TreeCount == 0)
                {
                    TileDestroy(FarmTileMap, FarmCurTileLocation);


                    ItemDrop(_DeltaTime, "Wood", "Items.png", TileLocation, Player->GetActorLocation(), 941, 2.0f,6);

                    FarmTileMap->SetTileIndex("TREE002.PNG", FarmCurTileLocation, { 0, -20}, { 16*3.f, 20 * 3.f }, 0, false, 0 , 5);
                    FarmTileMap->SetTreeTileCount(FarmCurTileLocation, 5);
                }

                IsTreeHit = true;
                TileLoc = FarmMousePoint;
                FarmTileMap->SetTreeTileCount(FarmMousePoint, TreeCount);


            }

            else if (GetFarmTileSpriteName(MouseLocation) == "TREE002.PNG" && Player->IsMouseInPlayerPos == true && GetFarmTileSpriteName(TileLocation) == "TREE002.PNG" && TreeTime == 0)
            {

                BGMPlayer = UEngineSound::Play("Axe.wav");


                int TreeCount = FarmTileMap->GetTreeTileCount(FarmMousePoint);

                if (TreeCount <= 0)
                {
                    TileDestroy(FarmTileMap, FarmCurTileLocation);
         
                    ItemDrop(_DeltaTime, "Wood", "Items.png", TileLocation, Player->GetActorLocation(), 941, 2.0f, 2);
           
                }

                TreeCount -= 1;
                IsTreeHit = true;
                TileLoc = FarmMousePoint;
                FarmTileMap->SetTreeTileCount(FarmMousePoint, TreeCount);


            }
        }

        CropCheck(_DeltaTime, CropMousePoint, "Parsnip.PNG", "parsnip", "Items.png", MouseLocation, Player->GetActorLocation(), 32, 3.0f);
        CropCheck(_DeltaTime, CropMousePoint, "GreenBean.png", "GreenBean", "Items.png", MouseLocation, Player->GetActorLocation(), 244, 3.0f);
        CropCheck(_DeltaTime, CropMousePoint, "Cauliflower.png", "Cauliflower", "Items.png", MouseLocation, Player->GetActorLocation(), 246, 3.0f);
        CropCheck(_DeltaTime, CropMousePoint, "Potato.png", "Potato", "Items.png", MouseLocation, Player->GetActorLocation(), 256, 3.0f);
        CropCheck(_DeltaTime, CropMousePoint, "Kale.png", "Kale", "Items.png", MouseLocation, Player->GetActorLocation(), 330, 3.0f);
        CropCheck(_DeltaTime, CropMousePoint, "Rhubarb.png", "Rhubarb", "Items.png", MouseLocation, Player->GetActorLocation(), 332, 3.0f);
        CropCheck(_DeltaTime, CropMousePoint, "Garlic.png", "Garlic", "Items.png", MouseLocation, Player->GetActorLocation(), 328, 3.0f);

    }
}

void AFarmGameMode::CropCheck(float _Deltatime, FIntPoint _TileLoc, std::string _TileSpriteName, std::string _ItemName, std::string _SpriteName, FVector2D _ItemLocatioln, FVector2D _PlayerPos, int _ItemIndex, float _ItemScale)
{
    std::string UpperName = UEngineString::ToUpper(_TileSpriteName);

    if (GetCropTileSpriteName(_ItemLocatioln) == UpperName)
    {

        Tile* Tile = CropTileMap->GetTileRef(_TileLoc);
        if (Tile->SpriteIndex == Tile->MaxSpriteIndex) // 다 자라야 캐지도록
        {
            TileDestroy(CropTileMap, _TileLoc);
            // Tree Item Drop
            ItemDrop(_Deltatime, _ItemName, _SpriteName, _ItemLocatioln, _PlayerPos, _ItemIndex, _ItemScale);
        }
    }
}

void AFarmGameMode::TreeMove(float _DeltaTime)
{
    if (FarmTileMap->GetTileSpriteName(TileLoc) == "TREE001.PNG")
    {
        TreeTime += _DeltaTime;
        if (TreeTime >= 0.1 && TreeTime < 0.15)
        {
            FarmTileMap->SetTilePivot(TileLoc, { 5, -110 });
        }
        else if (TreeTime >= 0.15 && TreeTime < 0.2)
        {
            FarmTileMap->SetTilePivot(TileLoc, { -5, -110 });
        }
        else if (TreeTime >= 0.2 && TreeTime < 0.25)
        {
            FarmTileMap->SetTilePivot(TileLoc, { +3,-110 });
        }
        else if (TreeTime >= 0.25 && TreeTime < 0.3)
        {
            FarmTileMap->SetTilePivot(TileLoc, { -3, -110 });
        }
        else if (TreeTime >= 0.3 && TreeTime < 0.35)
        {
            FarmTileMap->SetTilePivot(TileLoc, { 1, -110 });
        }
        else if (TreeTime >= 0.35 && TreeTime < 0.4)
        {
            FarmTileMap->SetTilePivot(TileLoc, { -1, -110 });
        }
        else if (TreeTime >= 0.4)
        {
            TreeTime = 0;
            IsTreeHit = false;
        }
    }
    if (FarmTileMap->GetTileSpriteName(TileLoc) == "TREE002.PNG")
    {
        TreeTime += _DeltaTime;

        if (TreeTime >= 0.2 && TreeTime < 0.25)
        {
            FarmTileMap->SetTilePivot(TileLoc, { +3,-20 });
        }
        else if (TreeTime >= 0.25 && TreeTime < 0.3)
        {
            FarmTileMap->SetTilePivot(TileLoc, { -3, -20 });
        }
        else if (TreeTime >= 0.3 && TreeTime < 0.35)
        {
            FarmTileMap->SetTilePivot(TileLoc, { 1, -20 });
        }
        else if (TreeTime >= 0.35 && TreeTime < 0.4)
        {
            FarmTileMap->SetTilePivot(TileLoc, { -1, -20 });
        }
        else if (TreeTime >= 0.4)
        {
            TreeTime = 0;
            IsTreeHit = false;
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
        TileLocation += {0.0, -_TileMap->GetTileSize().Half().Y};
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
    BGMPlayer = UEngineSound::Play("DirtyHit.wav");
    APlayer* Player = GetWorld()->GetPawn<APlayer>();
    Player->UseItem();
}

void AFarmGameMode::ItemDrop(float _Deltatime, std::string _ItemName, std::string _SpriteName, FVector2D _ItemLocatioln, FVector2D _PlayerPos, int _ItemIndex, float _ItemScale, int _ItemCount)
{
    for (int i = 0; i < _ItemCount; i++)
    {
        UEngineRandom Random;
        Random.SetSeed(i);
        FVector2D RandomDir = { Random.RandomInt(-50, 50),  Random.RandomInt(-50, 50) };
        AItem* Item = GetWorld()->SpawnActor<AItem>();
        Item->ItemSetSprite(_SpriteName, _ItemIndex, _ItemScale);
        Item->SetActorLocation(_ItemLocatioln + RandomDir);
        Item->SetOrder(Item->GetActorLocation().Y);
        Item->SetForce();
        Item->SetItemType(_ItemName);
        Item->GainItemInfo(_ItemName, _SpriteName, _ItemIndex, _ItemScale);
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


