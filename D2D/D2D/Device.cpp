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

HWND Hwnd = nullptr;
wstring Title = L"D2D";

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

    ShowWindow(Hwnd, nCmdShow);
    UpdateWindow(Hwnd);
}

void InitDirect3D(HINSTANCE hInstance)
{
}

void Destroy()
{
}

WPARAM Running()
{
    MSG msg;
    ZeroMemory(&msg, sizeof(MSG));

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
            Update();
            Render();
        }
    }
    /////////////////////////////
    DestroyScene();

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_DESTROY: PostQuitMessage(0); break;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

//19:00