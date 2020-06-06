#pragma once



#include "Brain/Renderer/render_context.h"



struct GLFWwindow;



namespace Brain
{
    class OpenGL_Context : public Render_Context
    {
    public:
        OpenGL_Context( GLFWwindow* window_handle );

        void init( void ) override;
        void swap_buffers( void ) override;

    private:
        GLFWwindow* window_handle_;
    };
}