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

	void operator=(std::function<void()> _Function)
	{
		Functions.push_back(_Function);
	}

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

