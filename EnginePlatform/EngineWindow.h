#pragma once
// OS Header
#include <Windows.h>

// std Header
#include <map>
#include <string>
#include <functional>

// user header
#include <EngineBase/EngineDelegate.h>

class UEngineWindow
{
public:

	// 윈도우 세팅
	static void EngineWindowInit(HINSTANCE _Instance);

	// 윈도우 클래스 생성
	static void CreateWindowClass(const WNDCLASSEXA& _Class);

	// 윈도우 메세지 루프
	static int WindowMessageLoop(EngineDelegate _StartFunction, EngineDelegate _FrameFunction);

	// constrcuter destructer
	UEngineWindow();
	~UEngineWindow();

	// delete Function
	UEngineWindow(const UEngineWindow& _Other) = delete;
	UEngineWindow(UEngineWindow&& _Other) noexcept = delete;
	UEngineWindow& operator=(const UEngineWindow& _Other) = delete;
	UEngineWindow& operator=(UEngineWindow&& _Other) noexcept = delete;

	// 윈도우 생성
	void Create(std::string_view _TitleName, std::string_view _ClassName = "Default");

	// 윈도우 열기
	void Open(std::string_view _TitleName = "Window");

protected:

private:
	static HINSTANCE hInstance;

	// 윈도우 창 여러개 만들 경우, Map으로 관리
	static std::map<std::string, WNDCLASSEXA> WindowClasses;

	HWND WindowHandle = nullptr;

};


