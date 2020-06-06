#include "br.pch.h"
#include "Platform/OpenGL/opengl_context.h"



#include <glad/glad.h>
#include <GLFW/glfw3.h>



namespace Brain
{
    OpenGL_Context::OpenGL_Context( GLFWwindow* window_handle )
        :
        window_handle_( window_handle )
    {
        BR_CORE_ASSERT( window_handle, "Window handle is nullptr," );
    }



    void OpenGL_Context::init( void )
    {
        BR_PROFILE_FUNCTION();

        glfwMakeContextCurrent( window_handle_ );
        auto glad_status = gladLoadGLLoader( reinterpret_cast<GLADloadproc>( glfwGetProcAddress ) );
        BR_CORE_ASSERT( glad_status, "Failed to initialize \"glad!\"" );

        BR_CORE_INFO( "OpenGL Info:" );
        BR_CORE_INFO( "\tVendor\t\t:\t{0}", glGetString( GL_VENDOR ) );
        BR_CORE_INFO( "\tVersion\t\t:\t{0}", glGetString( GL_VERSION ) );
        BR_CORE_INFO( "\tDevice\t\t:\t{0}", glGetString( GL_RENDERER ) );

        int ver_maj{ 0 }, ver_min{ 0 };
        glGetIntegerv( GL_MAJOR_VERSION, &ver_maj );
        glGetIntegerv( GL_MINOR_VERSION, &ver_min );

        BR_CORE_ASSERT( ver_maj > 4 || ( ver_maj == 4 && ver_min >= 5 ), "Brain need at least OpenGL 4.5." );

        BR_CORE_INFO( "\tOpenGL Version\t:\t{0}.{1}", ver_maj, ver_min );
    }
    
    
    
    void OpenGL_Context::swap_buffers( void )
    {
        BR_PROFILE_FUNCTION();

        glfwSwapBuffers( window_handle_ );
    }
}