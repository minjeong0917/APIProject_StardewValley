#pragma once
#include <filesystem>

class UEnginePath
{
public:
	// constrcuter destructer
	UEnginePath();
	UEnginePath(std::string_view _Path);
	UEnginePath(std::filesystem::path _Path);
	~UEnginePath();


	bool IsExists();
	void MoveParent();

	std::string GetPathToString();

	// 파일명 + 확장자 포함
	std::string GetFileName();
	std::string GetDirectoryName();

	// 확장자
	std::string GetExtension();

	bool MoveParentToDirectory(std::string_view _Path);

	bool IsDirectory();

	bool IsFile();

	void Append(std::string_view _AppendName);


protected:
	std::filesystem::path Path;

private:
};

