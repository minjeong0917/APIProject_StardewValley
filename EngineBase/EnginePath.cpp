#include "PreCompile.h"
#include "EnginePath.h"
#include "EngineDebug.h"

UEnginePath::UEnginePath()
	: Path(std::filesystem::current_path())
{
}

UEnginePath::UEnginePath(std::string_view _Path)
	: Path(_Path)
{

}

UEnginePath::UEnginePath(std::filesystem::path _Path)
	: Path(_Path)
{

}

UEnginePath::~UEnginePath()
{
}

std::string UEnginePath::GetPathToString()
{
	return Path.string();
}


bool UEnginePath::IsExists()
{
	return std::filesystem::exists(Path);
}

bool UEnginePath::IsFile()
{
	return false == IsDirectory();
}

// Path�� ���丮�� true ��ȯ
bool UEnginePath::IsDirectory()
{
	return std::filesystem::is_directory(Path);
}

void UEnginePath::MoveParent()
{
	Path = Path.parent_path();
}

// Path�� �θ���丮���� _Path�� �����ϴ� ���丮�� ã���� �ش� ��η� �̵�
bool UEnginePath::MoveParentToDirectory(std::string_view _Path)
{
	// Path�� ���������� ���� �� ã�� ������ ���� ��쿡 ������ ���� �� ������ �ӽ� DummyPath�� �̿�
	UEnginePath DummyPath = UEnginePath(Path);

	if (false == DummyPath.IsDirectory())
	{
		MSGASSERT("���丮 ����϶��� MoveParentToDirectory �� ȣ���Ҽ� �ֽ��ϴ�");
		return false;
	}

	bool Result = false;

	// ���� ���丮 ��� CurPath�� ����
	std::filesystem::path CurPath = DummyPath.Path;

	// ���� ���丮�� ��Ʈ ���丮�� �ƴ϶��
	while (CurPath != CurPath.root_path())
	{
		CurPath = DummyPath.Path;

		// ���� ��� + _Path
		CurPath.append(_Path);
		// �� ��ο� �����Ѵٸ�
		if (true == std::filesystem::exists(CurPath))
		{
			Result = true;
			Path = CurPath;
			break;
		}
		// �ƴ϶�� �θ� ���丮�� �̵�
		DummyPath.MoveParent();
	}

	return Result;
}



