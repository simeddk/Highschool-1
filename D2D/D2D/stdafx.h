#pragma once

//Common Header
#include <Windows.h>
#include <assert.h>

//STL
#include <vector>
#include <string>
#include <bitset>
#include <algorithm>
#include <functional>
using namespace std;

//DirectX SDK
#include <d3d11.h>
#include <D3DX11.h>
#include <D3DX10.h>
#include <D3DX10math.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

//Effect
#include <d3dx11effect.h>
#include <d3dcompiler.h>
#pragma comment(lib, "Effects11d.lib")
#pragma comment(lib, "d3dcompiler.lib")

//ImGui
#include <imgui.h>
#include <imguiDx11.h>
#pragma comment(lib, "ImGui.lib")

//Macro
#define SafeRelease(p) { if(p) { (p)->Release(); (p) = nullptr; } }
#define SafeDelete(p) { if(p) { delete (p); (p) = nullptr; } }
#define SafeDeleteArray(p) { if(p) { delete[] (p); (p) = nullptr; } }
#define Check(hr) { assert(SUCCEEDED(hr)); }

//Typedef
typedef D3DXVECTOR3 Vector3;
typedef D3DXVECTOR2 Vector2;
typedef D3DXCOLOR Color;
typedef D3DXMATRIX Matrix;

//Framework
#include "Systems/Keyboard.h"
#include "Utilities/String.h"
#include "Utilities/Path.h"
#include "Renders/Shader.h"

//Glbal Variable
const UINT Width = 1024;
const UINT Height = 768;

extern HWND Hwnd;
extern wstring Title;

//DirectX ComInterface
extern IDXGISwapChain* SwapChain;
extern ID3D11Device* Device;
extern ID3D11DeviceContext* DeviceContext;
extern ID3D11RenderTargetView* RTV;

extern Keyboard* Key;