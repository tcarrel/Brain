#pragma once



#include "Brain/Core/input.h"



namespace Brain
{
    class Windows_Input : public Input
    {
    protected:
        bool is_key_pressed_impl( Keycode keycode ) override;
        bool is_mouse_button_pressed_impl( Mousecode button ) override;
        std::pair<float, float> mouse_position_impl( void ) override;
        void mouse_position_impl( double& x, double& y ) override;
        double mouse_x_impl( void ) override;
        double mouse_y_impl( void ) override;
    };
}