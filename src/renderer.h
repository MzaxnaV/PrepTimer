#ifndef RENDERER_H_
#define RENDERER_H_

#include <d3d11.h>

bool InitD3D(HWND hwnd);
void ShutdownD3D();
void BeginFrame(float r, float g, float b);
void OnWindowResize(UINT width, UINT height);
void EndFrame();

ID3D11Device*        GetDevice();
ID3D11DeviceContext* GetContext();
ID3D11RenderTargetView** GetRenderTarget();

#endif // RENDERER_H_