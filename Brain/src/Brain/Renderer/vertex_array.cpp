#include "br.pch.h"
#include "Brain/Renderer/renderer.h"
#include "Brain/Renderer/vertex_array.h"
#include "Platform/OpenGL/opengl_vertex_array.h"



namespace Brain
{
    Ref<Vertex_Array> Vertex_Array::create( void )
    {
        switch( Renderer::get_api() )
        {
        case Renderer_API::API::None:
            BR_ASSERT( false, "Renderer_API::None is not currently supported!" );
            return nullptr;
        case Renderer_API::API::OpenGL:
            return create_ref<OpenGL_Vertex_Array>();
        }

        return nullptr;
    }
}