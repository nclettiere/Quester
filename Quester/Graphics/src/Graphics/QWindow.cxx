//
// Created by Percebe32 on 2/12/2021.
//

#include <Graphics/QWindow.hxx>

#ifdef DEBUG
#define D_PRINT_OUT(fmt, ...) fprintf(stdout, fmt, __VA_ARGS__)
#define D_PRINT_CERR(fmt, ...) fprintf(stdout, fmt, __VA_ARGS__)
#else
#define D_PRINT_OUT(fmt, ...) do {} while (0)
#define D_PRINT_CERR(fmt, ...) do {} while (0)
#endif

QWindow::QWindow(const std::string &title, int width, int height) :
        _title(title), _width(width), _height(height), _backend(DX11_Backend())
{
    D_PRINT_OUT("Initializing window id[%s] . . .\n", title.c_str());

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

    D_PRINT_CERR("Window id[%s] terminated with no errors.\n", _title.c_str());

    SDL_DestroyWindow(_window);
    SDL_Quit();
}

bool QWindow::Initialize() {
    // Setup SDL
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return 0;
    }

    // Setup window
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    _window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, window_flags);

    if(_window == nullptr) {
        std::cerr << "QWindow::_window returned: nullptr.\n";
        return 0;
    }

    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(_window, &wmInfo);
    HWND hwnd = (HWND)wmInfo.info.win.window;

#ifdef USING_DX11
    std::cout << "Initializing Direct3D\n";
    // Initialize Direct3D
    if (!_backend.CreateDeviceD3D(hwnd))
    {
        _backend.CleanupDeviceD3D();
        std::cerr << "Could not create DeviceD3D.\n";
        return 1;
    }
    std::cout << "Good\n";
#endif

    std::cout << "Passing IMGUI Context and IO\n";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    //ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // SET_STYLE METHOD HERE !
    Style();

    std::cout << "Good\n";
    std::cout << "Setup Platform/Renderer backends\n";
    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForD3D(_window);
    std::cout << "SDL2: Passing\n";
#ifdef USING_DX11
    std::cout << "Testing backend specific passing...\n";
    std::cout << "IS DEVICE NULLPTR " << (_backend.GetBackendSpecific()._device == nullptr) << '\n';
    ImGui_ImplDX11_Init(_backend.GetBackendSpecific()._device, _backend.GetBackendSpecific()._deviceContext);
    //std::cout << "Good\n";
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
    //std::cout << "Testing DeviceContext...\n";
    ID3D11RenderTargetView* tView = _backend.GetBackendSpecific()._renderTargetView;
    _backend.GetBackendSpecific()._deviceContext->OMSetRenderTargets(
            1,
            &tView, //reinterpret_cast<ID3D11RenderTargetView *const *>
            NULL);
    //std::cout << "Good\n";

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