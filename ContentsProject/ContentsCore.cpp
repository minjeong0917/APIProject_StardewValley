#include "PreCompile.h"
#include "ContentsCore.h"

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
	// 농장 레벨 생성 및 Open
	UEngineAPICore::GetCore()->CreateLevel<AFarmGameMode, APlayer>("Farm");
	UEngineAPICore::GetCore()->OpenLevel("Farm");
}

void ContentsCore::Tick()
{
}