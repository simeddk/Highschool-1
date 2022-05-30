#include "stdafx.h"
#include "Device.h"

int APIENTRY WinMain
(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd
)
{
    InitWindow(hInstance, nShowCmd);
    InitDirect3D(hInstance);

    Running();
    Destroy();

    DestroyWindow(Hwnd);
    UnregisterClass(Title.c_str(), hInstance);

	return 0;
}

UINT Width = 800;
UINT Height = 600;

HWND Hwnd = nullptr;
wstring Title = L"D2D";

IDXGISwapChain* SwapChain = nullptr;
ID3D11Device* Device = nullptr;
ID3D11DeviceContext* DeviceContext = nullptr;
ID3D11RenderTargetView* RTV = nullptr;

Keyboard* Key = nullptr;
CMouse* Mouse = nullptr;

void InitWindow(HINSTANCE hInstance, int nCmdShow)
{
    //Register Window Class
    {
        WNDCLASSEX wc;
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = WndProc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = hInstance;
        wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)WHITE_BRUSH;
        wc.lpszMenuName = nullptr;
        wc.lpszClassName = Title.c_str();
        wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

        WORD check = RegisterClassEx(&wc);
        assert(check != NULL);
    }

    //Create Hwnd and Show Window
    {
        Hwnd = CreateWindowEx
        (
            NULL,
            Title.c_str(),
            Title.c_str(),
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            Width,
            Height,
            nullptr,
            nullptr,
            hInstance,
            nullptr
        );
        assert(Hwnd != nullptr);
    }

    RECT rect = { 0, 0, (LONG)Width, (LONG)Height };
    UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - (UINT)Width) / 2;
    UINT centerY = (GetSystemMetrics(SM_CYSCREEN) - (UINT)Height) / 2;
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
    MoveWindow
    (
        Hwnd,
        centerX,
        centerY,
        rect.right - rect.left,
        rect.bottom - rect.top,
        TRUE
    );

    ShowWindow(Hwnd, nCmdShow);
    UpdateWindow(Hwnd);
}

void InitDirect3D(HINSTANCE hInstance)
{
    //SwpaChain->GI
    DXGI_MODE_DESC giDesc;
    ZeroMemory(&giDesc, sizeof(DXGI_MODE_DESC));
    giDesc.Width = Width;
    giDesc.Height = Height;
    giDesc.RefreshRate.Numerator = 60;
    giDesc.RefreshRate.Denominator = 1;
    giDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    giDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    giDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    //SwapChain
    DXGI_SWAP_CHAIN_DESC swapDesc;
    ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
    swapDesc.BufferDesc = giDesc;
    swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapDesc.BufferCount = 1;
    swapDesc.SampleDesc.Count = 1;
    swapDesc.SampleDesc.Quality = 0;
    swapDesc.OutputWindow = Hwnd;
    swapDesc.Windowed = TRUE;
    swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    //FeatureLevel
    vector<D3D_FEATURE_LEVEL> featureLevel =
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1,
    };

    //Create SwapChain
    HRESULT hr = D3D11CreateDeviceAndSwapChain
    (   
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        D3D11_CREATE_DEVICE_BGRA_SUPPORT,
        featureLevel.data(),
        featureLevel.size(),
        D3D11_SDK_VERSION,
        &swapDesc,
        &SwapChain,
        &Device,
        nullptr,
        &DeviceContext
    );
    assert(SUCCEEDED(hr));

    CreateBackBuffer();
}

void Destroy()
{
    SafeRelease(RTV);
    SafeRelease(SwapChain);
    SafeRelease(DeviceContext);
    SafeRelease(Device);
}

WPARAM Running()
{
    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));

    Gui::Create();

    DirectWrite::Create();

    Time::Create();
    Time::Get()->Start();

    Context::Create();

    Key = new Keyboard();
    Mouse = new CMouse();

    InitScene();
    /////////////////////////////
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            Time::Get()->Update();
            Gui::Get()->Update();

            Context::Get()->Update();
            Mouse->Update();

            Update();

            D3DXCOLOR bgcolor = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);
            DeviceContext->ClearRenderTargetView(RTV, (float*)bgcolor);
            {
                Render();
            }

            DirectWrite::GetDC()->BeginDraw();
            {
                PostRender();
            }
            DirectWrite::GetDC()->EndDraw();

            Gui::Get()->Render();
            SwapChain->Present(0, 0);
        }
    }
    /////////////////////////////
    DestroyScene();

    SafeDelete(Mouse);
    SafeDelete(Key);
    Context::Delete();
    Gui::Delete();
    Time::Delete();
    DirectWrite::Delete();

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (Gui::Get()->MsgProc(hwnd, msg, wParam, lParam))
        return true;

    if (Mouse != nullptr)
        Mouse->WndProc(msg, wParam, lParam);

    switch (msg)
    {
        case WM_SIZE:
        {
            Width = LOWORD(lParam);
            Height = HIWORD(lParam);

            if (Device != nullptr)
            {
                DeleteBackBuffer();
                DirectWrite::DeleteBackBuffer();

                SwapChain->ResizeBuffers(0, Width, Height, DXGI_FORMAT_UNKNOWN, 0);

                DirectWrite::CreateBackBuffer();
                CreateBackBuffer();
            }
           
        }
        break;

        case WM_DESTROY: PostQuitMessage(0); break;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

void CreateBackBuffer()
{
    //BackBuffer
    ID3D11Texture2D* firstFrame;
    HRESULT hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&firstFrame);
    assert(SUCCEEDED(hr));

    //Create RTV
    hr = Device->CreateRenderTargetView(firstFrame, nullptr, &RTV);
    assert(SUCCEEDED(hr));
    firstFrame->Release();

    //OMSet
    DeviceContext->OMSetRenderTargets(1, &RTV, nullptr);

    //Create Viewport
    {
        D3D11_VIEWPORT viewport;
        ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
        viewport.TopLeftX = 0;
        viewport.TopLeftY = 0;
        viewport.Width = (FLOAT)Width;
        viewport.Height = (FLOAT)Height;

        DeviceContext->RSSetViewports(1, &viewport);
    }
}

void DeleteBackBuffer()
{
    SafeRelease(RTV);
}