#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <stdio.h>

// include OpenGL
#ifdef __WXMAC__
#include "OpenGL/glu.h"
#include "OpenGL/gl.h"
#else
#include <GL/glew.h>
#include <GL/gl.h>
#endif

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/sizer.h>
#include <wx/listctrl.h>

#include "wx/sizer.h"
#include "wx/glcanvas.h"

#include "BasicGLPane.h"

#include <iostream>

class QuestEditor : public wxFrame
{
public:
	QuestEditor();

private:
	wxFrame* frame;
	BasicGLPane* glPane;
};

