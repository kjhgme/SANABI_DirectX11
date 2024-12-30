#include "PreCompile.h"
#include "EngineSprite.h"

#include <EngineBase/EngineDebug.h>
#include "EngineTexture.h"

UEngineSprite::UEngineSprite()
{
}

UEngineSprite::~UEngineSprite()
{
}

ENGINEAPI std::shared_ptr<UEngineSprite> UEngineSprite::CreateSpriteToFolder(std::string_view _Name, std::string_view _Path)
{
	UEngineDirectory Dir = _Path;

	std::vector<UEngineFile> Files = Dir.GetAllFile(false, { ".png" });

	if (0 == Files.size())
	{
		MSGASSERT("Wrong Dir.");
	}

	std::shared_ptr<UEngineSprite> NewRes = std::make_shared<UEngineSprite>();
	PushRes<UEngineSprite>(NewRes, _Name, "");

	for (size_t i = 0; i < Files.size(); i++)
	{
		std::string UpperName = UEngineString::ToUpper(Files[i].GetFileName());

		std::shared_ptr<UEngineTexture> Texture = UEngineTexture::Find<UEngineTexture>(UpperName);

		if (nullptr == Texture)
		{
			MSGASSERT(UpperName + " is not loaded.");
			return nullptr;
		}

		NewRes->SpriteTexture.push_back(Texture.get());

		FSpriteData SpriteData;
		SpriteData.CuttingPos = { 0.0f, 0.0f };
		SpriteData.CuttingSize = { 1.0f, 1.0f };
		SpriteData.Pivot = { 0.5f, 0.0f };
		NewRes->SpriteData.push_back(SpriteData);
	}

	return NewRes;
}

ENGINEAPI UEngineTexture* UEngineSprite::GetTexture(size_t _Index)
{
	return SpriteTexture[_Index];
}

ENGINEAPI ID3D11ShaderResourceView* UEngineSprite::GetSRV(size_t _Index)
{
	return SpriteTexture[_Index]->GetSRV();
}

ENGINEAPI FVector UEngineSprite::GetSpriteScaleToReal(size_t _Index)
{
	if (SpriteData.size() <= _Index)
	{
		MSGASSERT("Index bigger than data.");
	}

	FVector Result;

	Result.X = SpriteData[_Index].CuttingSize.X * SpriteTexture[_Index]->GetTextureSize().X;
	Result.Y = SpriteData[_Index].CuttingSize.Y * SpriteTexture[_Index]->GetTextureSize().Y;

	return Result;
}