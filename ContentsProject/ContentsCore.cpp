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
	// ���� ���� ���� �� Open
	UEngineAPICore::GetCore()->CreateLevel<AFarmGameMode, APlayer>("Farm");
	UEngineAPICore::GetCore()->OpenLevel("Farm");
}

void ContentsCore::Tick()
{
}