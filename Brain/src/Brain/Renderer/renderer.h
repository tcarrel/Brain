#pragma once


#include "Brain/Renderer/shader.h"
#include "Brain/Renderer/render_command.h"
#include "Brain/Renderer/orthographic_camera.h"



namespace Brain
{

    class Renderer
    {
    public:
        static void init( void );
        static void shutdown( void );
        static void on_window_resize( uint32_t width, uint32_t height );

        static void begin_scene( Orthographic_Camera& camera );
        static void end_scene( void );

        static void submit( const Ref<Shader>& shader, const Ref<Vertex_Array>& vert_array, const glm::mat4& transform = glm::mat4( 1.0f ) );

        static Renderer_API::API get_api( void );

    private:

        struct Scene_Data
        {
            glm::mat4 view_projection{ glm::mat4(1.0) };
        };

        static Scope<Scene_Data> scene_data_;
    };
}