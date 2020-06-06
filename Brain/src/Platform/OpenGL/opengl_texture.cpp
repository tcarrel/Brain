#include "br.pch.h"



#include<stb_image.h>



#include "Platform/OpenGL/opengl_texture.h"



namespace Brain
{
    OpenGL_Texture_2D::OpenGL_Texture_2D( uint32_t width, uint32_t height )
        :
        width_( width ),
        height_( height ),
        path_{ "NONE" }
    {
        BR_PROFILE_FUNCTION();

        glCreateTextures( GL_TEXTURE_2D, 1, &texture_id_ );
        glTextureStorage2D( texture_id_, 1, internal_fmt_, width_, height_ );

        glTextureParameteri( texture_id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTextureParameteri( texture_id_, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

        glTextureParameteri( texture_id_, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTextureParameteri( texture_id_, GL_TEXTURE_WRAP_T, GL_REPEAT );

    }



    OpenGL_Texture_2D::OpenGL_Texture_2D( const std::string& path )
        :
        path_( path )
    {
        BR_PROFILE_FUNCTION();

        int width, height, channels;
        stbi_set_flip_vertically_on_load( static_cast<int>( true ) );
        stbi_uc* data{ nullptr };
        {
            BR_PROFILE_SCOPE( "stbi_load : OpenGL_Texture_2D::OpenGL_Texture_2D( const std::string& )" );
            data = stbi_load( path.c_str(), &width, &height, &channels, 0 );
        }
        BR_CORE_ASSERT( data, "Failed to load image '{0}'.", path );

        width_ = static_cast<uint32_t>( width );
        height_ = static_cast<uint32_t>( height );

        uint32_t bpp{ 4U };
        if( channels == 3 )
        {
            internal_fmt_ = GL_RGB8;
            data_fmt_ = GL_RGB;
            bpp = 3U;
        }

        BR_ASSERT( internal_fmt_ & data_fmt_, "Image format not supported." );

        glCreateTextures( GL_TEXTURE_2D, 1, &texture_id_ );
        glTextureStorage2D( texture_id_, 1, internal_fmt_, width_, height_ );

        glTextureParameteri( texture_id_, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTextureParameteri( texture_id_, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

        glTextureParameteri( texture_id_, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTextureParameteri( texture_id_, GL_TEXTURE_WRAP_T, GL_REPEAT );

        set_data( data, width * height * bpp );

        stbi_image_free( data );
    }



    uint32_t OpenGL_Texture_2D::width( void ) const noexcept
    {
        return width_;
    }



    uint32_t OpenGL_Texture_2D::height( void ) const noexcept
    {
        return height_;
    }



    void OpenGL_Texture_2D::set_data( void* data, [[maybe_unused]]uint32_t size )
    {
        BR_PROFILE_FUNCTION();

        uint32_t bpp{ 4 };
        if( data_fmt_ == GL_RGB )
        {
            bpp = 3U;
        }

        BR_CORE_ASSERT( size == width_ * height_ * bpp, "Data must fill the entire texture." );
        glTextureSubImage2D( texture_id_, 0, 0, 0, width_, height_, data_fmt_, GL_UNSIGNED_BYTE, data );
    }



    OpenGL_Texture_2D::~OpenGL_Texture_2D( void )
    {
        BR_PROFILE_FUNCTION();

        glDeleteTextures( 1, &texture_id_ );
    }



    void OpenGL_Texture_2D::bind( uint32_t slot ) const noexcept
    {
        BR_PROFILE_FUNCTION();

        glBindTextureUnit( slot, texture_id_ );
    }
}