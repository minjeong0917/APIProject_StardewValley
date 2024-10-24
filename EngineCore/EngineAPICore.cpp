#include "PreCompile.h"
#include "EngineAPICore.h"

#include <EnginePlatform/EngineWindow.h>
#include <EngineBase/EngineDelegate.h>


// static 초기화
UEngineAPICore* UEngineAPICore::MainCore = nullptr;
UContentsCore* UEngineAPICore::UserCore = nullptr;

UEngineAPICore::UEngineAPICore()
{
	MainCore = this;
}

UEngineAPICore::~UEngineAPICore()
{
	// Levels - Leak 제거
	std::map<std::string, class ULevel*>::iterator StartIter = Levels.begin();
	std::map<std::string, class ULevel*>::iterator EndIter = Levels.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			delete StartIter->second;
			StartIter->second = nullptr;
		}
	}

	Levels.clear();
}

// 프로그램 실행 시 
int UEngineAPICore::EngineStart(HINSTANCE _Inst, UContentsCore* _UserCore)
{
	// Leak 체크
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	UserCore = _UserCore;

	// 윈도우 기본 세팅 지정
	UEngineWindow::EngineWindowInit(_Inst);

	// 윈도우 open
	UEngineAPICore Core = UEngineAPICore();
	Core.EngineMainWindow.Open();

	// Delegate에 EngineLoop 함수 추가
	EngineDelegate Start = EngineDelegate(std::bind(EngineBeginPlay));
	EngineDelegate FrameLoop = EngineDelegate(std::bind(EngineTick));;

	// EngineLoop -> 윈도우 메세지 루프
	return UEngineWindow::WindowMessageLoop(Start, FrameLoop);
}

// 프로그램 시작 시 한번 실행시켜줘야 하는 함수들
void UEngineAPICore::EngineBeginPlay()
{
	UserCore->BeginPlay();
}

// 프로그램 실행 동안 반복되는 함수들
void UEngineAPICore::EngineTick()
{
	UserCore->Tick();
	MainCore->Tick();
}

void UEngineAPICore::Tick()
{

}

void UEngineAPICore::Render()
{

}