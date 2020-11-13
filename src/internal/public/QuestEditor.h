#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <stdio.h>

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/sizer.h>
#include <wx/listctrl.h>

#include "wx/sizer.h"
#include "wx/glcanvas.h"

#include "NodeCanvas.h"

#include <iostream>

class QuestEditor : public wxFrame
{
public:
	QuestEditor(wxWindow* parent, const std::string title, const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize);
	virtual ~QuestEditor();
	QuestEditor(const QuestEditor& tw) = delete;
	QuestEditor(QuestEditor&& tw) = delete;
	QuestEditor& operator=(const QuestEditor& tw) = delete;
	QuestEditor& operator=(QuestEditor&&) = delete;
};
