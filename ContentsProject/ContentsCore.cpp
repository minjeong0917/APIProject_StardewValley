#include "PreCompile.h"
#include "ContentsCore.h"

#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineDebug.h>

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
	UEngineDirectory Dir;

	// Images 폴더 찾기
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

	// ------------------------------- [ UI ] -------------------------------------------
	// Clock & Cursor
	{
		UEngineDirectory Dir;
		Dir.MoveParentToDirectory("Resources//Images");
		Dir.Append("UI");
		UImageManager::GetInst().LoadFolder(Dir.GetPathToString());
	}
	// Money Font
	{
		UEngineDirectory Dir;
		Dir.MoveParentToDirectory("Resources//Images");
		Dir.Append("Font");
		UImageManager::GetInst().CuttingSprite("Gold3.png", { 77, 110 });

	}


	// ------------------------------- [ Player ] -------------------------------------------
	// player
	{
		UImageManager::GetInst().CuttingSprite("Farmer_Right.png", { 64, 128 });
		UImageManager::GetInst().CuttingSprite("Farmer_Left.png", { 64, 128 });
	}
}