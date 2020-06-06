#include "br.pch.h"
#include "Platform/OpenGL/opengl_vertex_array.h"



#include<glad/glad.h>



namespace Brain
{
    static GLenum shader_data_type_to_OpenGL_base_type( Shader_Data_Type type )
    {
        switch( type )
        {
        case Shader_Data_Type::Float:  [[fallthrough]];
        case Shader_Data_Type::Float2: [[fallthrough]];
        case Shader_Data_Type::Float3: [[fallthrough]];
        case Shader_Data_Type::Float4: [[fallthrough]];
        case Shader_Data_Type::Mat3:   [[fallthrough]];
        case Shader_Data_Type::Mat4:   return GL_FLOAT;
        case Shader_Data_Type::Int:    [[fallthrough]];
        case Shader_Data_Type::Int2:   [[fallthrough]];
        case Shader_Data_Type::Int3:   [[fallthrough]];
        case Shader_Data_Type::Int4:   return GL_INT;
        case Shader_Data_Type::Bool:   return GL_BOOL;
        default:
            BR_CORE_ASSERT( false, "Unkown Shader Data Type." );
            return 0;
        }
    }



    OpenGL_Vertex_Array::OpenGL_Vertex_Array( void )
    {
        BR_PROFILE_FUNCTION();

        glCreateVertexArrays( 1, &renderer_id_ );
    }



    OpenGL_Vertex_Array::~OpenGL_Vertex_Array( void )
    {
        BR_PROFILE_FUNCTION();

        glDeleteVertexArrays( 1, &renderer_id_ );
    }



    void OpenGL_Vertex_Array::bind( void ) const
    {
        BR_PROFILE_FUNCTION();
        glBindVertexArray( renderer_id_ );
    }



    void OpenGL_Vertex_Array::unbind( void ) const
    {
        BR_PROFILE_FUNCTION();

        glBindVertexArray( 0 );
    }



    void OpenGL_Vertex_Array::add_vertex_buffer( const Ref<Vertex_Buffer>& vertex_buffer )
    {
        BR_PROFILE_FUNCTION();

        BR_CORE_ASSERT( vertex_buffer->get_layout().elements.size(), "Vertex buffer has no layout." );

        glBindVertexArray( renderer_id_ );
        vertex_buffer->bind();

        uint32_t index{ 0 };
        const auto& layout = vertex_buffer->get_layout();
        for( const auto& element : layout )
        {
            glEnableVertexAttribArray( index );
            glVertexAttribPointer(
                index,
                element.component_count(),
                shader_data_type_to_OpenGL_base_type( element.type ),
                element.normalized ? GL_TRUE : GL_FALSE,
                layout.stride,
                element.offset_ptr() );
            ++index;
        }
        vertex_buffers_.push_back( vertex_buffer );
    }



    void OpenGL_Vertex_Array::set_index_buffer( const Ref<Index_Buffer>& index_buffer )
    {
        BR_PROFILE_FUNCTION();

        glBindVertexArray( renderer_id_ );
        index_buffer->bind();

        index_buffer_ = index_buffer;
    }



    const std::vector<Ref<Vertex_Buffer>>& OpenGL_Vertex_Array::vertex_buffers( void ) const
    {
        return vertex_buffers_;
    }



    const Ref<Index_Buffer>& OpenGL_Vertex_Array::index_buffer( void ) const
    {
        return index_buffer_;
    }
}