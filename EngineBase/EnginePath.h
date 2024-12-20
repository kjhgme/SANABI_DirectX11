#pragma once
#include <filesystem>

class UEnginePath
{
public:
	ENGINEAPI UEnginePath();
	ENGINEAPI UEnginePath(std::string_view _Path);
	ENGINEAPI UEnginePath(std::filesystem::path _Path);
	ENGINEAPI virtual ~UEnginePath();

	bool IsExists();
	void MoveParent();

	ENGINEAPI std::string GetPathToString();

	std::string GetFileName();
	std::string GetDirectoryName();
	ENGINEAPI std::string GetExtension();

	ENGINEAPI bool Move(std::string_view _Path);
	ENGINEAPI bool MoveParentToDirectory(std::string_view _Path);

	bool IsDirectory();
	bool IsFile();
	void Append(std::string_view _AppendName);

protected:
	std::filesystem::path Path;

private:
};

