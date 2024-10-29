#include "PreCompile.h"
#include "ContentsCore.h"

#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineDebug.h>
#include <EngineCore/EngineAPICore.h>
#include "FarmGameMode.h"
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

	// Images ���� ã��
	if (false == Dir.MoveParentToDirectory("Images"))
	{
		MSGASSERT("�̹��� ������ ã�� ���߽��ϴ�.");
		return;
	}

	std::vector<UEngineFile> ImageFiles = Dir.GetAllFile();

	for (size_t i = 0; i < ImageFiles.size(); i++)
	{
		std::string FilePath = ImageFiles[i].GetPathToString();
	}

	// ������ Ÿ��Ʋ ����
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("StardewValley");
	// ������ ũ��� ��ġ ����
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, { 1280, 720 });
	// ���� ���� ���� �� Open
	UEngineAPICore::GetCore()->CreateLevel<AFarmGameMode, APlayer>("Farm");
	UEngineAPICore::GetCore()->OpenLevel("Farm");
}

void ContentsCore::Tick()
{
}