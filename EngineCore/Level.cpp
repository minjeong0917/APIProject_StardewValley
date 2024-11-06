#include "PreCompile.h"
#include "Level.h"
#include "EngineAPICore.h"

#include <EngineBase/EngineMath.h>
#include <EnginePlatform/EngineWindow.h>
#include <EnginePlatform/EngineWinImage.h>

#include "SpriteRenderer.h"

#include "EngineCoreDebug.h"
ULevel::ULevel()
{
}

ULevel::~ULevel()
{
	{
		// BeginPlayList : 한번도 체인지 안한 액터들 제거
		std::list<AActor*>::iterator StartIter = BeginPlayList.begin();
		std::list<AActor*>::iterator EndIter = BeginPlayList.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			AActor* CurActor = *StartIter;
			delete CurActor;
		}
	}

	{
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
}

void ULevel::LevelChangeStart()
{
	{
		std::list<AActor*>::iterator StartIter = AllActors.begin();
		std::list<AActor*>::iterator EndIter = AllActors.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			AActor* CurActor = *StartIter;

			CurActor->LevelChangeStart();
		}
	}
	{
		std::list<AActor*>::iterator StartIter = BeginPlayList.begin();
		std::list<AActor*>::iterator EndIter = BeginPlayList.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			AActor* CurActor = *StartIter;

			CurActor->LevelChangeStart();
		}
	}

}

void ULevel::LevelChangeEnd()
{
	{
		std::list<AActor*>::iterator StartIter = AllActors.begin();
		std::list<AActor*>::iterator EndIter = AllActors.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			AActor* CurActor = *StartIter;

			CurActor->LevelChangeEnd();
		}
	}
	{
		std::list<AActor*>::iterator StartIter = BeginPlayList.begin();
		std::list<AActor*>::iterator EndIter = BeginPlayList.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			AActor* CurActor = *StartIter;
			CurActor->LevelChangeEnd();
		}
	}

}


void ULevel::Tick(float _DeltaTime)
{
	{
		std::list<AActor*>::iterator StartIter = BeginPlayList.begin();
		std::list<AActor*>::iterator EndIter = BeginPlayList.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			AActor* CurActor = *StartIter;
			CurActor->BeginPlay();
			AllActors.push_back(CurActor);
		}

		BeginPlayList.clear();

		// todtjdtl 
		AActor::ComponentBeginPlay();
	}

	{
		std::list<AActor*>::iterator StartIter = AllActors.begin();
		std::list<AActor*>::iterator EndIter = AllActors.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			AActor* CurActor = *StartIter;

			if (false == CurActor->IsActive())
			{
				continue;
			}

			CurActor->Tick(_DeltaTime);
		}
	}
}

void ULevel::Render(float _DeltaTime)
{
	// Render 시작 시 스크린 비우기
	ScreenClear();

	if (true == IsCameraToMainPawn)
	{
		// CameraPivot = FVector2D(-1280, -720) * 0.5f;
		CameraPos = MainPawn->GetTransform().Location + CameraPivot;
	}


	std::map<int, std::list<class USpriteRenderer*>>::iterator StartOrderIter = Renderers.begin();
	std::map<int, std::list<class USpriteRenderer*>>::iterator EndOrderIter = Renderers.end();

	for (; StartOrderIter != EndOrderIter; ++StartOrderIter)
	{
		std::list<class USpriteRenderer*>& RendererList = StartOrderIter->second;

		std::list<class USpriteRenderer*>::iterator RenderStartIter = RendererList.begin();
		std::list<class USpriteRenderer*>::iterator RenderEndIter = RendererList.end();

		for (; RenderStartIter != RenderEndIter; ++RenderStartIter)
		{
			if (false == (*RenderStartIter)->IsActive())
			{
				continue;
			}
			(*RenderStartIter)->Render(_DeltaTime);
		}

	}

	UEngineDebug::PrintEngineDebugText();
	DoubleBuffering();
}

void ULevel::Release(float _DeltaTime)
{
	// 릴리즈 순서는 말단부터 돌려야 합니다.

	std::map<int, std::list<class USpriteRenderer*>>::iterator StartOrderIter = Renderers.begin();
	std::map<int, std::list<class USpriteRenderer*>>::iterator EndOrderIter = Renderers.end();

	for (; StartOrderIter != EndOrderIter; ++StartOrderIter)
	{
		std::list<class USpriteRenderer*>& RendererList = StartOrderIter->second;

		std::list<class USpriteRenderer*>::iterator RenderStartIter = RendererList.begin();
		std::list<class USpriteRenderer*>::iterator RenderEndIter = RendererList.end();

		// 언리얼은 중간에 삭제할수 없어.
		for (; RenderStartIter != RenderEndIter; )
		{
			if (false == (*RenderStartIter)->IsDestroy())
			{
				++RenderStartIter;
				continue;
			}

			// 랜더러는 지울 필요가 없습니다.
			// (*RenderStartIter) 누가 지울 권한을 가졌느냐.
			// 컴포넌트의 메모리를 삭제할수 권한은 오로지 액터만 가지고 있다.
			RenderStartIter = RendererList.erase(RenderStartIter);
		}
	}

	{
		std::list<AActor*>::iterator StartIter = AllActors.begin();
		std::list<AActor*>::iterator EndIter = AllActors.end();

		for (; StartIter != EndIter; )
		{
			AActor* CurActor = *StartIter;


			if (false == CurActor->IsDestroy())
			{
				CurActor->ReleaseCheck(_DeltaTime);
				++StartIter;
				continue;
			}

			// 레벨은 액터의 삭제권한을 가지고 있으니 액터는 진짜 지워 준다.
			delete CurActor;
			StartIter = AllActors.erase(StartIter);
		}
	}
}


// 화면 사이즈의 사각형을 그려 전체가 clear 된 것 처럼 구현
void ULevel::ScreenClear()
{
	UEngineWindow& MainWindow = UEngineAPICore::GetCore()->GetMainWindow();
	UEngineWinImage* BackBufferImage = MainWindow.GetBackBuffer();
	FVector2D Size = MainWindow.GetWindowSize();

	Rectangle(BackBufferImage->GetDC(), -1, -1, Size.iX() + 2, Size.iY() + 2);
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

void ULevel::PushRenderer(class USpriteRenderer* _Renderer)
{
	int Order = _Renderer->GetOrder();

	Renderers[Order].push_back(_Renderer);
}

void ULevel::ChangeRenderOrder(class USpriteRenderer* _Renderer, int _PrevOrder)
{

	Renderers[_PrevOrder].remove(_Renderer);

	Renderers[_Renderer->GetOrder()].push_back(_Renderer);


}