#include "PreCompile.h"
#include "EngineAPICore.h"

#include <EnginePlatform/EngineWindow.h>
#include <EngineBase/EngineDelegate.h>

UEngineAPICore* UEngineAPICore::MainCore = nullptr;


UEngineAPICore::UEngineAPICore()
{
	MainCore = this;
}

UEngineAPICore::~UEngineAPICore()
{
}

// ���α׷� ���� �� 
int UEngineAPICore::EngineStart(HINSTANCE _Inst)
{
	UEngineWindow::EngineWindowInit(_Inst);

	UEngineAPICore Core;
	Core.EngineMainWindow.Open();

	EngineDelegate NewDel;
	NewDel = EngineLoop;

	return UEngineWindow::WindowMessageLoop(NewDel);
}

// ���α׷� ���� ���� �ݺ��Ǵ� ���
void UEngineAPICore::EngineLoop()
{
	MainCore->Tick();
	MainCore->Render();
}

void UEngineAPICore::Tick()
{

}

void UEngineAPICore::Render()
{

}