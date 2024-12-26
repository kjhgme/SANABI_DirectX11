#include "PreCompile.h"
#include "EngineTexture.h"

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex_Debug.lib")
#else
#pragma comment(lib, "DirectXTex_Release.lib")
#endif

UEngineTexture::UEngineTexture()
{
}

UEngineTexture::~UEngineTexture()
{
}

std::shared_ptr<UEngineTexture> UEngineTexture::Load(std::string_view _Name, std::string_view _Path)
{
	std::string UpperName = ToUpperName(_Name);

	if (true == Contains(UpperName))
	{
		MSGASSERT(UpperName + "is already loaded.");
		return nullptr;
	}

	std::shared_ptr<UEngineTexture> NewRes = std::make_shared<UEngineTexture>();
	PushRes<UEngineTexture>(NewRes, _Name, _Path);
	NewRes->ResLoad();

	return NewRes;
}

void UEngineTexture::ResLoad()
{
	UEngineFile File = Path;

	std::string Str = File.GetPathToString();
	std::string Ext = File.GetExtension();
	std::wstring wLoadPath = UEngineString::AnsiToUnicode(Str.c_str());
	std::string UpperExt = UEngineString::ToUpper(Ext.c_str());

	DirectX::TexMetadata Metadata;
	DirectX::ScratchImage ImageData;

	if (UpperExt == ".DDS")
	{
		if (S_OK != DirectX::LoadFromDDSFile(wLoadPath.c_str(), DirectX::DDS_FLAGS_NONE, &Metadata, ImageData))
		{
			MSGASSERT("Load DDS failed.");
			return;
		}
	}
	else if (UpperExt == ".TGA")
	{
		if (S_OK != DirectX::LoadFromTGAFile(wLoadPath.c_str(), DirectX::TGA_FLAGS_NONE, &Metadata, ImageData))
		{
			MSGASSERT("Load TGA failed.");
			return;
		}
	}
	else
	{
		if (S_OK != DirectX::LoadFromWICFile(wLoadPath.c_str(), DirectX::WIC_FLAGS_NONE, &Metadata, ImageData))
		{
			MSGASSERT(UpperExt + " load failed.");
			return;
		}
	}

	if (S_OK != DirectX::CreateShaderResourceView(
		UEngineCore::Device.GetDevice(),
		ImageData.GetImages(),
		ImageData.GetImageCount(),
		ImageData.GetMetadata(),
		SRV.GetAddressOf()
	))
	{
		MSGASSERT(UpperExt + " CreateShader failed.");
		return;
	}
}