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

std::string UEnginePath::GetFileName()
{
	return Path.filename().string();
}
std::string UEnginePath::GetExtension()
{
	return Path.extension().string();
}

bool UEnginePath::IsExists()
{
	return std::filesystem::exists(Path);
}

bool UEnginePath::IsFile()
{
	return false == IsDirectory();
}

// Path가 디렉토리면 true 반환
bool UEnginePath::IsDirectory()
{
	return std::filesystem::is_directory(Path);
}

void UEnginePath::MoveParent()
{
	Path = Path.parent_path();
}

// Path의 부모디렉토리에서 _Path가 존재하는 디렉토리를 찾으면 해당 경로로 이동
bool UEnginePath::MoveParentToDirectory(std::string_view _Path)
{
	// Path를 직접적으로 변경 시 찾는 파일이 없을 경우에 문제가 있을 수 있으니 임시 DummyPath를 이용
	UEnginePath DummyPath = UEnginePath(Path);

	if (false == DummyPath.IsDirectory())
	{
		MSGASSERT("디렉토리 경로일때만 MoveParentToDirectory 를 호출할수 있습니다");
		return false;
	}

	bool Result = false;

	// 현재 디렉토리 경로 CurPath에 저장
	std::filesystem::path CurPath = DummyPath.Path;
	// 현재 디렉토리의 루트 디렉터리 저장
	std::filesystem::path Root = CurPath.root_path();

	// 현재 디렉토리가 루트 디렉토리가 아니라면
	while (true)
	{
		CurPath = DummyPath.Path;
		if (CurPath == Root)
		{
			break;
		}

		// 현재 경로 + _Path
		CurPath.append(_Path);
		// 이 경로에 존재한다면
		if (true == std::filesystem::exists(CurPath))
		{
			Result = true;
			Path = CurPath;
			break;
		}
		// 아니라면 부모 디렉토리로 이동
		DummyPath.MoveParent();
	}

	return Result;
}



