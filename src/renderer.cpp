#include "renderer.h"

static ID3D11Device* g_pd3dDevice                 = nullptr;
static ID3D11DeviceContext* g_pd3dDeviceContext   = nullptr;
static IDXGISwapChain* g_pSwapChain               = nullptr;
static ID3D11RenderTargetView* g_mainRenderTarget = nullptr;

// DX11 setup
void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer = nullptr;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTarget);
    pBackBuffer->Release();
}

void CleanupRenderTarget()
{
    if (g_mainRenderTarget) {
        g_mainRenderTarget->Release();
        g_mainRenderTarget = nullptr;
    }
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) {
        g_pSwapChain->Release();
        g_pSwapChain = nullptr;
    }
    if (g_pd3dDeviceContext) {
        g_pd3dDeviceContext->Release();
        g_pd3dDeviceContext = nullptr;
    }
    if (g_pd3dDevice) {
        g_pd3dDevice->Release();
        g_pd3dDevice = nullptr;
    }
}

[[nodiscard]] bool CreateDeviceD3D(HWND hWnd)
{
    DXGI_SWAP_CHAIN_DESC sd = {
        .BufferDesc   = {.Width = 0, .Height = 0, .Format = DXGI_FORMAT_R8G8B8A8_UNORM},
        .SampleDesc   = {.Count = 1},
        .BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT,
        .BufferCount  = 2,
        .OutputWindow = hWnd,
        .Windowed     = TRUE,
        .SwapEffect   = DXGI_SWAP_EFFECT_DISCARD,
        .Flags        = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH,
    };

    D3D_FEATURE_LEVEL featureLevel;
    constexpr D3D_FEATURE_LEVEL featureLevels[] = {D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0};

    HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr,
                                                D3D_DRIVER_TYPE_HARDWARE,
                                                nullptr,
                                                0,
                                                featureLevels,
                                                2,
                                                D3D11_SDK_VERSION,
                                                &sd,
                                                &g_pSwapChain,
                                                &g_pd3dDevice,
                                                &featureLevel,
                                                &g_pd3dDeviceContext);

    if (res == DXGI_ERROR_UNSUPPORTED)
        res = D3D11CreateDeviceAndSwapChain(nullptr,
                                            D3D_DRIVER_TYPE_WARP,
                                            nullptr,
                                            0,
                                            featureLevels,
                                            2,
                                            D3D11_SDK_VERSION,
                                            &sd,
                                            &g_pSwapChain,
                                            &g_pd3dDevice,
                                            &featureLevel,
                                            &g_pd3dDeviceContext);

    if (res != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

bool InitD3D(HWND hwnd)
{
    if (!CreateDeviceD3D(hwnd)) {
        CleanupDeviceD3D();
        return false;
    }
    return true;
}

void ShutdownD3D() { CleanupDeviceD3D(); }

void BeginFrame(float r, float g, float b)
{
    const float clear_color[4] = {r, g, b, 1.0f};
    g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTarget, nullptr);
    g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTarget, clear_color);
}

void EndFrame()
{
    g_pSwapChain->Present(1, 0); // 1 = vsync on
}

void OnWindowResize(UINT width, UINT height)
{
    CleanupRenderTarget();
    g_pSwapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);
    CreateRenderTarget();
}

ID3D11Device* GetDevice() { return g_pd3dDevice; }
ID3D11DeviceContext* GetContext() { return g_pd3dDeviceContext; }
ID3D11RenderTargetView** GetRenderTarget() { return &g_mainRenderTarget; }
