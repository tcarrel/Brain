#pragma once



#include "Brain/nucleus.h"



namespace Brain
{
    class BRAIN_API Input
    {
    public:
        static bool is_key_pressed( int keycode )
        {
            return instance_->is_key_pressed_impl( keycode );
        }

        static bool is_mouse_button_pressed( int button )
        {
            return instance_->is_mouse_button_pressed_impl( button );
        }

        static std::pair<double, double> mouse_position( void )
        {
            return instance_->mouse_position_impl();
        }

        static void mouse_position( double& x, double& y )
        {
            return instance_->mouse_position_impl( x, y );
        }

        static double mouse_x( void )
        {
            return instance_->mouse_x_impl();
        }

        static double mouse_y( void )
        {
            return instance_->mouse_y_impl();
        }

    protected:
        virtual bool is_key_pressed_impl( int keycode ) = 0;
        virtual bool is_mouse_button_pressed_impl( int button ) = 0;
        virtual std::pair<double, double> mouse_position_impl( void ) = 0;
        virtual void mouse_position_impl( double& x, double& y ) = 0;
        virtual double mouse_x_impl( void ) = 0;
        virtual double mouse_y_impl( void ) = 0;

    private:
        static Input* instance_;
    };
}