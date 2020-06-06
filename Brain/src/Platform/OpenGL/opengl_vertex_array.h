#pragma once



#include<vector>
#include<memory>



#include "Brain/Renderer/vertex_array.h"



namespace Brain
{
    class OpenGL_Vertex_Array : public Vertex_Array
    {
    public:
        OpenGL_Vertex_Array( void );
        ~OpenGL_Vertex_Array( void );

        void bind( void ) const override;
        void unbind( void ) const override;

        void add_vertex_buffer( const Ref<Vertex_Buffer>& vertex_buffer ) override;
        void set_index_buffer( const Ref<Index_Buffer>& index_buffer ) override;

        const std::vector<Ref<Vertex_Buffer>>& vertex_buffers( void ) const override;
        const Ref<Index_Buffer>& index_buffer( void ) const override;

    private:
        std::vector<Ref<Vertex_Buffer>> vertex_buffers_;
        Ref<Index_Buffer> index_buffer_;

        uint32_t renderer_id_{ 0 };
    };
}