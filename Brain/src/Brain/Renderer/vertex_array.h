#pragma once



#include "Brain/Renderer/buffer.h"
#include<memory>



namespace Brain
{
    class Vertex_Array
    {
    public:
        virtual ~Vertex_Array( void ) = default;

        virtual void bind( void ) const = 0;
        virtual void unbind( void ) const = 0;

        virtual void add_vertex_buffer( const Ref<Vertex_Buffer>& vertex_buffer ) = 0;
        virtual void set_index_buffer( const Ref<Index_Buffer>& index_buffer ) = 0;

        virtual const std::vector<Ref<Vertex_Buffer>>& vertex_buffers( void ) const = 0;
        virtual const Ref<Index_Buffer>& index_buffer( void ) const = 0;

        static Ref<Vertex_Array> create( void );
    };
}
