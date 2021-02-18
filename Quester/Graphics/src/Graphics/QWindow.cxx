//
// Created by Percebe32 on 2/12/2021.
//

#include <Graphics/QWindow.hxx>

QWindow::QWindow(const std::string &title, int width, int height) :
        _title(title), _width(width), _height(height), _backend(DX11_Backend())
{
    spdlog::debug("Initializing window uuid[{0}] . . .", title.c_str());

    if(!Initialize()) {
        _closed = true;
    }
}

QWindow::~QWindow()
{
    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

#ifdef USING_DX11
    _backend.CleanupDeviceD3D();
#endif

    spdlog::debug("Window uuid[{0}] terminated with no errors.", _title.c_str());

    SDL_DestroyWindow(_window);
    SDL_Quit();
}

bool QWindow::Initialize() {
    // Setup SDL
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        spdlog::error("SDL Error: {0}", SDL_GetError());
        return 0;
    }

    // Setup window
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    _window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, window_flags);

    if(_window == nullptr) {
        spdlog::error("QWindow::_window returned: nullptr.");
        return 0;
    }

    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(_window, &wmInfo);
    HWND hwnd = (HWND)wmInfo.info.win.window;

#ifdef USING_DX11
    // Initialize Direct3D
    if (!_backend.CreateDeviceD3D(hwnd))
    {
        _backend.CleanupDeviceD3D();
        spdlog::error("Could not create DeviceD3D");
        return 1;
    }

    spdlog::debug("D3D11 Device: Passing");
#endif

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    /* SET APP STYLE ==> */ Style();

    ImGui_ImplSDL2_InitForD3D(_window);
    spdlog::debug("ImGui SDL2 Implementation: Passing");
#ifdef USING_DX11
    ImGui_ImplDX11_Init(_backend.GetBackendSpecific()._device, _backend.GetBackendSpecific()._deviceContext);
    spdlog::debug("ImGui D3D11 Implementation: Passing");
#endif
    io.Fonts->AddFontFromFileTTF("assets/fonts/IBMPlex/IBMPlexSansCondensed-Medium.ttf", 18.0f);

    return true;
}

void QWindow::Render() {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT)
            _closed = true;
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(_window))
            _closed = true;
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED && event.window.windowID == SDL_GetWindowID(_window))
        {
            // Release all outstanding references to the swap chain's buffers before resizing.
#ifdef USING_DX11
            _backend.CleanupRenderTarget();
            _backend.GetBackendSpecific()._swapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
            _backend.CreateRenderTarget();
#endif
        }
    }

    // Start the Dear ImGui frame
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplSDL2_NewFrame(_window);
    ImGui::NewFrame();
}

void QWindow::FinishRender() {
    // Rendering
    ImGui::Render();
#ifdef USING_DX11
    ID3D11RenderTargetView* tView = _backend.GetBackendSpecific()._renderTargetView;
    _backend.GetBackendSpecific()._deviceContext->OMSetRenderTargets(
            1,
            &tView,
            NULL);

    _backend.GetBackendSpecific()._deviceContext->ClearRenderTargetView(
            _backend.GetBackendSpecific()._renderTargetView,
            (float*)&_clearColor);

    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
#endif
    // Update and Render additional Platform Windows
    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
#ifdef USING_DX11
    _backend.GetBackendSpecific()._swapChain->Present(1, 0); // Present with vsync
    //_backend.GetBackendSpecific()._swapChain->Present(0, 0); // Present without vsync
#endif
}