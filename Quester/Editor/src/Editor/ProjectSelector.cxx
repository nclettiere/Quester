//
// Created by Percebe32 on 2/11/2021.
//

#include <Editor/ProjectSelector.hxx>

void ProjectSelector::OnFrame() {

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Options"))
        {
            // Disabling fullscreen would allow the window to be moved to the front of other windows,
            // which we can't undo at the moment without finer window depth/z control.
            ImGui::MenuItem("Fullscreen", NULL, nullptr);
            ImGui::MenuItem("Padding", NULL, nullptr);
            ImGui::Separator();

            ImGui::Separator();

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    ImGui::Begin("Project Selector");

    ImGui::Dummy(ImVec2(0, 8.0f));

    ImGui::Dummy(ImVec2(16.0f, 16.0f)); ImGui::SameLine();
    ImGui::Text("Select or Create Project");

    ImGui::Dummy(ImVec2(0, 8.0f));

    ImGui::Dummy(ImVec2(16.0f, 16.0f)); ImGui::SameLine();

    if(ImGui::ImageButton(testTexture,ImVec2(120, 120),ImVec2(0, 0), ImVec2(1.0f, 1.0f),2))
        ImGui::OpenPopup("Create Project");

    ImGui::SameLine(); ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);

    //ImGui::Begin("Progress Indicators");

    const ImU32 col = ImGui::GetColorU32(ImGuiCol_NavHighlight);
    const ImU32 bg = ImGui::GetColorU32(ImGuiCol_Button);

    //Spinner("##spinner", 15, 6, col);

    //ImGui::End();

    ImGui::SetNextWindowSize(ImVec2(350, 310));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 8));
    if (ImGui::BeginPopupModal("Create Project", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove))
    {
        ImGui::Text("Enter Project Name:");
        ImGui::PushItemWidth(-1);
        ImGui::InputText("##p-name", _titleBuf, 64, ImGuiInputTextFlags_CallbackCharFilter, TextFilters::FilterImGuiLetters);
        ImGui::PopItemWidth();

        ImGui::Text("Select Unreal Engine Version:");
        ImGui::PushItemWidth(-1);
        ImGui::Combo("##p-ue4v", &_selectedUE4Version, G_ue4Versions, IM_ARRAYSIZE(G_ue4Versions));
        //ImGui::Combo("##p-ue4v", &_selectedUE4Version, _availableUE4Versions);
        ImGui::PopItemWidth();

        ImGui::Text("Enter Short Description (optional):");
        ImGui::InputTextMultiline("##source", _descriptionBuf, IM_ARRAYSIZE(_descriptionBuf), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 5), ImGuiInputTextFlags_AllowTabInput);

        //ImGui::ColorEdit4("color", color);

        ImGui::Dummy(ImVec2(0.0f, 16.0f));

        ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV( 7.0f, 0.6f, 0.6f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(7.0f, 0.7f, 0.7f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV( 7.0f, 0.8f, 0.8f));
        if (ImGui::Button("Cancel", ImVec2(100, 32.0f))) {
            _selectedUE4Version = 0;
            memset(_descriptionBuf, 0, sizeof _descriptionBuf);
            memset(_titleBuf, 0, sizeof _titleBuf);
            ImGui::CloseCurrentPopup();
        }
        ImGui::PopStyleColor(3);

        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(2 / 7.0f, 0.6f, 0.6f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(2 / 7.0f, 0.7f, 0.7f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(2 / 7.0f, 0.8f, 0.8f));

        if(strlen(_titleBuf) == 0) {
            ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
        }
        if(ImGui::Button("Create", ImVec2(-FLT_MIN, 32.0f))) {
            ImGui::OpenPopup("Loading");

            QProject p = QProject(
                    std::string(_titleBuf),
                    std::string(G_ue4Versions[_selectedUE4Version]),
                    std::string(_descriptionBuf));
            p.SaveProject();
            savingProject = false;
        }

        if(strlen(_titleBuf) == 0) {
            ImGui::PopItemFlag();
            ImGui::PopStyleVar();
        }

        ImGui::PopStyleColor(3);

        //BufferingBar("##buffer_bar", 0.0f, ImVec2(400, 6), bg, col);
        if (ImGui::BeginPopupModal("Loading", &savingProject,
                                   ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDecoration |
                                   ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBackground |
                                   ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize |
                                   ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar)) {
            Spinner("##spinner", 10, 3, col);
            if(!savingProject) {
                ImGui::EndPopup();
            }
        }

        ImGui::EndPopup();
    }
    ImGui::PopStyleVar();

    ImGui::End();

    bool opened = true;
    ImGui::ShowDemoWindow(&opened);
}
