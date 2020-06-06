#include "br.pch.h"



#include "Brain/Renderer/texture.h"
#include "Brain/Renderer/renderer_api.h"
#include "Platform/OpenGL/opengl_texture.h"



namespace Brain
{
    Ref<Texture_2D> Texture_2D::create( uint32_t width, uint32_t height )
    {
        switch( Renderer_API::get_api() )
        {
        case Renderer_API::API::None:
            BR_CORE_ASSERT( false, "Renderer_API::None is not currently supported!" );
            return nullptr;
        case Renderer_API::API::OpenGL:
            return create_ref<OpenGL_Texture_2D>( width, height );
        }

        BR_CORE_ASSERT( false, "Unknown Renderer API!" );
        return nullptr;
    }



    Ref<Texture_2D> Texture_2D::create( const std::string& path )
    {
        switch( Renderer_API::get_api() )
        {
        case Renderer_API::API::None:
            BR_CORE_ASSERT( false, "Renderer_API::None is not currently supported!" );
            return nullptr;
        case Renderer_API::API::OpenGL:
            return create_ref<OpenGL_Texture_2D>( path );
        }

        BR_CORE_ASSERT( false, "Unknown Renderer API!" );
        return nullptr;
    }
}