#pragma once



#include "Brain/Renderer/buffer.h"



namespace Brain
{
    class OpenGL_Vertex_Buffer : public Vertex_Buffer
    {
    public:
        OpenGL_Vertex_Buffer( float* vertices, uint32_t size );
        ~OpenGL_Vertex_Buffer( void );

        void bind( void ) const override;
        void unbind( void ) const override;

        const Buffer_Layout& get_layout( void ) const override;
        void set_layout( const Buffer_Layout& layout ) override;

    private:
        uint32_t renderer_id_;
        Buffer_Layout layout_;
    };




    class OpenGL_Index_Buffer : public Index_Buffer
    {
    public:
        OpenGL_Index_Buffer( uint32_t* indices, uint32_t count );
        ~OpenGL_Index_Buffer( void );

        void bind( void ) const override;
        void unbind( void ) const override;

        uint32_t get_count( void ) const override;

    private: 
        uint32_t renderer_id_{ 0 };
        uint32_t count_{ 0 };
    };
}
