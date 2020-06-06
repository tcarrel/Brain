#include "2d.h"
#include<imgui/imgui.h>



#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>



Sandbox_2D::Sandbox_2D()
    :
    Layer( "Sandbox 2D" ),
    camera_controller_( 1280.0f / 720.0f, true )
{}



void Sandbox_2D::on_attach( void )
{
    BR_PROFILE_FUNCTION();

    checkerboard_ = Brain::Texture_2D::create( "assets\\textures\\checkerboard.png" );
}



void Sandbox_2D::on_detach( void )
{
    BR_PROFILE_FUNCTION();
}



void Sandbox_2D::on_update( Brain::Time_Step ts )
{
    BR_PROFILE_FUNCTION();

    //Update
        camera_controller_.on_update( ts );

    //Render
    {
        BR_PROFILE_SCOPE( "pre-renderer" );
        Brain::Render_Command::set_clear_color( { 37.0 / 255.0, 37.0 / 255.0, 37.0 / 255.0, 1.0 } );
        Brain::Render_Command::clear();
    }

    {
        BR_PROFILE_SCOPE( "render draw" );
        Brain::Renderer_2D::begin_scene( camera_controller_.get_camera() );

        Brain::Renderer_2D::draw_rotated_quad( { 0.5f, -0.5f }, { 0.5f,  0.75f }, -3.1415927f / 12.0f, { 0.8f, 0.2f, 0.3f, 1.0f } );
        Brain::Renderer_2D::draw_quad( { -1.0f, 0 }, { 0.8f,  0.8f }, square_color_ );
        Brain::Renderer_2D::draw_quad( { 0, 0, 0.0f }, { 10.0f, 10.0f }, checkerboard_, 10, { 0, 1.0f, 0.1f, 1.0f } );

        Brain::Renderer_2D::end_scene();
    }
}



void Sandbox_2D::on_imgui_render( void )
{
    BR_PROFILE_FUNCTION();

    ImGui::Begin( "Settin's" );
    ImGui::ColorEdit4( "Square Color", glm::value_ptr( square_color_ ) );
    ImGui::End();
}



void Sandbox_2D::on_event( Brain::Event & e )
{
    camera_controller_.on_event( e );
}
