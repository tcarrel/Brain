#include "br.pch.h"
#include "Brain/Renderer/orthographic_camera.h"



#include<glm/gtc/matrix_transform.hpp>



namespace Brain
{
    Orthographic_Camera::Orthographic_Camera( float left, float right, float bottom, float top )
        :
        projection_( glm::ortho( left, right, bottom, top, -1.0f, 1.0f ) )
    {

        BR_PROFILE_FUNCTION();

        calculate_vp_matrix();
    }



    void Orthographic_Camera::set_projection( float left, float right, float bottom, float top )
    {
        BR_PROFILE_FUNCTION();

        projection_ = glm::ortho( left, right, bottom, top, -1.0f, 1.0f );
        calculate_vp_matrix();
    }



    void Orthographic_Camera::set_position( const glm::vec3& pos )
    {
        position_ = pos;
        recalculate_view_matrix();
    }



    void Orthographic_Camera::set_rotation( const float& rotz )
    {
        rotation_ = rotz;
        recalculate_view_matrix();
    }



    void Orthographic_Camera::calculate_vp_matrix( void )
    {
        view_projection_ = projection_ * view_;
    }



    void Orthographic_Camera::recalculate_view_matrix( void )
    {
        BR_PROFILE_FUNCTION();

        auto transform =
            glm::translate( glm::mat4( 1.0f ), position_ ) *
            glm::rotate( glm::mat4( 1.0f ), glm::radians( static_cast<float>( rotation_ ) ), glm::vec3( 0, 0, 1.0f ) );

        view_ = glm::inverse( transform );
        calculate_vp_matrix();
    }
}