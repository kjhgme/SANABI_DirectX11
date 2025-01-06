#pragma once
#include <memory>

#include <wrl.h>
#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <d2d1.h>
#include <dwrite.h>
#include <EnginePlatform/EngineWindow.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler") 
#pragma comment(lib, "dxguid")
#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")

#pragma comment(lib, "DXGI") 

class UEngineGraphicDevice
{
public:
	ENGINEAPI UEngineGraphicDevice();
	ENGINEAPI ~UEngineGraphicDevice();

	UEngineGraphicDevice(const UEngineGraphicDevice& _Other) = delete;
	UEngineGraphicDevice(UEngineGraphicDevice&& _Other) noexcept = delete;
	UEngineGraphicDevice& operator=(const UEngineGraphicDevice& _Other) = delete;
	UEngineGraphicDevice& operator=(UEngineGraphicDevice&& _Other) noexcept = delete;

	void CreateDeviceAndContext();

	void CreateBackBuffer(const UEngineWindow& _Window);

	IDXGIAdapter* GetHighPerformanceAdapter();

	ENGINEAPI void Release();

	void RenderStart();

	void RenderEnd();

	ENGINEAPI ID3D11Device* GetDevice()
	{
		return Device.Get();
	}

	ENGINEAPI ID3D11DeviceContext* GetContext()
	{
		return Context.Get();
	}

	ENGINEAPI ID3D11RenderTargetView* GetRTV()
	{
		return RTV.Get();
	}

	ENGINEAPI HRESULT CreateD2DRenderTarget();

	ENGINEAPI void RenderText(std::string_view text, float x, float y, float _FontSize = 24.0f);

protected:

private:
	Microsoft::WRL::ComPtr<ID3D11Device> Device = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> Context = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain> SwapChain = nullptr;
	Microsoft::WRL::ComPtr<IDXGIAdapter> MainAdapter = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> DXBackBufferTexture = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> RTV = nullptr;

	Microsoft::WRL::ComPtr<ID2D1Factory> d2dFactory;
	Microsoft::WRL::ComPtr<ID2D1RenderTarget> d2dRenderTarget;
	Microsoft::WRL::ComPtr<IDWriteFactory> dwriteFactory;
	Microsoft::WRL::ComPtr<IDWriteTextFormat> textFormat;

	std::shared_ptr<class UEngineTexture> DepthTex;

	ENGINEAPI void DefaultResourcesInit();
	ENGINEAPI void MeshInit();
	ENGINEAPI void BlendInit();
	ENGINEAPI void ShaderInit();
	ENGINEAPI void MaterialInit();
	ENGINEAPI void RasterizerStateInit();
	ENGINEAPI void TextureInit();
	ENGINEAPI void DepthStencilInit();
};

