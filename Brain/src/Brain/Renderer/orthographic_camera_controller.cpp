#include "br.pch.h"
#include "Brain/Renderer/orthographic_camera_controller.h"



namespace Brain
{
    Orthographic_Camera_Controller::Orthographic_Camera_Controller( float aspect_ratio, bool rotation_enable )
        :
        ALLOW_ROTATION_( rotation_enable ),
        aspect_ratio_( aspect_ratio ),
        camera_( -aspect_ratio_ * zoom_level_, aspect_ratio_* zoom_level_, -zoom_level_, zoom_level_ )
    {
        translation_speed_ = zoom_level_;
    }



    void Orthographic_Camera_Controller::on_update( Time_Step ts )
    {
        BR_PROFILE_FUNCTION();

        if( Input::is_key_pressed( Keycode::D ) )
        {
            position_.x += translation_speed_ * ts;
        }
        else if( Input::is_key_pressed( Keycode::A ) )
        {
            position_.x -= translation_speed_ * ts;
        }
        if( Input::is_key_pressed( Keycode::S ) )
        {
            position_.y -= translation_speed_ * ts;
        }
        else if( Input::is_key_pressed( Keycode::W ) )
        {
            position_.y += translation_speed_ * ts;
        }



        if( ALLOW_ROTATION_ )
        {
            if( Brain::Input::is_key_pressed( Keycode::Q ) )
            {
                rotation_ += rotation_speed_ * ts;
                if( rotation_ > 360.0f )
                {
                    rotation_ -= 360.0f;
                }
            }
            else if( Brain::Input::is_key_pressed( Keycode::E ) )
            {
                rotation_ -= rotation_speed_ * ts;
                if( rotation_ < 0.0f )
                {
                    rotation_ += 360.0f;
                }
            }
            camera_.set_rotation( rotation_ );
        }
        camera_.set_position( position_ );
    }



    void Orthographic_Camera_Controller::on_event( Event& e )
    {
        BR_PROFILE_FUNCTION();

        Event_Dispatch dispatcher( e );

        dispatcher.dispatch<Mouse_Scroll_Event>( BR_BIND_EVENT_FUNCTION( Orthographic_Camera_Controller::on_mouse_scrolled ) );
        dispatcher.dispatch<Window_Resize_Event>( BR_BIND_EVENT_FUNCTION( Orthographic_Camera_Controller::on_window_resize ) );
    }



    Orthographic_Camera& Orthographic_Camera_Controller::get_camera( void )
    {
        return camera_;
    }

    const Orthographic_Camera& Orthographic_Camera_Controller::get_camera( void ) const
    {
        return camera_;
    }



    bool Orthographic_Camera_Controller::on_mouse_scrolled( Mouse_Scroll_Event& e )
    {
        BR_PROFILE_FUNCTION();

        zoom_level_ -= ( e.y_offset * 0.25f );
        zoom_level_ = std::max( zoom_level_, 0.25f );
        translation_speed_ = zoom_level_;
        camera_.set_projection( -aspect_ratio_ * zoom_level_, aspect_ratio_ * zoom_level_, -zoom_level_, zoom_level_ );
        return false;
    }



    bool Orthographic_Camera_Controller::on_window_resize( Window_Resize_Event& e )
    {
        BR_PROFILE_FUNCTION();

        aspect_ratio_ = static_cast<float>( e.w ) / static_cast<float>( e.h );
        camera_.set_projection( -aspect_ratio_ * zoom_level_, aspect_ratio_ * zoom_level_, -zoom_level_, zoom_level_ );
        return false;
    }
}