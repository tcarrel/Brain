#include "br.pch.h"
#include "Platform/OpenGL/opengl_buffer.h"



#include<glad/glad.h>



namespace Brain
{
    OpenGL_Vertex_Buffer::OpenGL_Vertex_Buffer( float* vertices, uint32_t size )
    {
        BR_PROFILE_FUNCTION();

        glCreateBuffers( 1, &renderer_id_ );
        glBindBuffer( GL_ARRAY_BUFFER, renderer_id_ );
        glBufferData( GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW );
    }



    OpenGL_Vertex_Buffer::~OpenGL_Vertex_Buffer( void )
    {
        BR_PROFILE_FUNCTION();

        glDeleteBuffers( 1, &renderer_id_ );
    }



    void OpenGL_Vertex_Buffer::bind( void ) const
    {
        BR_PROFILE_FUNCTION();

        glBindBuffer( GL_ARRAY_BUFFER, renderer_id_ );
    }



    void OpenGL_Vertex_Buffer::unbind( void ) const
    {
        BR_PROFILE_FUNCTION();

        glBindBuffer( GL_ARRAY_BUFFER, 0 );
    }



    const Buffer_Layout& OpenGL_Vertex_Buffer::get_layout( void ) const
    {
        return layout_;
    }

    void OpenGL_Vertex_Buffer::set_layout( const Buffer_Layout& layout )
    {
        layout_ = layout;
    }






    OpenGL_Index_Buffer::OpenGL_Index_Buffer( uint32_t* indices, uint32_t count )
        :
        count_( count )
    {
        BR_PROFILE_FUNCTION();

        glCreateBuffers( 1, &renderer_id_ );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, renderer_id_ );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, count * sizeof( uint32_t ), indices, GL_STATIC_DRAW );
    }



    OpenGL_Index_Buffer::~OpenGL_Index_Buffer( void )
    {
        BR_PROFILE_FUNCTION();

        glDeleteBuffers( 1, &renderer_id_ );
    }



    void OpenGL_Index_Buffer::bind( void ) const
    {
        BR_PROFILE_FUNCTION();

        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, renderer_id_ );
    }



    void OpenGL_Index_Buffer::unbind( void ) const
    {
        BR_PROFILE_FUNCTION();

        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
    }



    uint32_t OpenGL_Index_Buffer::get_count( void ) const
    {
        return count_;
    }
}