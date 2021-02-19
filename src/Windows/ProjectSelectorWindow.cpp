//
// Created by Percebe32 on 2/11/2021.
//

#include <Windows/ProjectSelectorWindow.h>

void ProjectSelectorWindow::Run() {
    ProjectSelector pSelector(&_window);

    while(!_window.IsClosed()) {
        _window.Render();

        pSelector.Run();

        _window.FinishRender();
    }
}