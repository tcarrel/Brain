#pragma once



#include <glm/glm.hpp>



#include "Brain/Renderer/vertex_array.h"



namespace Brain
{
    class Renderer_API
    {
    public:
        enum class API
        {
            None = 0,
            OpenGL
        };
        virtual void init( void ) = 0;
        virtual void set_viewport( uint32_t x, uint32_t y, uint32_t w, uint32_t h ) = 0;

        virtual void set_clear_color( const glm::vec4& color ) = 0;
        virtual void clear( void ) = 0;
        
        virtual void draw_indexed( const Ref<Vertex_Array>& vert_array ) = 0;

        static API get_api( void ) { return api_; };

        static Scope<Renderer_API> create( void );

    private:
        static API api_;
    };
}