#include "Device.h"

void InitScene()
{

}

void DestroyScene()
{

}

void Update()
{

}

void Render()
{
	D3DXCOLOR bgcolor = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgcolor);
	{
		//�׷��ִ� �ڵ� �ۼ�
	}
	SwapChain->Present(0, 0);
}