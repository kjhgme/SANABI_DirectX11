#include "PreCompile.h"
#include "EngineGraphicDevice.h"

#include "EngineTexture.h"
#include "EngineDepthStencilState.h"
#include "EngineRenderTarget.h"

UEngineGraphicDevice::UEngineGraphicDevice()
{
}

UEngineGraphicDevice::~UEngineGraphicDevice()
{
    Release();
}

void UEngineGraphicDevice::Release()
{
    MainAdapter = nullptr;
    SwapChain = nullptr;
    Context = nullptr;
    Device = nullptr;
}

IDXGIAdapter* UEngineGraphicDevice::GetHighPerformanceAdapter()
{
    unsigned __int64 MaxVideoMemory = 0;

    IDXGIFactory* Factory = nullptr;
    IDXGIAdapter* ResultAdapter = nullptr;

    HRESULT HR = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&Factory));

    if (nullptr == Factory)
    {
        MSGASSERT("Factory is nullptr.");
        return nullptr;
    }

    for (int Index = 0;; ++Index)
    {
        IDXGIAdapter* CurAdapter = nullptr;

        Factory->EnumAdapters(Index, &CurAdapter);

        if (nullptr == CurAdapter)
        {
            break;
        }

        DXGI_ADAPTER_DESC Desc;
        CurAdapter->GetDesc(&Desc);

        if (MaxVideoMemory <= Desc.DedicatedVideoMemory)
        {
            MaxVideoMemory = Desc.DedicatedVideoMemory;
           
            if (nullptr != ResultAdapter)
            {
                ResultAdapter->Release();
            }
            
            ResultAdapter = CurAdapter;
            continue;
        }

        CurAdapter->Release();
    }

    if (nullptr != Factory)
    {
        Factory->Release();
    }

    if (nullptr == ResultAdapter)
    {
        MSGASSERT("Adapter is nullptr.");
        return nullptr;
    }

    return ResultAdapter;
}

void UEngineGraphicDevice::CreateDeviceAndContext()
{
   
    MainAdapter = GetHighPerformanceAdapter();

    UINT iFlag = 0;

#ifdef _DEBUG
    iFlag = D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_DEBUG;
#endif
    D3D_FEATURE_LEVEL ResultLevel;

    HRESULT Result = D3D11CreateDevice(
        MainAdapter.Get(),
        D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN,
        nullptr,
        iFlag,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &Device,
        &ResultLevel,
        &Context);

    if (nullptr == Device)
    {
        MSGASSERT("Device is nullptr.");
        return;
    }

    if (nullptr == Context)
    {
        MSGASSERT("Context is nullptr.");
        return;
    }
    if (Result != S_OK)
    {
        MSGASSERT("Result is Error.");
        return;
    }

    if (ResultLevel != D3D_FEATURE_LEVEL_11_0
        && ResultLevel != D3D_FEATURE_LEVEL_11_1)
    {
        MSGASSERT("다이렉트 11버전을 지원하지 않는 그래픽카드 입니다.");
        return;
    }

    if (FAILED(Result))
    {
        MSGASSERT("Failed to create Direct2D render target.");
        return;
    }

    Result = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
   
    if (Result != S_OK)
    {
        MSGASSERT("Thread has wrong something.");
        return;
    }

    DefaultResourcesInit();
}

void UEngineGraphicDevice::CreateBackBuffer(const UEngineWindow& _Window)
{
    FVector Size = _Window.GetWindowSize();

    DXGI_SWAP_CHAIN_DESC ScInfo = { 0 };

    ScInfo.BufferCount = 2;
    ScInfo.BufferDesc.Width = Size.iX();
    ScInfo.BufferDesc.Height = Size.iY();
    ScInfo.OutputWindow = _Window.GetWindowHandle();
    ScInfo.Windowed = true;
    ScInfo.BufferDesc.RefreshRate.Denominator = 1;
    ScInfo.BufferDesc.RefreshRate.Numerator = 60;
    ScInfo.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    ScInfo.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    ScInfo.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    ScInfo.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
    ScInfo.SampleDesc.Quality = 0;
    ScInfo.SampleDesc.Count = 1;
    ScInfo.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    ScInfo.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    IDXGIFactory* pF = nullptr;

    MainAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pF));

    pF->CreateSwapChain(Device.Get(), &ScInfo, &SwapChain);
    pF->Release();
    MainAdapter->Release();

    if (nullptr == SwapChain)
    {
        MSGASSERT("SwapChain is nullptr.");
    }

    Microsoft::WRL::ComPtr<ID3D11Texture2D> DXBackBufferTexture = nullptr;
    if (S_OK != SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &DXBackBufferTexture))
    {
        MSGASSERT("GetBuffer failed.");
    };
    
    BackBufferTarget = std::make_shared<UEngineRenderTarget>();
    BackBufferTarget->CreateTarget(DXBackBufferTexture);
    BackBufferTarget->CreateDepth();
}

void UEngineGraphicDevice::RenderStart()
{
    BackBufferTarget->Clear();
    BackBufferTarget->Setting();    
}

void UEngineGraphicDevice::RenderEnd()
{
    HRESULT Result = SwapChain->Present(0, 0);

    if (Result == DXGI_ERROR_DEVICE_REMOVED || Result == DXGI_ERROR_DEVICE_RESET)
    {
        MSGASSERT("해상도 변경이나 디바이스 관련 설정이 런타임 도중 수정되었습니다.");
        return;
    }
}