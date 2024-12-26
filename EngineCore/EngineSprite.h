#pragma once
#include <EngineBase/EngineMath.h>
#include "EngineTexture.h"
#include "EngineResources.h"

struct FSpriteData
{
	float4 CuttingPos = { 0.0f, 0.0f };
	float4 CuttingSize = { 1.0f, 1.0f };
};

class UEngineSprite : public UEngineResources
{
public:
	UEngineSprite();
	~UEngineSprite();

	UEngineSprite(const UEngineSprite& _Other) = delete;
	UEngineSprite(UEngineSprite&& _Other) noexcept = delete;
	UEngineSprite& operator=(const UEngineSprite& _Other) = delete;
	UEngineSprite& operator=(UEngineSprite&& _Other) noexcept = delete;

	ENGINEAPI static std::shared_ptr<UEngineSprite> CreateSpriteToMeta(std::string_view _Name, std::string_view _DataFileExt);

	ENGINEAPI ID3D11ShaderResourceView* GetSRV();

	ENGINEAPI FSpriteData GetSpriteData(size_t _Index)
	{
		if (SpriteDatas.size() <= _Index)
		{
			MSGASSERT("IndexNum is bigger than Data's size.");
		}

		return SpriteDatas[_Index];
	}

protected:

private:
	UEngineTexture* Texture;
	std::vector<FSpriteData> SpriteDatas;

};

