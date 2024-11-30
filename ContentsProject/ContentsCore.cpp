#include "PreCompile.h"
#include "ContentsCore.h"

#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineDebug.h>

#include <EnginePlatform/EngineSound.h>

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/ImageManager.h>

#include "FarmGameMode.h"
#include "TitleGameMode.h"
#include "TownGameMode.h"
#include "StoreGameMode.h"
#include "HouseGameMode.h"
#include "ShippingGameMode.h"

#include "Player.h"
#include "Clock.h"

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::BeginPlay()
{

    ReadySprite();

    // 윈도우 타이틀 지정
    UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("StardewValley");
    // 윈도우 크기와 위치 설정
    UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, { 1280, 720 });
    // 농장 레벨 생성 및 Open
    UEngineAPICore::GetCore()->CreateLevel<AFarmGameMode, APlayer>("Farm");
    UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, AActor>("Title");
    UEngineAPICore::GetCore()->CreateLevel<AShippingGameMode, APlayer>("Shipping");
    UEngineAPICore::GetCore()->CreateLevel<ATownGameMode, APlayer>("Town");
    UEngineAPICore::GetCore()->CreateLevel<AStoreGameMode, APlayer>("Store");
    UEngineAPICore::GetCore()->CreateLevel<AHouseGameMode, APlayer>("House");
    UEngineAPICore::GetCore()->OpenLevel("Title");
}

void ContentsCore::Tick()
{
}

