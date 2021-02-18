//
// Created by Percebe32 on 2/12/2021.
//

#ifndef QUESTER_QWINDOW_HXX
#define QUESTER_QWINDOW_HXX

#include <Core/DX11_Backend.hxx>

#include <backends/imgui_impl_sdl.h>
#include <backends/imgui_impl_dx11.h>
#include <SDL.h>
#include <SDL_syswm.h>

#include <Graphics/Global.h>
#include <Graphics/QTexture.hxx>



#include <string>

class QWindow : public IQTexture {
public:
    QWindow(const std::string &title, int width, int height);
    ~QWindow();

    inline bool IsClosed() const { return _closed; }

private:
    bool Initialize();
public:
    void Render();
    void FinishRender();

    IBackend<DX_Data>* GetBackendData() {
        return &_backend;
    }

private:
    std::string _title;
    int         _width =  1280;
    int         _height = 720;
    bool        _closed = false;

    ImVec4 _clearColor = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);

    DX11_Backend _backend;
    SDL_Window* _window = nullptr;

};


#endif //QUESTER_QWINDOW_HXX
