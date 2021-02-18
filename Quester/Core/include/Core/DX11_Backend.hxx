//
// Created by Percebe64 on 2/11/2021.
//

#ifndef QUESTER_CORE_H
#define QUESTER_CORE_H

#define USING_DX11

#include <Core/IBackend.hxx>
#include <d3d11.h>

struct DX_Data {
    DX_Data(ID3D11Device* device,
            ID3D11DeviceContext* deviceContext,
            IDXGISwapChain* swapChain,
            ID3D11RenderTargetView*  renderTargetView) :
    _device(device), _deviceContext(deviceContext), _swapChain(swapChain), _renderTargetView(renderTargetView) {}

    ID3D11Device* _device;
    ID3D11DeviceContext* _deviceContext;
    IDXGISwapChain* _swapChain;
    ID3D11RenderTargetView* _renderTargetView;
};

class DX11_Backend : public IBackend<DX_Data> {
public:
    DX11_Backend() = default;
    ~DX11_Backend() = default;

    DX_Data GetBackendSpecific() override {
        return DX_Data(g_pd3dDevice, g_pd3dDeviceContext, g_pSwapChain, g_mainRenderTargetView);
    }

    virtual void CleanupDeviceD3D();
    virtual bool CreateDeviceD3D(HWND hWnd);
    virtual void CleanupRenderTarget();
    virtual void CreateRenderTarget();

protected:
    // Data
    ID3D11Device*            g_pd3dDevice = nullptr;
    ID3D11DeviceContext*     g_pd3dDeviceContext = nullptr;
    IDXGISwapChain*          g_pSwapChain = nullptr;
    ID3D11RenderTargetView*  g_mainRenderTargetView = nullptr;

};
#endif // QUESTER_CORE_H