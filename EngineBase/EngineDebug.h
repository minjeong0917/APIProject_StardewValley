#pragma once
#include <Windows.h>
#include <assert.h>

// VALUE를 std::string으로 다 바꾸고 넣기 
#define MSGASSERT(VALUE) std::string ErrorText = VALUE; MessageBoxA(nullptr, ErrorText.c_str(), "치명적 에러", MB_OK); assert(false);
