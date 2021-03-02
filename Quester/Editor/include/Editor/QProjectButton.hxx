//
// Created by Percebe64 on 2/27/2021.
//

#ifndef QUESTER_QPROJECTBUTTON_HXX
#define QUESTER_QPROJECTBUTTON_HXX

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>
#include <spdlog/spdlog.h>
#include <Graphics/QWindow.hxx>

struct ProjectButtonData {
    ProjectButtonData() = default;

    ProjectButtonData(const std::string& title, const std::string& path) : _title(title), _path(path) {}

    const char * GetTitle() const { return _title.c_str(); };
    const char * GetPath() const { return _path.c_str(); };

    const std::string _title, _path;
};

static inline ImVec2 operator*(const ImVec2& lhs, const float rhs)              { return ImVec2(lhs.x * rhs, lhs.y * rhs); }
static inline ImVec2 operator/(const ImVec2& lhs, const float rhs)              { return ImVec2(lhs.x / rhs, lhs.y / rhs); }
static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs)            { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
static inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs)            { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }
static inline ImVec2 operator*(const ImVec2& lhs, const ImVec2& rhs)            { return ImVec2(lhs.x * rhs.x, lhs.y * rhs.y); }
static inline ImVec2 operator/(const ImVec2& lhs, const ImVec2& rhs)            { return ImVec2(lhs.x / rhs.x, lhs.y / rhs.y); }
static inline ImVec2& operator*=(ImVec2& lhs, const float rhs)                  { lhs.x *= rhs; lhs.y *= rhs; return lhs; }
static inline ImVec2& operator/=(ImVec2& lhs, const float rhs)                  { lhs.x /= rhs; lhs.y /= rhs; return lhs; }
static inline ImVec2& operator+=(ImVec2& lhs, const ImVec2& rhs)                { lhs.x += rhs.x; lhs.y += rhs.y; return lhs; }
static inline ImVec2& operator-=(ImVec2& lhs, const ImVec2& rhs)                { lhs.x -= rhs.x; lhs.y -= rhs.y; return lhs; }
static inline ImVec2& operator*=(ImVec2& lhs, const ImVec2& rhs)                { lhs.x *= rhs.x; lhs.y *= rhs.y; return lhs; }
static inline ImVec2& operator/=(ImVec2& lhs, const ImVec2& rhs)                { lhs.x /= rhs.x; lhs.y /= rhs.y; return lhs; }
static inline ImVec4 operator+(const ImVec4& lhs, const ImVec4& rhs)            { return ImVec4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w); }
static inline ImVec4 operator-(const ImVec4& lhs, const ImVec4& rhs)            { return ImVec4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w); }
static inline ImVec4 operator*(const ImVec4& lhs, const ImVec4& rhs)            { return ImVec4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w); }

namespace ImGui {
    static IMGUI_API bool QProjectButton(const char* id, QWindow* qWindow, const ImVec2& size, const ProjectButtonData& data, int frame_padding = -1, const ImVec4& bg_col = ImVec4(0,0,0,0), const ImVec4& tint_col = ImVec4(1,1,1,1), ImGuiButtonFlags flags = ImGuiButtonFlags_None);
    static void LoadUE4Logo(QWindow& qWindow);
    static ID3D11ShaderResourceView* ue4Logo = NULL;
    static int ue4LogoW;
    static int ue4LogoH;
}

namespace ImGui {
    void LoadUE4Logo(QWindow& qWindow) {
        qWindow.LoadTextureDX11(
                qWindow.GetBackendData()->GetBackendSpecific()._device,
                R"(assets\textures\ue4_24_blue.png)",
                &ue4Logo,
                &ue4LogoW,
                &ue4LogoH);
    }

    IMGUI_API bool QProjectButton(const char* id_str, QWindow* qWindow, const ImVec2& size, const ProjectButtonData& data, int frame_padding, const ImVec4& bg_col, const ImVec4& tint_col, ImGuiButtonFlags flags) {
        ImGuiWindow* window = GetCurrentWindow();
        if (window->SkipItems)
            return false;

        ImGuiContext& g = *GImGui;
        const ImGuiStyle& style = g.Style;
        const ImGuiID id = window->GetID(id_str);
        const ImVec2 title_size = CalcTextSize(data.GetTitle(), NULL, true);
        const ImVec2 path_size = CalcTextSize(data.GetPath(), NULL, true);

        ImVec2 pos = window->DC.CursorPos;
        if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
            pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
        //ImVec2 size = CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

        const ImRect bb(pos, pos + size);
        ItemSize(size, style.FramePadding.y);
        if (!ItemAdd(bb, id))
            return false;

        if (window->DC.ItemFlags & ImGuiItemFlags_ButtonRepeat)
            flags |= ImGuiButtonFlags_Repeat;
        bool hovered, held;
        bool pressed = ButtonBehavior(bb, id, &hovered, &held, flags);

        // Render
        const ImU32 col = GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
        RenderNavHighlight(bb, id);
        RenderFrame(bb.Min, bb.Max, col, true, style.FrameRounding);

        if (g.LogEnabled)
            LogSetNextTextDecoration("[", "]");

        ImVec2 minTitle = bb.Min + style.FramePadding - size + ImVec2(50, 30);
        ImVec2 minPath = bb.Min + style.FramePadding - size + ImVec2(50, 65);
        ImVec2 max = bb.Max - style.FramePadding;

        RenderTextClipped(minTitle, max, data.GetTitle(), NULL, &title_size, style.ButtonTextAlign, &bb);

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 0.4f));
        RenderTextClipped(minPath, max, data.GetPath(), NULL, &title_size, style.ButtonTextAlign, &bb);
        ImGui::PopStyleColor();

        if(ue4Logo == nullptr)
            LoadUE4Logo(*qWindow);

        window->DrawList->AddImage(ue4Logo, bb.Min, bb.Max, ImVec2(0, 0), ImVec2(1.0f, 1.0f), GetColorU32(tint_col));

        // Automatically close popups
        //if (pressed && !(flags & ImGuiButtonFlags_DontClosePopups) && (window->Flags & ImGuiWindowFlags_Popup))
        //    CloseCurrentPopup();

        IMGUI_TEST_ENGINE_ITEM_INFO(id, label, window->DC.LastItemStatusFlags);
        return pressed;
    }
}

#endif //QUESTER_QPROJECTBUTTON_HXX
