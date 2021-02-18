#include <Windows/ProjectSelectorWindow.h>
#include <spdlog/spdlog-inl.h>

int main(int, char**)
{
#ifdef DEBUG
    spdlog::set_level(spdlog::level::debug); // Set global log level to debug
#endif

    ProjectSelectorWindow projectSelector;
    projectSelector.Run();
    return 0;
}