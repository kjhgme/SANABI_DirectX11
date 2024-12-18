#include "PreCompile.h"
#include "EngineDirectory.h"

#include "EngineFile.h"
#include "EngineDebug.h"

UEngineDirectory::UEngineDirectory()
	: UEnginePath()
{

}

UEngineDirectory::UEngineDirectory(std::string_view _Path)
	: UEnginePath(_Path)
{

}

UEngineDirectory::UEngineDirectory(std::filesystem::path _Path)
	: UEnginePath(_Path)
{

}


UEngineDirectory::~UEngineDirectory()
{
}


std::vector<class UEngineFile> UEngineDirectory::GetAllFile(bool _IsRecursive)
{
	std::vector<class UEngineFile> Result;

	std::filesystem::directory_iterator DirIter = std::filesystem::directory_iterator(Path);

	while (false == DirIter._At_end())
	{
		std::filesystem::path FilePath = *DirIter;

		UEnginePath Path = UEnginePath(FilePath);
		if (true == Path.IsDirectory())
		{
			if (true == _IsRecursive)
			{
				GetAllFileRecursive(FilePath, Result);
			}

			++DirIter;
			continue;
		}

		Result.push_back(UEngineFile(FilePath));
		++DirIter;
	}
	
	return Result;
}

std::vector<class UEngineDirectory> UEngineDirectory::GetAllDirectory()
{
	std::vector<class UEngineDirectory> Result;

	std::filesystem::directory_iterator DirIter = std::filesystem::directory_iterator(Path);

	while (false == DirIter._At_end())
	{
		std::filesystem::path FilePath = *DirIter;

		UEnginePath Path = UEnginePath(FilePath);
		if (false == Path.IsDirectory())
		{
			++DirIter;
			continue;
		}

		Result.push_back(UEngineDirectory(FilePath));
		++DirIter;
	}

	return Result;
}


void UEngineDirectory::GetAllFileRecursive(std::filesystem::path _Path
	, std::vector<class UEngineFile>& _Result)
{
	std::filesystem::directory_iterator DirIter = std::filesystem::directory_iterator(_Path);

	while (false == DirIter._At_end())
	{
		std::filesystem::path FilePath = *DirIter;

		UEnginePath Path = UEnginePath(FilePath);
		if (true == Path.IsDirectory())
		{
			GetAllFileRecursive(FilePath, _Result);
			++DirIter;
			continue;
		}

		_Result.push_back(UEngineFile(FilePath));
		++DirIter;
	}
}

UEngineFile UEngineDirectory::GetFile(std::string_view _FileName)
{
	UEnginePath FilePath = Path;
	FilePath.Append(_FileName);

	if (false == FilePath.IsExists())
	{
		MSGASSERT("FilePath is not exists.");
	}

	return UEngineFile(FilePath);
}