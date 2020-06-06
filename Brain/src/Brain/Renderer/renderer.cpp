#include "br.pch.h"
#include "Brain/Renderer/renderer.h"



#include "Brain/Renderer/renderer_2d.h"



namespace Brain
{
    Scope<Renderer::Scene_Data> Renderer::scene_data_ = create_scope<Renderer::Scene_Data>();



    void Renderer::init( void )
    {
        BR_PROFILE_FUNCTION();

        Render_Command::init();
        Renderer_2D::init();
    }



    void Renderer::shutdown( void )
    {
        Renderer_2D::shutdown();
    }



    void shutdown( void )
    {
        Renderer_2D::shutdown();
    }



    void Renderer::on_window_resize( uint32_t width, uint32_t height )
    {
        Render_Command::set_viewport( 0, 0, width, height );
    }



    void Renderer::begin_scene( Orthographic_Camera& camera )
    {
        scene_data_->view_projection = camera.vp;
    }



    void Renderer::end_scene( void )
    {}



    void Renderer::submit(
        const Ref<Shader>& shader,
        const Ref<Vertex_Array>& vert_array,
        const glm::mat4& transform )
    {
        shader->bind();
        shader->set( "u_view_projection", scene_data_->view_projection );
        shader->set( "u_transform", transform );
        vert_array->bind();
        Render_Command::draw_indexed( vert_array );
    }



    Renderer_API::API Renderer::get_api( void )
    {
        return Renderer_API::get_api();
    }
}