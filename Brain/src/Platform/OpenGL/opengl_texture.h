#pragma once



#include "Brain/Renderer/texture.h"
#include<glad/glad.h>



namespace Brain
{
    class OpenGL_Texture_2D : public Texture_2D
    {
    public:
        OpenGL_Texture_2D( uint32_t width, uint32_t height );
        OpenGL_Texture_2D( const std::string& path );
        ~OpenGL_Texture_2D( void );

        uint32_t width( void ) const noexcept override;
        uint32_t height( void ) const noexcept override;
        
        void set_data( void* data, uint32_t size ) override;

        void bind( uint32_t slot = 0 ) const noexcept override;

    private:
        const std::string path_;

        uint32_t width_, height_;
        uint32_t texture_id_;
        GLenum internal_fmt_{ GL_RGBA8 };
        GLenum data_fmt_{ GL_RGBA };
    };
}
