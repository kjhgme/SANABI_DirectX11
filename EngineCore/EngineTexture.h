#pragma once
#include "EngineResources.h"

class UEngineTexture : public UEngineResources<UEngineTexture>
{
public:
	ENGINEAPI UEngineTexture();
	ENGINEAPI ~UEngineTexture();

	UEngineTexture(const UEngineTexture& _Other) = delete;
	UEngineTexture(UEngineTexture&& _Other) noexcept = delete;
	UEngineTexture& operator=(const UEngineTexture& _Other) = delete;
	UEngineTexture& operator=(UEngineTexture&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineTexture> Load(std::string_view _Path)
	{
		UEnginePath EnginePath = UEnginePath(_Path);

		std::string FileName = EnginePath.GetFileName();

		return Load(FileName, _Path);
	}

	static std::shared_ptr<UEngineTexture> Load(std::string_view _Name, std::string_view _Path)
	{
		std::string UpperName = ToUpperName(_Name);

		if (true == Contains(UpperName))
		{
			MSGASSERT(UpperName + " is Contained.");
			return nullptr;
		}

		std::shared_ptr<UEngineTexture> NewTexture = MakeRes(_Name, _Path);
		NewTexture->ResLoad();
		return NewTexture;
	}

protected:

private:
	ENGINEAPI void ResLoad();
};
