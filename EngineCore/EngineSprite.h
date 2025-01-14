#pragma once
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineDirectory.h>
#include "EngineTexture.h"
#include "EngineResources.h"
#include "EngineDataStruct.h"

class UEngineSprite : public UEngineResources
{
public:
	UEngineSprite();
	~UEngineSprite();

	UEngineSprite(const UEngineSprite& _Other) = delete;
	UEngineSprite(UEngineSprite&& _Other) noexcept = delete;
	UEngineSprite& operator=(const UEngineSprite& _Other) = delete;
	UEngineSprite& operator=(UEngineSprite&& _Other) noexcept = delete;

	ENGINEAPI static std::shared_ptr<UEngineSprite> CreateSpriteToFolder(std::string_view _Path)
	{
		UEngineDirectory Dir = _Path;

		return CreateSpriteToFolder(Dir.GetDirectoryName(), _Path);
	}

	ENGINEAPI static std::shared_ptr<UEngineSprite> CreateSpriteToFolder(std::string_view _Name, std::string_view _Path);

	ENGINEAPI UEngineTexture* GetTexture(size_t _Index = 0);

	ENGINEAPI ID3D11ShaderResourceView* GetSRV(size_t _Index = 0);

	ENGINEAPI FSpriteData GetSpriteData(size_t _Index)
	{
		if (SpriteData.size() <= _Index)
		{
			MSGASSERT("IndexNum is bigger than Data's size.");
		}

		return SpriteData[_Index];
	}

	ENGINEAPI FVector GetSpriteScaleToReal(size_t _Index);

	ENGINEAPI int GetSpriteTextureCount()
	{
		return static_cast<int>(SpriteTexture.size());
	}

protected:

private:
	std::vector<UEngineTexture*> SpriteTexture;
	std::vector<FSpriteData> SpriteData;

};

