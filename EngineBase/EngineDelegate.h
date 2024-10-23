#pragma once
#include <functional>

// ������ �Լ� ���� ȣ���� ���� Ŭ����
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

	// Fuctions�� �Լ� ���� ���� Ȯ��
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

	// Fuctions�� �ִ� �Լ��� clear
	void Clear()
	{
		Functions.clear();
	}

protected:

private:
	std::list<std::function<void()>> Functions;
};

