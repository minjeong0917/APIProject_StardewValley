#include "PreCompile.h"
#include "EngineDirectory.h"
#include "EngineFile.h"

UEngineDirectory::UEngineDirectory()
	: UEnginePath()
{

}

UEngineDirectory::UEngineDirectory(std::string_view _Path)
	: UEnginePath(_Path)
{

}


UEngineDirectory::~UEngineDirectory()
{
}

// 디렉토리 안 파일 모두 가져오기 - _IsRecursive == true면 하위 폴더 안까지 모두 가져오기
std::vector<class UEngineFile> UEngineDirectory::GetAllFile(bool _IsRecursive)
{
	// vector로 파일 목록 관리
	std::vector<class UEngineFile> Result;

	// Path 이 경로에 있는 디렉토리 이터레이터 설정
	std::filesystem::directory_iterator Diriter = std::filesystem::directory_iterator(Path);

	// 디렉토리의 끝에 도달할때까지
	while (false == Diriter._At_end())
	{
		// 현재 이터레이터가 가리키고 있는 경로 저장
		std::filesystem::path FilePath = *Diriter;

		UEnginePath Path = UEnginePath(FilePath);

		// Path 이 경로가 디렉토리가 맞다면
		if (true == Path.IsDirectory())
		{
			if (true == _IsRecursive)
			{
				GetAllFileRecursive(FilePath, Result);
			}

			++Diriter;
			continue;
		}
		// Result에 현재 파일 경로 저장
		Result.push_back(UEngineFile(FilePath));
		++Diriter;
	}

	return Result;
}


// 폴더 안 하위 폴더 안에 있는 파일까지 vector에 저장
void UEngineDirectory::GetAllFileRecursive(std::filesystem::path _Path, std::vector<class UEngineFile>& _Result)
{
	std::filesystem::directory_iterator Diriter = std::filesystem::directory_iterator(_Path);

	while (false == Diriter._At_end())
	{
		std::filesystem::path FilePath = *Diriter;
		UEnginePath Path = UEnginePath(FilePath);
		if (true == Path.IsDirectory())
		{
			GetAllFileRecursive(FilePath, _Result);
			++Diriter;
			continue;
		}

		_Result.push_back(UEngineFile(FilePath));
		++Diriter;
	}
}