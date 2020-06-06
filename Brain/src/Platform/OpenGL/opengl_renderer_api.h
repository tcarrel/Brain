#pragma once



#include "Brain/Renderer/renderer_api.h"



namespace Brain
{
    class OpenGL_Renderer_API : public Renderer_API
    {
    public:
        void init( void ) override;
        void set_viewport( uint32_t x, uint32_t y, uint32_t w, uint32_t h ) override;

        void set_clear_color( const glm::vec4& color ) override;
        void clear( void ) override;

        void draw_indexed( const Ref<Vertex_Array>& vert_array ) override;
    };
}
