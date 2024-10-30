#pragma once
#include <string>

class UObject
{
public:
	// constrcuter destructer
	UObject();

	// 자식들의 소멸자가 무조건 호출되기 위해 virtual
	virtual ~UObject();

	// delete Function
	UObject(const UObject& _Other) = delete;
	UObject(UObject&& _Other) noexcept = delete;
	UObject& operator=(const UObject& _Other) = delete;
	UObject& operator=(UObject&& _Other) noexcept = delete;

	virtual void SetName(std::string_view _Name)
	{
		Name = _Name.data();
	}

protected:

private:
	std::string Name;

};

