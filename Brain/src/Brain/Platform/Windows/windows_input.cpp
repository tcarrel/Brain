


#include "br.pch.h"
#include "windows_input.h"



#include "Brain/application.h"
#include <GLFW/glfw3.h>



namespace Brain
{
    Input* Input::instance_{ new Windows_Input };



    bool Windows_Input::is_key_pressed_impl( int keycode )
    {
        auto window = static_cast<GLFWwindow*>( Application::get().window().get_native_window() );
        auto state = glfwGetKey( window, keycode );

        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }



    bool Windows_Input::is_mouse_button_pressed_impl( int button )
    {
        auto window = static_cast<GLFWwindow*>( Application::get().window().get_native_window() );
        auto state = glfwGetMouseButton( window, button );

        return state == GLFW_PRESS;
    }



    std::pair<double, double> Windows_Input::mouse_position_impl( void )
    {
        auto window = static_cast<GLFWwindow*>( Application::get().window().get_native_window() );
        double x, y;
        glfwGetCursorPos( window, &x, &y );

        return { x, y };
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