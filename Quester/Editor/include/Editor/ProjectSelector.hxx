//
// Created by Percebe32 on 2/11/2021.
//

#ifndef QUESTER_PROJECTSELECTOR_HXX
#define QUESTER_PROJECTSELECTOR_HXX

#include <Editor/IBase.h>
#include <Editor/QProjectButton.hxx>
#include <Graphics/QWindow.hxx>
#include <Core/QGlobals.hxx>
#include <Core/QProject.hxx>

#include <vector>

using namespace ImGui;

class ProjectSelector: public IBaseEditorWindow {
public:
    ProjectSelector(QWindow* window)
    : IBaseEditorWindow("Stats"), _window(window) {
        _window->LoadTextureDX11(
                _window->GetBackendData()->GetBackendSpecific()._device,
                R"(assets\textures\new_project.png)",
                &testTexture,
                &testW,
                &testH);

    }

    virtual void OnFrame();
    virtual void Run() {
        InitializeWindow();
        OnFrame();
        FinishWindow();
    }

private:
    int _selectedUE4Version = 0;
    char _titleBuf[64] = "";
    char _descriptionBuf[256] = "";

    bool savingProject = true;

    float color[4] = { 0.4f, 0.7f, 0.0f, 0.5f };

    std::vector<std::string> vProjects;

    unsigned int lastTime = 0, currentTime;

    bool
    BufferingBar(const char *label, float value, const ImVec2 &size_arg, const ImU32 &bg_col, const ImU32 &fg_col) {
        ImGuiWindow *window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext &g = *GImGui;
        const ImGuiStyle &style = g.Style;
        const ImGuiID id = window->GetID(label);

        ImVec2 pos = window->DC.CursorPos;
        ImVec2 size = size_arg;
        size.x -= style.FramePadding.x * 2;

        const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
        ItemSize(bb, style.FramePadding.y);
        if (!ItemAdd(bb, id))
            return false;

        // Render
        const float circleStart = size.x * 0.7f;
        const float circleEnd = size.x;
        const float circleWidth = circleEnd - circleStart;

        window->DrawList->AddRectFilled(bb.Min, ImVec2(pos.x + circleStart, bb.Max.y), bg_col);
        window->DrawList->AddRectFilled(bb.Min, ImVec2(pos.x + circleStart * value, bb.Max.y), fg_col);

        const float t = g.Time;
        const float r = size.y / 2;
        const float speed = 1.5f;

        const float a = speed * 0;
        const float b = speed * 0.333f;
        const float c = speed * 0.666f;

        const float o1 = (circleWidth + r) * (t + a - speed * (int) ((t + a) / speed)) / speed;
        const float o2 = (circleWidth + r) * (t + b - speed * (int) ((t + b) / speed)) / speed;
        const float o3 = (circleWidth + r) * (t + c - speed * (int) ((t + c) / speed)) / speed;

        window->DrawList->AddCircleFilled(ImVec2(pos.x + circleEnd - o1, bb.Min.y + r), r, bg_col);
        window->DrawList->AddCircleFilled(ImVec2(pos.x + circleEnd - o2, bb.Min.y + r), r, bg_col);
        window->DrawList->AddCircleFilled(ImVec2(pos.x + circleEnd - o3, bb.Min.y + r), r, bg_col);
    }

    bool Spinner(const char *label, float radius, int thickness, const ImU32 &color) {
        ImGuiWindow *window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext &g = *GImGui;
        const ImGuiStyle &style = g.Style;
        const ImGuiID id = window->GetID(label);

        ImVec2 pos = window->DC.CursorPos;
        ImVec2 size((radius) * 2, (radius + style.FramePadding.y) * 2);

        const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
        ItemSize(bb, style.FramePadding.y);
        if (!ItemAdd(bb, id))
            return false;

        // Render
        window->DrawList->PathClear();

        int num_segments = 30;
        int start = abs(ImSin(g.Time * 1.8f) * (num_segments - 5));

        const float a_min = IM_PI * 2.0f * ((float) start) / (float) num_segments;
        const float a_max = IM_PI * 2.0f * ((float) num_segments - 3) / (float) num_segments;

        const ImVec2 centre = ImVec2(pos.x + radius, pos.y + radius + style.FramePadding.y);

        for (int i = 0; i < num_segments; i++) {
            const float a = a_min + ((float) i / (float) num_segments) * (a_max - a_min);
            window->DrawList->PathLineTo(ImVec2(centre.x + ImCos(a + g.Time * 8) * radius,
                                                centre.y + ImSin(a + g.Time * 8) * radius));
        }

        window->DrawList->PathStroke(color, false, thickness);

        return true;
    }



protected:
    ID3D11ShaderResourceView* testTexture = NULL;
    int testW;
    int testH;

    struct TextFilters
    {
        // Return 0 (pass) if no symbols are typed.
        static int FilterImGuiLetters(ImGuiInputTextCallbackData* data)
        {
            if (data->EventChar < 256 && strchr(R"(`~!@#$%^&*()+[]\/,.<>='"{}|:;?)", (char)data->EventChar))
                return 1;
            return 0;
        }
    };

public:

    QWindow* _window;
};

#endif //QUESTER_PROJECTSELECTOR_HXX
