#include "PreCompile.h"
#include "EngineAPICore.h"
#include <EnginePlatform/EngineInput.h>

#include <EnginePlatform/EngineWindow.h>
#include <EngineBase/EngineDelegate.h>
#include <EngineBase/EngineDebug.h>

// static �ʱ�ȭ
UEngineAPICore* UEngineAPICore::MainCore = nullptr;
UContentsCore* UEngineAPICore::UserCore = nullptr;

#include <Windows.h>

UEngineAPICore::UEngineAPICore()
{

}

UEngineAPICore::~UEngineAPICore()
{
	// Levels - Leak ����
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

// ���α׷� ���� �� 
int UEngineAPICore::EngineStart(HINSTANCE _Inst, UContentsCore* _UserCore)
{
	// Leak üũ
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	UserCore = _UserCore;

	// ������ �⺻ ���� ����
	UEngineWindow::EngineWindowInit(_Inst);

	// ������ open
	UEngineAPICore Core = UEngineAPICore();
	Core.EngineMainWindow.Open();
	MainCore = &Core;

	// Delegate�� EngineLoop �Լ� �߰�
	EngineDelegate Start = EngineDelegate(std::bind(EngineBeginPlay));
	EngineDelegate FrameLoop = EngineDelegate(std::bind(EngineTick));;

	// EngineLoop -> ������ �޼��� ����
	return UEngineWindow::WindowMessageLoop(Start, FrameLoop);
}

// ���α׷� ���� �� �ѹ� ���������� �ϴ� �Լ���
void UEngineAPICore::EngineBeginPlay()
{
	UserCore->BeginPlay();
}

// ���α׷� ���� ���� �ݺ��Ǵ� �Լ���
void UEngineAPICore::EngineTick()
{

	UserCore->Tick();

	MainCore->Tick();

}

void UEngineAPICore::Tick()
{
	if (nullptr != NextLevel)
	{
		// �������� �Դٰ��� �Ҷ��� �ֱ� ������.
		// �� �������� �����е��� ������ ���ְ� �������� �ִ�.

		if (nullptr != CurLevel)
		{
			CurLevel->LevelChangeEnd();
		}

		CurLevel = NextLevel;

		NextLevel->LevelChangeStart();

		NextLevel = nullptr;
		// ��ŸŸ���� �����ɼ� �����Ƿ� ��ŸŸ���� �ʱ�ȭ�����ִ°��� ����.
		DeltaTimer.TimeStart();
	}


	// ���� �ð� ���� �� DeltaTime�� ��������
	DeltaTimer.TimeCheck();
	float DeltaTime = DeltaTimer.GetDeltaTime();

	// Űüũ
	UEngineInput::GetInst().KeyCheck(DeltaTime);

	if (nullptr == CurLevel)
	{
		MSGASSERT("���� �ھ ���� ������ �������� �ʾҽ��ϴ�");
		return;
	}

	UEngineInput::GetInst().EventCheck(DeltaTime);
	CurLevel->Tick(DeltaTime);
	//  UEngineInput::GetInst().EventCheck(DeltaTime);
	CurLevel->Render(DeltaTime);
	CurLevel->Release(DeltaTime);

}

// ���� ���� ����
void UEngineAPICore::OpenLevel(std::string_view _LevelName)
{
	std::string ChangeName = _LevelName.data();

	std::map<std::string, class ULevel*>::iterator FindIter = Levels.find(ChangeName);
	std::map<std::string, class ULevel*>::iterator EndIter = Levels.end();

	if (EndIter == FindIter)
	{
		MSGASSERT(ChangeName + "��� �̸��� ������ �������� �ʽ��ϴ�.");
		return;
	}
	NextLevel = FindIter->second;
}