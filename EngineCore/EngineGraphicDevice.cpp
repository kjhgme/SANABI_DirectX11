#include "PreCompile.h"
#include "EngineGraphicDevice.h"

#include "EngineTexture.h"
#include "EngineDepthStencilState.h"

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
    DXBackBufferTexture = nullptr;
    SwapChain = nullptr;
    Context = nullptr;
    Device = nullptr;
    RTV = nullptr;
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
        MSGASSERT("���̷�Ʈ 11������ �������� �ʴ� �׷���ī�� �Դϴ�.");
        return;
    }

    if (FAILED(Result))
    {
        MSGASSERT("Failed to create Direct2D render target.");
        return;
    }

    Result = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
   
    // Direct2D ���丮 ����
    Result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, d2dFactory.ReleaseAndGetAddressOf());
    // if (FAILED(hr)) return hr;

    // DirectWrite ���丮 ����
    Result = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)dwriteFactory.ReleaseAndGetAddressOf());
    // if (FAILED(hr)) return hr;


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

    D3D11_TEXTURE2D_DESC Desc = { 0 };
    Desc.ArraySize = 1;
    Desc.Width = Size.iX();
    Desc.Height = Size.iY();
    Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

    Desc.SampleDesc.Count = 1;
    Desc.SampleDesc.Quality = 0;

    Desc.MipLevels = 1;
    Desc.Usage = D3D11_USAGE_DEFAULT;
    Desc.CPUAccessFlags = 0;
    Desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;

    DepthTex = std::make_shared<UEngineTexture>();

    DepthTex->ResCreate(Desc);

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
        MSGASSERT("����ü�� ���ۿ� �����߽��ϴ�.");
    }

    if (S_OK != SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &DXBackBufferTexture))
    {
        MSGASSERT("����� �ؽ�ó�� �����µ� �����߽��ϴ�.");
    };

    if (S_OK != Device->CreateRenderTargetView(DXBackBufferTexture.Get(), nullptr, &RTV))
    {
        MSGASSERT("�ؽ�ó �������� ȹ�濡 �����߽��ϴ�");
    }

    CreateD2DRenderTarget();
}

void UEngineGraphicDevice::RenderStart()
{
    FVector ClearColor;

    ClearColor = FVector(0.0f, 0.0f, 1.0f, 1.0f);

    Context->ClearRenderTargetView(RTV.Get(), ClearColor.Arr1D);
    Context->ClearDepthStencilView(DepthTex->GetDSV(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    
    ID3D11RenderTargetView* RTV = UEngineCore::GetDevice().GetRTV();
    ID3D11RenderTargetView* ArrRtv[16] = { 0 };
    ArrRtv[0] = RTV; // SV_Target0
    Context->OMSetRenderTargets(1, &ArrRtv[0], DepthTex->GetDSV());
}

void UEngineGraphicDevice::RenderEnd()
{
    HRESULT Result = SwapChain->Present(0, 0);

    if (Result == DXGI_ERROR_DEVICE_REMOVED || Result == DXGI_ERROR_DEVICE_RESET)
    {
        MSGASSERT("�ػ� �����̳� ����̽� ���� ������ ��Ÿ�� ���� �����Ǿ����ϴ�");
        return;
    }
}

ENGINEAPI HRESULT UEngineGraphicDevice::CreateD2DRenderTarget()
{ 
    // SwapChain�� �ùٸ��� �ʱ�ȭ�Ǿ����� Ȯ��
    if (!SwapChain) {
        MSGASSERT("SwapChain is not initialized.");
        return E_FAIL;  // �Ǵ� ������ ���� �ڵ� ��ȯ
    }

    Microsoft::WRL::ComPtr<IDXGISurface> dxgiSurface;
    HRESULT hr = SwapChain->GetBuffer(0, __uuidof(IDXGISurface), (void**)dxgiSurface.ReleaseAndGetAddressOf());
    if (FAILED(hr)) return hr;

    // Direct2D ���� Ÿ�� �Ӽ� ����
    D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
        D2D1_RENDER_TARGET_TYPE_DEFAULT,
        D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)
    );

    // ���� Ÿ�� ����
    hr = d2dFactory->CreateDxgiSurfaceRenderTarget(dxgiSurface.Get(), &props, d2dRenderTarget.ReleaseAndGetAddressOf());
    return hr;
}

void UEngineGraphicDevice::RenderText(std::string_view text, float x, float y, float _FontSize) {
    // ��Ƽ����Ʈ ���ڿ� -> �����ڵ� ��ȯ
    int wlen = MultiByteToWideChar(CP_ACP, 0, text.data(), -1, nullptr, 0);
    std::wstring wText(wlen, L'\0');
    MultiByteToWideChar(CP_ACP, 0, text.data(), -1, &wText[0], wlen);

    d2dRenderTarget->BeginDraw();

    // ���� �ʱ�ȭ
    d2dRenderTarget->Clear(D2D1::ColorF(1.0f, 0.0f, 0.0f, 0.0f));

    // �ؽ�Ʈ ���
    D2D1_RECT_F layoutRect = D2D1::RectF(x, y, x + 500, y + 100);
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> textBrush;
    HRESULT hr = d2dRenderTarget->CreateSolidColorBrush(
        D2D1::ColorF(D2D1::ColorF::White), textBrush.ReleaseAndGetAddressOf()
    );

    if (FAILED(hr)) {
        MessageBoxA(nullptr, "Failed to create text brush.", "Error", MB_OK);
        return;
    }
    // �ؽ�Ʈ ���� ����
    hr = dwriteFactory->CreateTextFormat(
        L"PFStardust", nullptr,
        DWRITE_FONT_WEIGHT_REGULAR,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        _FontSize, L"ko", textFormat.ReleaseAndGetAddressOf()
    );
    if (FAILED(hr)) {
        std::wcerr << L"��Ʈ ���� ����: HRESULT = " << hr << std::endl;
    }
    else {
        std::wcout << L"��Ʈ ���� ����: PFStardust" << std::endl;
    }

    // �����ڵ� ���ڿ� ���
    d2dRenderTarget->DrawText(
        wText.c_str(),                     // �����ڵ� ���ڿ�
        static_cast<UINT32>(wText.length()), // ���ڿ� ����
        textFormat.Get(),                  // �ؽ�Ʈ ����
        &layoutRect,                       // �ؽ�Ʈ ���̾ƿ� ����
        textBrush.Get()                    // �귯��
    );

    // ���� Ÿ�� ������
    hr = d2dRenderTarget->EndDraw();
    if (FAILED(hr)) {
        MessageBoxA(nullptr, "Failed to draw text.", "Error", MB_OK);
        return;
    }

    // ���� ü�� ������Ʈ
    SwapChain->Present(1, 0);
}