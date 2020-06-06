#include "br.pch.h"
#include "Brain/Renderer/renderer_api.h"



#include "Platform/OpenGL/opengl_renderer_api.h"



namespace Brain
{
    Renderer_API::API Renderer_API::api_{ Renderer_API::API::OpenGL };



    Scope<Renderer_API> Renderer_API::create( void )
    {
        switch( api_ )
        {
        case Brain::Renderer_API::API::None:
            BR_CORE_ASSERT( false, "Renderer_API::None is currently not supportsd." );
            return nullptr;

        case Brain::Renderer_API::API::OpenGL:
            return create_scope<OpenGL_Renderer_API>();
        }

        BR_CORE_ASSERT( false, "Renderer_API::?Unknown" );
        return nullptr;
    }
}
