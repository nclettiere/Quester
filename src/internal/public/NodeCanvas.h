#pragma once 

#include <memory> 
#include "wx/glcanvas.h" 
class NodeCanvas : public wxGLCanvas 
{
    public:
        NodeCanvas(wxWindow* parent, wxWindowID id = wxID_ANY, 
            const int* attribList = 0,
            const wxPoint& pos = wxDefaultPosition, 
            const wxSize& size = wxDefaultSize, long style = 0L, 
            const wxString& name = L"GLCanvas", 
            const wxPalette& palette = wxNullPalette);
        virtual ~NodeCanvas();
        NodeCanvas(const NodeCanvas& tc) = delete;
        NodeCanvas(NodeCanvas&& tc) = delete;
        NodeCanvas& operator=(const NodeCanvas& tc) = delete; 
        NodeCanvas& operator=(NodeCanvas&& tc) = delete; 
    private:
            void InitializeGLEW();
            void SetupGraphics();
            void OnPaint(wxPaintEvent& event);

            std::unique_ptr<wxGLContext> m_context;
            GLuint m_vbo; // vertex buffer pointer
            GLuint m_vao; // vertex array pointer 
};
