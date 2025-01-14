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
		UEngineCore::GetDevice().GetDevice(),
		ImageData.GetImages(),
		ImageData.GetImageCount(),
		ImageData.GetMetadata(),
		&SRV
	))
	{
		MSGASSERT(UpperExt + " CreateShader failed.");
		return;
	}

	Size.X = static_cast<float>(Metadata.width);
	Size.Y = static_cast<float>(Metadata.height);
}

void UEngineTexture::Setting(EShaderType _Type, UINT _BindIndex)
{
	ID3D11ShaderResourceView* ArrPtr[1] = { SRV.Get() };

	switch (_Type)
	{
	case EShaderType::VS:
		UEngineCore::GetDevice().GetContext()->VSSetShaderResources(_BindIndex, 1, ArrPtr);
		break;
	case EShaderType::PS:
		UEngineCore::GetDevice().GetContext()->PSSetShaderResources(_BindIndex, 1, ArrPtr);
		break;
	case EShaderType::HS:
	case EShaderType::DS:
	case EShaderType::GS:
	case EShaderType::CS:
	default:
		MSGASSERT("Shader is not exist.");
		break;
	}
}

void UEngineTexture::ResCreate(const D3D11_TEXTURE2D_DESC& _Value)
{
	Desc = _Value;

	UEngineCore::GetDevice().GetDevice()->CreateTexture2D(&Desc, nullptr, &Texture2D);

	if (nullptr == Texture2D)
	{
		MSGASSERT("CreateTexture2D failed.");
		return;
	}

	if (Desc.BindFlags & D3D11_BIND_SHADER_RESOURCE)
	{
		CreateShaderResourceView();
	}

	if (Desc.BindFlags & D3D11_BIND_RENDER_TARGET)
	{
		CreateRenderTargetView();
	}

	if (Desc.BindFlags & D3D11_BIND_DEPTH_STENCIL)
	{
		CreateDepthStencilView();
	}
}

void UEngineTexture::ResCreate(Microsoft::WRL::ComPtr<ID3D11Texture2D> _Texture2D)
{
	Texture2D = _Texture2D;
	Texture2D->GetDesc(&Desc);
	Size.X = static_cast<float>(Desc.Width);
	Size.Y = static_cast<float>(Desc.Height);

	CreateRenderTargetView();
}

void UEngineTexture::CreateRenderTargetView()
{
	if (S_OK != UEngineCore::GetDevice().GetDevice()->CreateRenderTargetView(Texture2D.Get(), nullptr, &RTV))
	{
		MSGASSERT("CreateRenderTargetView failed.");
	}
}

void UEngineTexture::CreateShaderResourceView()
{
	if (S_OK != UEngineCore::GetDevice().GetDevice()->CreateShaderResourceView(Texture2D.Get(), nullptr, &SRV))
	{
		MSGASSERT("CreateShaderResourceView failed.");
		return;
	}
}
void UEngineTexture::CreateDepthStencilView()
{
	if (S_OK != UEngineCore::GetDevice().GetDevice()->CreateDepthStencilView(Texture2D.Get(), nullptr, &DSV))
	{
		MSGASSERT("CreateDepthStencilView failed.");
		return;
	}
}