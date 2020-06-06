#pragma once



#include<string>
#include "Brain/Core/nucleus.h"



namespace Brain
{
    class Texture
    {
    public:
        virtual ~Texture( void ) = default;

        virtual uint32_t width( void ) const noexcept = 0;
        virtual uint32_t height( void ) const noexcept = 0;

        virtual void set_data( void* data, uint32_t size ) = 0;

        virtual void bind( uint32_t slot = 0 ) const noexcept = 0;
    };



    class Texture_2D : public Texture
    {
    public:
        static Ref<Texture_2D> create( uint32_t width, uint32_t height );
        static Ref<Texture_2D> create( const std::string& path );
    };
}