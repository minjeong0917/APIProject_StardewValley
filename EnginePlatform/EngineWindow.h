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

	// ������ ����
	static void EngineWindowInit(HINSTANCE _Instance);

	// ������ Ŭ���� ����
	static void CreateWindowClass(const WNDCLASSEXA& _Class);

	// ������ �޼��� ����
	static int WindowMessageLoop(EngineDelegate _StartFunction, EngineDelegate _FrameFunction);

	// constrcuter destructer
	UEngineWindow();
	~UEngineWindow();

	// delete Function
	UEngineWindow(const UEngineWindow& _Other) = delete;
	UEngineWindow(UEngineWindow&& _Other) noexcept = delete;
	UEngineWindow& operator=(const UEngineWindow& _Other) = delete;
	UEngineWindow& operator=(UEngineWindow&& _Other) noexcept = delete;

	// ������ ����
	void Create(std::string_view _TitleName, std::string_view _ClassName = "Default");

	// ������ ����
	void Open(std::string_view _TitleName = "Window");

protected:

private:
	static HINSTANCE hInstance;

	// ������ â ������ ���� ���, Map���� ����
	static std::map<std::string, WNDCLASSEXA> WindowClasses;

	HWND WindowHandle = nullptr;

};

