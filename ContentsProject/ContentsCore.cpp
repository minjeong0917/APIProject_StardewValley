#include "PreCompile.h"
#include "ContentsCore.h"

#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineDebug.h>

#include <EngineCore/EngineAPICore.h>
#include <EngineCore/ImageManager.h>

#include "FarmGameMode.h"
#include "TitleGameMode.h"
#include "Player.h"


ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::BeginPlay()
{	
	UEngineDirectory Dir;

	// Images 폴더 찾기
	if (false == Dir.MoveParentToDirectory("Images"))
	{
		MSGASSERT("이미지 폴더를 찾지 못했습니다.");
		return;
	}

	std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();

	for (size_t i = 0; i < ImageFiles.size(); i++)
	{
		std::string FilePath = ImageFiles[i].GetPathToString();
		UImageManager::GetInst().Load(FilePath);
	}

	UImageManager::GetInst().CuttingSprite("Farmer_Right.png", { 64, 128 });

	// 윈도우 타이틀 지정
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("StardewValley");
	// 윈도우 크기와 위치 설정
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, { 1280, 720 });
	// 농장 레벨 생성 및 Open
	UEngineAPICore::GetCore()->CreateLevel<AFarmGameMode, APlayer>("Farm");
	UEngineAPICore::GetCore()->CreateLevel<ATitleGameMode, AActor>("Title");
	UEngineAPICore::GetCore()->OpenLevel("Title");
}

void ContentsCore::Tick()
{
}