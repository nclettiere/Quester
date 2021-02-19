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

private:
    QWindow _window;
};

#endif //QUESTER_PROJECTSELECTORWINDOW_H
