#pragma once
#include <Windows.h>
#include <assert.h>

// ���� VALUE�� std::string���� �� �ٲ㼭 Message ���
#define MSGASSERT(VALUE) std::string ErrorText = VALUE; MessageBoxA(nullptr, ErrorText.c_str(), "ġ���� ����", MB_OK); assert(false);
