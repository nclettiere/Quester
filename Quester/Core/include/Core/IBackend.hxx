//
// Created by Percebe64 on 2/13/2021.
//

#ifndef QUESTER_IBACKEND_HXX
#define QUESTER_IBACKEND_HXX

#include <string>

enum class DX11_Requests {
    ID3D11Device,
    ID3D11DeviceContext,
    IDXGISwapChain,
    ID3D11RenderTargetView
};

template <typename T>
class IBackend {
public:
    explicit IBackend() {}

    virtual T GetBackendSpecific() = 0;
};

#endif //QUESTER_IBACKEND_HXX
