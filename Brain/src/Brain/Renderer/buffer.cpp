#include "br.pch.h"
#include "Brain/Renderer/buffer.h"

#include<algorithm>

#include "Brain/Renderer/renderer.h"
#include<Platform/OpenGL/opengl_buffer.h>



namespace Brain
{
// //////////////////////////////////////////////////////////////////////////////////
// Vertex
// //////////////////////////////////////////////////////////////////////////////////



    Ref<Vertex_Buffer> Vertex_Buffer::create( float* vertices, uint32_t size )
    {
        switch( Renderer::get_api() )
        {
        case Renderer_API::API::None:
            BR_CORE_ASSERT( false, "Renderer_API::None is currently not supportsd." );
            return nullptr;

        case Renderer_API::API::OpenGL:
            return create_ref<OpenGL_Vertex_Buffer>( vertices, size );
        }

        BR_CORE_ASSERT( false, "Renderer_API::?Unknown" );
        return nullptr;
    }



// //////////////////////////////////////////////////////////////////////////////////
// Index
// //////////////////////////////////////////////////////////////////////////////////



    Ref<Index_Buffer> Index_Buffer::create( uint32_t* indices, uint32_t size )
    {
        switch( Renderer::get_api() )
        {
        case Renderer_API::API::None:
            BR_CORE_ASSERT( false, "Renderer_API::None is currently not supportsd." );
            return nullptr;

        case Renderer_API::API::OpenGL:
            return create_ref<OpenGL_Index_Buffer>( indices, size );
        }

        BR_CORE_ASSERT( false, "Renderer_API::?Unknown" );
        return nullptr;
    }



    Buffer_Layout& Buffer_Layout::operator=( Buffer_Layout&& other ) noexcept
    {
        if( *this != other )
        {
            std::swap( *this, other );
        }
        return *this;
    }



    std::vector<Buffer_Element>::iterator Buffer_Layout::begin() noexcept
    {
        return elements_.begin();
    }



    std::vector<Buffer_Element>::iterator Buffer_Layout::end() noexcept
    {
        return elements_.end();
    }

    std::vector<Buffer_Element>::const_iterator Buffer_Layout::begin() const noexcept
    {
        return elements_.begin();
    }

    std::vector<Buffer_Element>::const_iterator Buffer_Layout::end() const noexcept
    {
        return elements_.end();
    }



    Buffer_Element& Buffer_Element::operator=( Buffer_Element&& other ) noexcept
    {
        if( *this != other )
        {
            std::swap( *this, other );
        }
        return *this;
    }
}