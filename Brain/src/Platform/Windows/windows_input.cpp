#include "br.pch.h"
#include "Platform/Windows/windows_input.h"



#include "Brain/Core/application.h"
#include <GLFW/glfw3.h>



namespace Brain
{
    bool Windows_Input::is_key_pressed_impl( Keycode keycode )
    {
        auto window = static_cast<GLFWwindow*>( Application::get().window().get_native_window() );
        auto state = glfwGetKey( window, static_cast<int32_t>( keycode ) );

        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }



    bool Windows_Input::is_mouse_button_pressed_impl( Mousecode button )
    {
        auto window = static_cast<GLFWwindow*>( Application::get().window().get_native_window() );
        auto state = glfwGetMouseButton( window, static_cast<int32_t>( button ) );

        return state == GLFW_PRESS;
    }



    std::pair<float, float> Windows_Input::mouse_position_impl( void )
    {
        auto window = static_cast<GLFWwindow*>( Application::get().window().get_native_window() );
        double x, y;
        glfwGetCursorPos( window, &x, &y );

        return { static_cast<float>( x ), static_cast<float>( y ) };
    }



    void Windows_Input::mouse_position_impl( double& x, double& y )
    {
        auto window = static_cast<GLFWwindow*>( Application::get().window().get_native_window() );
        glfwGetCursorPos( window, &x, &y );
    }



    double Windows_Input::mouse_x_impl( void )
    {
        auto [x, y] = mouse_position_impl();
        return x;
    }



    double Windows_Input::mouse_y_impl( void )
    {
        auto [x, y] = mouse_position_impl();
        return y;
    }
}