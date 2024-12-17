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

std::string UEnginePath::GetDirectoryName()
{
	if (false == IsDirectory())
	{
		MSGASSERT(Path.string() + " is not directory.");
		return "";
	}

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

bool UEnginePath::IsDirectory()
{
	return std::filesystem::is_directory(Path);
}

void UEnginePath::MoveParent()
{
	Path = Path.parent_path();
}

bool UEnginePath::Move(std::string_view _Path)
{
	Append(_Path);

	if (false == IsExists())
	{
		MSGASSERT("path is not exists.");
		return false;
	}

	return true;
}

void UEnginePath::Append(std::string_view _AppendName)
{
	Path.append(_AppendName);
}

bool UEnginePath::MoveParentToDirectory(std::string_view _Path)
{
	UEnginePath DummyPath = UEnginePath(Path);

	if (false == DummyPath.IsDirectory())
	{
		MSGASSERT("It is not Directory's path.");
		return false;
	}

	bool Result = false;

	std::filesystem::path CurPath = DummyPath.Path;
	std::filesystem::path Root = CurPath.root_path();

	while (true)
	{
		CurPath = DummyPath.Path;

		if (CurPath == Root)
		{
			break;
		}

		CurPath.append(_Path);
		if (true == std::filesystem::exists(CurPath))
		{
			Result = true;
			Path = CurPath;
			break;
		}
		DummyPath.MoveParent();
	}

	return Result;
}



