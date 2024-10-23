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

// 프로그램 실행 시 
int UEngineAPICore::EngineStart(HINSTANCE _Inst)
{
	UEngineWindow::EngineWindowInit(_Inst);

	UEngineAPICore Core;
	Core.EngineMainWindow.Open();

	EngineDelegate NewDel;
	NewDel = EngineLoop;

	return UEngineWindow::WindowMessageLoop(NewDel);
}

// 프로그램 실행 동안 반복되는 기능
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