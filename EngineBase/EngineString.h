#pragma once
#include <string>

// 문자열에 관련된 static 함수들
class UEngineString
{
public:
	// constrcuter destructer
	~UEngineString();

	// delete Function
	UEngineString(const UEngineString& _Other) = delete;
	UEngineString(UEngineString&& _Other) noexcept = delete;
	UEngineString& operator=(const UEngineString& _Other) = delete;
	UEngineString& operator=(UEngineString&& _Other) noexcept = delete;

	static std::string ToUpper(std::string_view);

	static std::wstring AnsiToUnicode(std::string_view _Name);

private:
	UEngineString();
};

