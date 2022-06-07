#pragma once

//Common Header
#include <Windows.h>
#include <assert.h>
#include <mutex>

//STL
#include <vector>
#include <map>
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
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/ImGuizmo.h"
#pragma comment(lib, "ImGui/imgui.lib")

//DirectWrite
#include <d2d1_2.h>
#include <dwrite.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

#include <FMod/fmod.hpp>
#pragma comment(lib, "FMod/fmodexL_vc.lib")

//Macro
#define SafeRelease(p) { if(p) { (p)->Release(); (p) = nullptr; } }
#define SafeDelete(p) { if(p) { delete (p); (p) = nullptr; } }
#define SafeDeleteArray(p) { if(p) { delete[] (p); (p) = nullptr; } }
#define Check(hr) { assert(SUCCEEDED(hr)); }
#define CheckNull(p) { if(p == nullptr) return; }
#define CheckTrue(p) { if(p == true) return; }
#define CheckFalse(p) { if(p == false) return; }
#define CheckNullResult(p, result) { if(p == nullptr) return result; }
#define CheckTrueResult(p, result) { if(p == true) return result; }
#define CheckFalseResult(p, result) { if(p == false) return result; }

//Typedef
typedef D3DXVECTOR3 Vector3;
typedef D3DXVECTOR2 Vector2;
typedef D3DXCOLOR Color;
typedef D3DXMATRIX Matrix;

//Framework
#include "Systems/Keyboard.h"
#include "Systems/CMouse.h"
#include "Systems/Time.h"
#include "Systems/DirectWrite.h"
#include "Systems/Gui.h"
#include "Systems/CSound.h"

#include "Utilities/String.h"
#include "Utilities/Path.h"
#include "Utilities/Math.h"
#include "Utilities/BinaryFile.h"

#include "Renders/Shader.h"
#include "Renders/Context.h"
#include "Renders/PerFrame.h"
#include "Renders/Sprite.h"
#include "Renders/Clip.h"
#include "Renders/Animation.h"

#include "Viewer/Camera.h"
#include "Viewer/Freedom.h"
#include "Viewer/Follow.h"

#include "Collider/Collider.h"

//Glbal Variable
extern UINT Width;
extern UINT Height;

extern HWND Hwnd;
extern wstring Title;

//DirectX ComInterface
extern IDXGISwapChain* SwapChain;
extern ID3D11Device* Device;
extern ID3D11DeviceContext* DeviceContext;
extern ID3D11RenderTargetView* RTV;

extern Keyboard* Key;
extern CMouse* Mouse;
extern CSound* Sound;
