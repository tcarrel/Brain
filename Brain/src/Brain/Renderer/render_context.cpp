#include "br.pch.h"
#include "Brain/Renderer/render_context.h"



#include "Brain/Renderer/Renderer.h"
#include "Platform/OpenGL/opengl_context.h"



namespace Brain
{
    Scope<Render_Context> Render_Context::create( void* window )
    {
        switch( Renderer::get_api() )
        {
        case Renderer_API::API::None:
            BR_CORE_ASSERT( false, "Renderer_API::None is currently not supportsd." );
            return nullptr;
        case Renderer_API::API::OpenGL:
            return create_scope<OpenGL_Context>( static_cast<GLFWwindow*>( window ) );
        }

        BR_CORE_ASSERT( false, "Renderer_API::?Unknown" );
        return nullptr;
    }
}
