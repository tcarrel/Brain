#pragma once



#include<memory>
#include "Brain/Renderer/renderer_api.h"
#include "Brain/Renderer/vertex_array.h"



namespace Brain
{
    class Render_Command
    {
    public:
        static void init( void )
        {
            renderer_api_->init();
        }



        static void set_clear_color( const glm::vec4& color )
        {
            renderer_api_->set_clear_color( color );
        }



        static void set_viewport( uint32_t x, uint32_t y, uint32_t w, uint32_t h )
        {
            renderer_api_->set_viewport( x, y, w, h );
        }



        static void clear( void )
        {
            renderer_api_->clear();
        }



        void static draw_indexed( const Ref<Vertex_Array>& vert_array )
        {
            renderer_api_->draw_indexed( vert_array );
        }

    private:
        static Scope<Renderer_API> renderer_api_;
    };
}