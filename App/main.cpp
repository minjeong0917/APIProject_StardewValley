#include "PreCompile.h"

// user header
#include <EngineCore/EngineAPICore.h>
#include <ContentsProject/ContentsCore.h>

//pragma comment
#pragma comment (lib, "EngineCore.lib")
#pragma comment (lib, "ContentsProject.lib")

// Main에선 Start만 실행
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	ContentsCore User;
	return UEngineAPICore::EngineStart(hInstance, &User);
}