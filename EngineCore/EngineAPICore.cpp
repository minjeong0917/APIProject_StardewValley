#include "PreCompile.h"
#include "EngineAPICore.h"
#include <EnginePlatform/EngineInput.h>

#include <EnginePlatform/EngineWindow.h>
#include <EngineBase/EngineDelegate.h>
#include <EngineBase/EngineDebug.h>

// static 초기화
UEngineAPICore* UEngineAPICore::MainCore = nullptr;
UContentsCore* UEngineAPICore::UserCore = nullptr;

#include <Windows.h>

UEngineAPICore::UEngineAPICore()
{

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
	MainCore = &Core;

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
	if (nullptr != NextLevel)
	{
		// 레벨들을 왔다갔다 할때가 있기 때문에.
		// 그 순간마다 여러분들이 뭔가를 해주고 싶을수가 있다.

		if (nullptr != CurLevel)
		{
			CurLevel->LevelChangeEnd();
		}

		CurLevel = NextLevel;

		NextLevel->LevelChangeStart();

		NextLevel = nullptr;
		// 델타타임이 지연될수 있으므로 델타타임을 초기화시켜주는것이 좋다.
		DeltaTimer.TimeStart();
	}


	// 현재 시간 측정 후 DeltaTime값 가져오기
	DeltaTimer.TimeCheck();
	float DeltaTime = DeltaTimer.GetDeltaTime();

	// 키체크
	UEngineInput::GetInst().KeyCheck(DeltaTime);

	if (nullptr == CurLevel)
	{
		MSGASSERT("엔진 코어에 현재 레벨이 지정되지 않았습니다");
		return;
	}

	UEngineInput::GetInst().EventCheck(DeltaTime);
	CurLevel->Tick(DeltaTime);
	//  UEngineInput::GetInst().EventCheck(DeltaTime);
	CurLevel->Render(DeltaTime);
	CurLevel->Release(DeltaTime);

}

// 현재 레벨 설정
void UEngineAPICore::OpenLevel(std::string_view _LevelName)
{
	std::string ChangeName = _LevelName.data();

	std::map<std::string, class ULevel*>::iterator FindIter = Levels.find(ChangeName);
	std::map<std::string, class ULevel*>::iterator EndIter = Levels.end();

	if (EndIter == FindIter)
	{
		MSGASSERT(ChangeName + "라는 이름의 레벨은 존재하지 않습니다.");
		return;
	}
	NextLevel = FindIter->second;
}