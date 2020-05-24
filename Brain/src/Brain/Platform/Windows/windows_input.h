#pragma once



#include "Brain/input.h"



namespace Brain
{
    class Windows_Input : public Input
    {
    protected:
        bool is_key_pressed_impl( int keycode ) override;
        bool is_mouse_button_pressed_impl( int button ) override;
        std::pair<double, double> mouse_position_impl( void ) override;
        void mouse_position_impl( double& x, double& y ) override;
        double mouse_x_impl( void ) override;
        double mouse_y_impl( void ) override;
    };
}