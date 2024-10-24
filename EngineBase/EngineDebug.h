#pragma once
#include <Windows.h>
#include <assert.h>

// 들어온 VALUE를 std::string으로 다 바꿔서 Message 출력
#define MSGASSERT(VALUE) std::string ErrorText = VALUE; MessageBoxA(nullptr, ErrorText.c_str(), "치명적 에러", MB_OK); assert(false);
