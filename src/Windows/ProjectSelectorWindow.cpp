//
// Created by Percebe32 on 2/11/2021.
//

#include <Windows/ProjectSelectorWindow.h>

void ProjectSelectorWindow::Run() {
    ProjectSelector stats(&_window, _ue4Versions);

    while(!_window.IsClosed()) {
        _window.Render();

        stats.Run();

        _window.FinishRender();
    }
}

