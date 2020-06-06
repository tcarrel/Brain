#include "br.pch.h"
#include "Platform/OpenGL/opengl_renderer_api.h"



#include<glad/glad.h>



namespace Brain
{
    void OpenGL_Message_Callback( 
        [[maybe_unused]] unsigned source,
        [[maybe_unused]] unsigned type,
        [[maybe_unused]] unsigned id,
        unsigned severity,
        [[maybe_unused]] int length,
        const char* msg,
        [[maybe_unused]] const void* user )
    {
        switch( severity )
        {
        case GL_DEBUG_SEVERITY_HIGH:
            BR_CORE_FATAL( msg );
            return;
        case GL_DEBUG_SEVERITY_MEDIUM:
            BR_CORE_ERROR( msg );
            return;
        case GL_DEBUG_SEVERITY_LOW:
            BR_CORE_INFO( msg );
            return;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            BR_CORE_TRACE( msg );
            return;
        }
        BR_CORE_ASSERT( false, "Unknown OpenGL Message severity level." );
    }



    void OpenGL_Renderer_API::init( void )
    {
        BR_PROFILE_FUNCTION();

#ifdef BR_DEBUG
        glEnable( GL_DEBUG_OUTPUT );
        glEnable( GL_DEBUG_OUTPUT_SYNCHRONOUS );
        glDebugMessageCallback( OpenGL_Message_Callback, nullptr );

        glDebugMessageControl( GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE );
#endif

        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

        glEnable( GL_DEPTH_TEST );
    }



    void OpenGL_Renderer_API::set_viewport( uint32_t x, uint32_t y, uint32_t w, uint32_t h )
    {
        glViewport( x, y, w, h );
    }



    void OpenGL_Renderer_API::set_clear_color( const glm::vec4& color )
    {
        glClearColor( color.r, color.g, color.b, color.a );
    }



    void OpenGL_Renderer_API::clear( void )
    {
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    }



    void OpenGL_Renderer_API::draw_indexed( const Ref<Vertex_Array>& vert_array )
    {
        glDrawElements( GL_TRIANGLES, vert_array->index_buffer()->get_count(), GL_UNSIGNED_INT, nullptr );
        glBindTexture( GL_TEXTURE_2D, 0 );
    }
}
