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
    UEngineAPICore::GetCore()->CreateLevel<ATownGameMode, APlayer>("Town");
    UEngineAPICore::GetCore()->OpenLevel("Farm");
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
            UImageManager::GetInst().LoadFolder(Dir.GetPathToString());
        }
        // house
        {
            UEngineDirectory Dir;
            Dir.MoveParentToDirectory("Resources//Images");
            Dir.Append("TileMap//HouseTile");
            UImageManager::GetInst().LoadFolder(Dir.GetPathToString());
        }
        // crops
        {
            UEngineDirectory Dir;
            Dir.MoveParentToDirectory("Resources//Images");
            Dir.Append("TileMap//CropsTile");
            UImageManager::GetInst().CuttingSprite("parsnip.png", { 15, 16 });
            UImageManager::GetInst().CuttingSprite("GreenBean.png", { 13, 26 });

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
            UImageManager::GetInst().CuttingSprite("Logo.png", { 400, 220 });
            UImageManager::GetInst().CuttingSprite("SelectedSlot.png", { 16, 16 });
            UImageManager::GetInst().CuttingSprite("Slot.png", { 16, 16 });
            UImageManager::GetInst().CuttingSprite("TextBox.png", { 100, 35 });
            UImageManager::GetInst().CuttingSprite("TextBox_Top.png", { 100, 6 });
            UImageManager::GetInst().CuttingSprite("TextBox_Mid.png", { 100, 7 });
            UImageManager::GetInst().CuttingSprite("TextBox_Bot.png", { 100, 7 });

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
}