void ContentsCore::ReadySprite()
{
    // Images 폴더 찾기
    {
        UEngineDirectory Dir;


        if (false == Dir.MoveParentToDirectory("Resources"))
        {
            MSGASSERT("이미지 폴더를 찾지 못했습니다.");
            return;
        }
        Dir.Append("Images");

        std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();

        for (size_t i = 0; i < ImageFiles.size(); i++)
        {
            std::string FilePath = ImageFiles[i].GetPathToString();
            UImageManager::GetInst().Load(FilePath);
        }
        // ------------------------------- [ Tile ] -------------------------------------------
        // dirt
        {
            UEngineDirectory Dir;
            Dir.MoveParentToDirectory("Resources//Images");
            Dir.Append("TileMap//DirtTile");
            UImageManager::GetInst().CuttingSprite("Dirt.png", { 48, 48 });
            UImageManager::GetInst().CuttingSprite("WetDirt.png", { 48, 48 });

        }
        // tree
        {
            UEngineDirectory Dir;
            Dir.MoveParentToDirectory("Resources//Images");
            Dir.Append("TileMap//TreeTile");
            UImageManager::GetInst().CuttingSprite("Tree001.png", { 144, 276 });
            UImageManager::GetInst().CuttingSprite("Tree002.png", { 16, 20 });
        }
        // house
        {
            UEngineDirectory Dir;
            Dir.MoveParentToDirectory("Resources//Images");
            Dir.Append("TileMap//HouseTile");
            UImageManager::GetInst().LoadFolder(Dir.GetPathToString());
        }
        // Box
        {
            UEngineDirectory Dir;
            Dir.MoveParentToDirectory("Resources//Images");
            Dir.Append("TileMap//BoxTile");
            UImageManager::GetInst().LoadFolder(Dir.GetPathToString());
        }
        // crops
        {
            UEngineDirectory Dir;
            Dir.MoveParentToDirectory("Resources//Images");
            Dir.Append("TileMap//CropsTile");
            UImageManager::GetInst().CuttingSprite("parsnip.png", { 15, 16 });
            UImageManager::GetInst().CuttingSprite("GreenBean.png", { 13, 26 });
            UImageManager::GetInst().CuttingSprite("Cauliflower.png", { 16, 15 });
            UImageManager::GetInst().CuttingSprite("Potato.png", { 16,  18 });
            UImageManager::GetInst().CuttingSprite("Kale.png", { 16,  20 });
            UImageManager::GetInst().CuttingSprite("Rhubarb.png", { 16,  19 });
            UImageManager::GetInst().CuttingSprite("Garlic.png", { 16,  18 });

        }
        {
            UEngineDirectory Dir;
            Dir.MoveParentToDirectory("Resources//Images");
            Dir.Append("TileMap//StoreTile");
            UImageManager::GetInst().CuttingSprite("Counter.png", { 388, 200 });
      
        }
        // ------------------------------- [ UI ] -------------------------------------------
        // Clock & Cursor & InventotyBar
        {
            UEngineDirectory Dir;
            Dir.MoveParentToDirectory("Resources//Images");
            Dir.Append("UI");
            UImageManager::GetInst().LoadFolder(Dir.GetPathToString());
            UImageManager::GetInst().CuttingSprite("Clock.png", { 72, 59 });
            UImageManager::GetInst().CuttingSprite("Cursor.png", { 24, 30 });
            UImageManager::GetInst().CuttingSprite("Inventory.png", { 214, 74 });
            UImageManager::GetInst().CuttingSprite("Inventory2.png", { 216, 159 });
            UImageManager::GetInst().CuttingSprite("InventoryBar.png", { 203, 26 });
            UImageManager::GetInst().CuttingSprite("Logo.png", { 796, 374 });
            UImageManager::GetInst().CuttingSprite("SelectedSlot.png", { 16, 16 });
            UImageManager::GetInst().CuttingSprite("Slot.png", { 16, 16 });
            UImageManager::GetInst().CuttingSprite("TextBox.png", { 100, 35 });
            UImageManager::GetInst().CuttingSprite("TextBox_Top.png", { 100, 6 });
            UImageManager::GetInst().CuttingSprite("TextBox_Mid.png", { 100, 7 });
            UImageManager::GetInst().CuttingSprite("TextBox_Bot.png", { 100, 7 });
            UImageManager::GetInst().CuttingSprite("StoreBox.png", { 300, 170 });
            UImageManager::GetInst().CuttingSprite("ExitButton.png", { 12, 12 });
            UImageManager::GetInst().CuttingSprite("CurStoreColumn.png", { 294, 28 });
            UImageManager::GetInst().CuttingSprite("Up.png", { 11, 12 });
            UImageManager::GetInst().CuttingSprite("Down.png", { 11, 12 });
            UImageManager::GetInst().CuttingSprite("BedTextBox.png", { 1280, 300 });
            UImageManager::GetInst().CuttingSprite("YesSelected.png", { 1194, 67 });
            UImageManager::GetInst().CuttingSprite("YesUnSelected.png", { 1194, 67 });
            UImageManager::GetInst().CuttingSprite("NoSelected.png", { 1194, 67 });
            UImageManager::GetInst().CuttingSprite("NoUnSelected.png", { 1194, 67 });
            UImageManager::GetInst().CuttingSprite("GoldTextBox.png", { 546, 105 });
            UImageManager::GetInst().CuttingSprite("OKButton.png", { 64, 64 });


        }
        {
            UEngineDirectory Dir;
            Dir.MoveParentToDirectory("Resources//Images");
            Dir.Append("UI//LogoAnimation");
            UImageManager::GetInst().LoadFolder(Dir.GetPathToString());

        }
        {
            UEngineDirectory Dir;
            Dir.MoveParentToDirectory("Resources//Images");
            Dir.Append("UI//ClockHand");
            UImageManager::GetInst().LoadFolder(Dir.GetPathToString());

        }
        {
            UEngineDirectory Dir;
            Dir.MoveParentToDirectory("Resources//Images");
            Dir.Append("UI//Title");
            UImageManager::GetInst().CuttingSprite("Tree.png", { 1280, 383 });
            UImageManager::GetInst().CuttingSprite("Mountain1.png", { 1280, 296 });
            UImageManager::GetInst().CuttingSprite("Mountain2.png", { 1280, 296 });
            UImageManager::GetInst().CuttingSprite("NewButton.png", { 148, 116 });
            UImageManager::GetInst().CuttingSprite("NewButtonHover.png", { 148, 116 });
            UImageManager::GetInst().CuttingSprite("Cloud.png", { 512, 136 });

        }
        // Font
        {
            UEngineDirectory Dir;
            Dir.MoveParentToDirectory("Resources//Images");
            Dir.Append("Font");
            UImageManager::GetInst().CuttingSprite("Gold3.png", { 77, 110 });
            UImageManager::GetInst().CuttingSprite("Time.png", { 18, 28 });
            UImageManager::GetInst().CuttingSprite("apm.png", { 27, 30 });
            UImageManager::GetInst().CuttingSprite("Item.png", { 13, 15 });
            UImageManager::GetInst().CuttingSprite("Week.png", { 81, 33 });
            UImageManager::GetInst().CuttingSprite("Alphabet.png", { 33, 39 });
            UImageManager::GetInst().CuttingSprite("AlphabetBold.png", { 8, 16 });

        }
        // ------------------------------- [ Item & Tools ] -------------------------------------------
        {
            UEngineDirectory Dir;
            Dir.MoveParentToDirectory("Resources//Images");
            Dir.Append("Item");
            UImageManager::GetInst().CuttingSprite("Items.png", { 16, 16 });
            UImageManager::GetInst().CuttingSprite("Tools.png", { 16, 32 });
            UImageManager::GetInst().CuttingSprite("Hoe.png", { 16, 16 });
            UImageManager::GetInst().CuttingSprite("Ax.png", { 16, 16 });
            UImageManager::GetInst().CuttingSprite("Axs.png", { 21, 21 });
            UImageManager::GetInst().CuttingSprite("WateringCan.png", { 20, 20 });
        }

        // ------------------------------- [ Player ] -------------------------------------------
        // player
        {
            UEngineDirectory Dir;
            Dir.MoveParentToDirectory("Resources//Images");
            Dir.Append("Player");
            UImageManager::GetInst().CuttingSprite("Farmer_Right.png", { 64, 128 });
            UImageManager::GetInst().CuttingSprite("Farmer_Left.png", { 64, 128 });
            UImageManager::GetInst().CuttingSprite("Farmer_Right_2.png", { 64, 128 });
            UImageManager::GetInst().CuttingSprite("Farmer_Left_2.png", { 64, 128 });

            // player tool animation
            UImageManager::GetInst().CuttingSprite("Farmer_Right_Axe.png", { 64, 128 });
            UImageManager::GetInst().CuttingSprite("Farmer_Left_Axe.png", { 64, 128 });
            UImageManager::GetInst().CuttingSprite("Farmer_Right_Hoe.png", { 64, 128 });
            UImageManager::GetInst().CuttingSprite("Farmer_Left_Hoe.png", { 64, 128 });
            UImageManager::GetInst().CuttingSprite("Farmer_Right_WateringCan.png", { 64, 128 });
            UImageManager::GetInst().CuttingSprite("Farmer_Left_WateringCan.png", { 64, 128 });
        }
    }


    // 사운드 폴더 찾기
    {
        UEngineDirectory Dir;
        if (false == Dir.MoveParentToDirectory("Resources"))
        {
            MSGASSERT("리소스 폴더를 찾지 못했습니다.");
            return;
        }
        Dir.Append("Sounds");
        std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();
        for (size_t i = 0; i < ImageFiles.size(); i++)
        {
            std::string FilePath = ImageFiles[i].GetPathToString();
            UEngineSound::Load(FilePath);
        }
    }

    ULevel::CollisionGroupLink(ECollisionGroup::SLOT, ECollisionGroup::CURSOR);
    ULevel::CollisionGroupLink(ECollisionGroup::CURSOR, ECollisionGroup::SLOT);
    ULevel::CollisionGroupLink(ECollisionGroup::CURSOR, ECollisionGroup::StoreColumn);
    ULevel::CollisionGroupLink(ECollisionGroup::StoreColumn, ECollisionGroup::CURSOR);
    ULevel::CollisionGroupLink(ECollisionGroup::BUTTON, ECollisionGroup::CURSOR);
    ULevel::CollisionGroupLink(ECollisionGroup::UI, ECollisionGroup::CURSOR);
    //ULevel::CollisionGroupLink(ECollisionGroup::CURSOR, ECollisionGroup::UI);
}