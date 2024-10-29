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

// ���丮 �� ���� ��� �������� - _IsRecursive == true�� ���� ���� �ȱ��� ��� ��������
std::vector<class UEngineFile> UEngineDirectory::GetAllFile(bool _IsRecursive)
{
	// vector�� ���� ��� ����
	std::vector<class UEngineFile> Result;

	// Path �� ��ο� �ִ� ���丮 ���ͷ����� ����
	std::filesystem::directory_iterator Diriter = std::filesystem::directory_iterator(Path);

	// ���丮�� ���� �����Ҷ�����
	while (false == Diriter._At_end())
	{
		// ���� ���ͷ����Ͱ� ����Ű�� �ִ� ��� ����
		std::filesystem::path FilePath = *Diriter;

		UEnginePath Path = UEnginePath(FilePath);

		// Path �� ��ΰ� ���丮�� �´ٸ�
		if (true == Path.IsDirectory())
		{
			if (true == _IsRecursive)
			{
				GetAllFileRecursive(FilePath, Result);
			}

			++Diriter;
			continue;
		}
		// Result�� ���� ���� ��� ����
		Result.push_back(UEngineFile(FilePath));
		++Diriter;
	}

	return Result;
}


// ���� �� ���� ���� �ȿ� �ִ� ���ϱ��� vector�� ����
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