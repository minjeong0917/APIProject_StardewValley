#include "PreCompile.h"
#include "Level.h"
#include "EngineAPICore.h"
#include <EngineBase/EngineMath.h>
#include <EnginePlatform/EngineWindow.h>
#include <EnginePlatform/EngineWinImage.h>

ULevel::ULevel()
{
}

ULevel::~ULevel()
{
	// Actor - Leak ����
	std::list<AActor*>::iterator StartIter = AllActors.begin();
	std::list<AActor*>::iterator EndIter = AllActors.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		AActor* CurActor = *StartIter;

		if (nullptr != CurActor)
		{
			delete* StartIter;
		}
	}
}

void ULevel::Tick(float _DetaTime)
{
	std::list<AActor*>::iterator StartIter = AllActors.begin();
	std::list<AActor*>::iterator EndIter = AllActors.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		AActor* CurActor = *StartIter;

		CurActor->Tick(_DetaTime);
	}
}

void ULevel::Render()
{
	// Render ���� �� ��ũ�� ����
	ScreenClear();

	std::list<AActor*>::iterator StartIter = AllActors.begin();
	std::list<AActor*>::iterator EndIter = AllActors.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		AActor* CurActor = *StartIter;

		CurActor->Render();
	}
	DoubleBuffering();
}

// ȭ�� �������� �簢���� �׷� ��ü�� clear �� �� ó�� ����
void ULevel::ScreenClear()
{
	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	UEngineWinImage* BackBufferImage = MainWindow.GetBackBuffer();
	FVector2D Size = MainWindow.GetWindowSize();

	Rectangle(BackBufferImage->GetDC(), 0, 0, Size.iX(), Size.iY());
}


void ULevel::DoubleBuffering()
{
	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();

	UEngineWinImage* WindowImage = MainWindow.GetWindowImage();
	UEngineWinImage* BackBufferImage = MainWindow.GetBackBuffer();

	FTransform Trans;
	Trans.Location = MainWindow.GetWindowSize().Half();
	Trans.Scale = MainWindow.GetWindowSize();

	BackBufferImage->CopyToBit(WindowImage, Trans);

}