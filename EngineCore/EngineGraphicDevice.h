#pragma once
#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <EnginePlatform/EngineWindow.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler") 
#pragma comment(lib, "dxguid")

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

	IDXGIAdapter* GetHighPerFormanceAdapter();

	void Release();

	void RenderStart();

	void RenderEnd();

	ENGINEAPI ID3D11Device* GetDevice()
	{
		return Device;
	}

	ENGINEAPI ID3D11DeviceContext* GetContext()
	{
		return Context;
	}

protected:

private:
	ID3D11Device* Device = nullptr;
	ID3D11DeviceContext* Context = nullptr;
	IDXGISwapChain* SwapChain = nullptr;
	IDXGIAdapter* MainAdapter = nullptr;
	ID3D11Texture2D* DXBackBufferTexture = nullptr;
	ID3D11RenderTargetView* RTV = nullptr;
};

