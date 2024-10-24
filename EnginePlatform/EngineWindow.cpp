#include "PreCompile.h"

#include "EngineWindow.h"
#include <EngineBase/EngineDebug.h>

HINSTANCE UEngineWindow::hInstance = nullptr;
std::map<std::string, WNDCLASSEXA> UEngineWindow::WindowClasses;

// WindowCount : WndProc������ ����ؾ��ϹǷ� �ɹ����� ��� ���������� ����
int WindowCount = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
    break;

    // �����ִ� ��� ������ â�� ������ ���α׷� ����
    case WM_DESTROY: 
        --WindowCount; 
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// �⺻ ������ ���� - ������ Ŭ���� �̸� : Default, �������� : ��Ƽ����Ʈ
void UEngineWindow::EngineWindowInit(HINSTANCE _Instance)
{
    hInstance = _Instance;

    WNDCLASSEXA wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "Default";
    wcex.hIconSm = nullptr;

    CreateWindowClass(wcex);
}

// ������ ����
int UEngineWindow::WindowMessageLoop(EngineDelegate _StartFunction, EngineDelegate _FrameFunction)
{
    MSG msg = MSG();

    // ���α׷� �����ϰ� �� �ѹ� �ؾ��ϴ� �Լ�
    _StartFunction();

    while (0 != WindowCount)
    {
        // ���α׷��� focus �ƴϾ ��� ����
        if (0 != PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // ���α׷� �����Ӹ��� ��� �����ؾ��ϴ� �Լ�
        if (true == _FrameFunction.IsBind())
        {
            _FrameFunction();
        }
    }

    return (int)msg.wParam;
}

// ������ Ŭ���� ��� �Լ�
void UEngineWindow::CreateWindowClass(const WNDCLASSEXA& _Class)
{
    std::map<std::string, WNDCLASSEXA>::iterator EndIter = WindowClasses.end();
    std::map<std::string, WNDCLASSEXA>::iterator FindIter = WindowClasses.find(std::string(_Class.lpszClassName));

    // ���� �̸��� ������ Ŭ������ ã�� ��
    if (EndIter != FindIter)
    {
        MSGASSERT(std::string(_Class.lpszClassName) + " ���� �̸��� ������ Ŭ������ 2�� ����߽��ϴ�");
        return;
    }

    RegisterClassExA(&_Class);
    WindowClasses.insert(std::pair{ _Class.lpszClassName, _Class });
}

UEngineWindow::UEngineWindow()
{
}

UEngineWindow::~UEngineWindow()
{
}

// ������ ���� 
void UEngineWindow::Create(std::string_view _TitleName, std::string_view _ClassName)
{
    if (false == WindowClasses.contains(_ClassName.data()))
    {
        MSGASSERT(std::string(_ClassName) + " ������� ���� Ŭ������ ������â�� ������� �߽��ϴ�");
        return;
    }

    WindowHandle = CreateWindowA(_ClassName.data(), _TitleName.data(), WS_OVERLAPPEDWINDOW, 0, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (nullptr == WindowHandle)
    {
        MSGASSERT(std::string(_TitleName) + " ������ ������ �����߽��ϴ�.");
        return;
    }

}


void UEngineWindow::Open(std::string_view _TitleName)
{
    // window �ȸ���� Open ���� �� �⺻������ �⺻ ������ �ϳ� ����
    if (nullptr == WindowHandle)
    {
        Create("Window");
    }

    if (0 == WindowHandle)
    {
        return;
    }

    ShowWindow(WindowHandle, SW_SHOW);
    UpdateWindow(WindowHandle);

    // ���ο� ������â�� Open �ɶ����� Count
    ++WindowCount;
}