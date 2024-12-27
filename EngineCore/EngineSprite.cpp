#include "PreCompile.h"
#include "EngineSprite.h"
#include "EngineBase/EngineDebug.h"

UEngineSprite::UEngineSprite()
{
}

UEngineSprite::~UEngineSprite()
{
}

ID3D11ShaderResourceView* UEngineSprite::GetSRV()
{
	return Texture->GetSRV();
}

ENGINEAPI FVector UEngineSprite::GetSpriteScaleToReal(size_t _Index)
{
	if (SpriteData.size() <= _Index)
	{
		MSGASSERT("Index bigger than data.");
	}

	FVector Result;

	Result.X = SpriteData[_Index].CuttingSize.X * Texture->GetTextureSize().X;
	Result.Y = SpriteData[_Index].CuttingSize.Y * Texture->GetTextureSize().Y;

	return Result;
}
