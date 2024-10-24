#include "PreCompile.h"
#include "EngineAPICore.h"

#include <EnginePlatform/EngineWindow.h>
#include <EngineBase/EngineDelegate.h>


// static �ʱ�ȭ
UEngineAPICore* UEngineAPICore::MainCore = nullptr;
UContentsCore* UEngineAPICore::UserCore = nullptr;

UEngineAPICore::UEngineAPICore()
{
	MainCore = this;
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

}

void UEngineAPICore::Render()
{

}