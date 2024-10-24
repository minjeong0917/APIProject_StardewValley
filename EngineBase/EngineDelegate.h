#pragma once
#include <functional>

// 여러개 함수 동시 호출을 위한 클래스
class EngineDelegate
{
public:
	// constrcuter destructer
	EngineDelegate();
	EngineDelegate(std::function<void()> _Function)
	{
		Functions.push_back(_Function);
	}

	~EngineDelegate();

	// Fuctions에 함수 존재 여부 확인
	bool IsBind()
	{
		return false == Functions.empty();
	}

	// += 연산자 재정의 : 함수를 리스트 Functions에 추가
	void operator+=(std::function<void()> _Function)
	{
		Functions.push_back(_Function);
	}

	// () 연산자 재정의 : Functions에 있는 함수들 호출
	void operator()()
	{
		std::list<std::function<void()>>::iterator StartIter = Functions.begin();
		std::list<std::function<void()>>::iterator EndIter = Functions.end();

		for (; StartIter != EndIter; ++StartIter)
		{
			std::function<void()>& Function = *StartIter;
			Function();
		}
	}

	// Fuctions에 있는 함수들 clear
	void Clear()
	{
		Functions.clear();
	}

protected:

private:
	std::list<std::function<void()>> Functions;
};

