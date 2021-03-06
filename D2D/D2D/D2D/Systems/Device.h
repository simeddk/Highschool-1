#pragma once

//Global Function
void InitWindow(HINSTANCE hInstance, int nCmdShow);
void InitDirect3D(HINSTANCE hInstance);
void Destroy();
WPARAM Running();
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//Scene
void InitScene();
void DestroyScene();
void Update();
void Render();
void PostRender();

void CreateBackBuffer();
void DeleteBackBuffer();