#pragma once



#include "Brain/Core/nucleus.h"
#include "Brain/Core/keycodes.h"
#include "Brain/Core/mouse_codes.h"



namespace Brain
{
    class Input
    {
    public:
        static bool is_key_pressed( Keycode kc )
        {
            return instance_->is_key_pressed_impl( kc );
        }

        static bool is_mouse_button_pressed( Mousecode button )
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

        static Scope<Input> create( void );
    protected:
        Input() = default;
        virtual bool is_key_pressed_impl( Keycode keycode ) = 0;
        virtual bool is_mouse_button_pressed_impl( Mousecode button ) = 0;
        virtual std::pair<float, float> mouse_position_impl( void ) = 0;
        virtual void mouse_position_impl( double& x, double& y ) = 0;
        virtual double mouse_x_impl( void ) = 0;
        virtual double mouse_y_impl( void ) = 0;

    private:
        static Scope<Input> instance_;
    };
}