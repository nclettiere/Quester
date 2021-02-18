//
// Created by Percebe32 on 2/11/2021.
//

#ifndef QUESTER_PROJECTSELECTORWINDOW_H
#define QUESTER_PROJECTSELECTORWINDOW_H

#include <Editor/ProjectSelector.hxx>


class ProjectSelectorWindow {

public:
    ProjectSelectorWindow() : _window(QWindow("Project Selector", 720, 560)) {}

    void Run();

protected:
    const char* _ue4Versions = " 4.26\0 4.25\0 4.24\0 4.23\0 4.22\0 4.21\0 4.20\0\0";

private:
    QWindow _window;
};

#endif //QUESTER_PROJECTSELECTORWINDOW_H
