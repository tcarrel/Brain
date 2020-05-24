


#include "br.pch.h"
#include "imgui.layer.h"



#include "imgui.h"
#include "Brain/Platform/OpenGL/imgui_opengl_renderer.h"



#include "Brain/application.h"



// Temp
#include <glad/glad.h>
#include <GLFW/glfw3.h>



namespace Brain
{
    imgui_Layer::imgui_Layer( const std::string& name )
        :
        Layer( name )
    {}



    imgui_Layer::~imgui_Layer( void )
    {}



    void imgui_Layer::on_attach( void )
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        // Temporary
        io.KeyMap[ ImGuiKey_Tab ] = GLFW_KEY_TAB;
        io.KeyMap[ ImGuiKey_LeftArrow ] = GLFW_KEY_LEFT;
        io.KeyMap[ ImGuiKey_RightArrow ] = GLFW_KEY_RIGHT;
        io.KeyMap[ ImGuiKey_UpArrow ] = GLFW_KEY_UP;
        io.KeyMap[ ImGuiKey_DownArrow ] = GLFW_KEY_DOWN;
        io.KeyMap[ ImGuiKey_PageUp ] = GLFW_KEY_PAGE_UP;
        io.KeyMap[ ImGuiKey_PageDown ] = GLFW_KEY_PAGE_DOWN;
        io.KeyMap[ ImGuiKey_Home ] = GLFW_KEY_HOME;
        io.KeyMap[ ImGuiKey_End ] = GLFW_KEY_END;
        io.KeyMap[ ImGuiKey_Insert ] = GLFW_KEY_INSERT;
        io.KeyMap[ ImGuiKey_Delete ] = GLFW_KEY_DELETE;
        io.KeyMap[ ImGuiKey_Backspace ] = GLFW_KEY_BACKSPACE;
        io.KeyMap[ ImGuiKey_Space ] = GLFW_KEY_SPACE;
        io.KeyMap[ ImGuiKey_Enter ] = GLFW_KEY_ENTER;
        io.KeyMap[ ImGuiKey_Escape ] = GLFW_KEY_ESCAPE;
        io.KeyMap[ ImGuiKey_KeyPadEnter ] = GLFW_KEY_KP_ENTER;
        io.KeyMap[ ImGuiKey_A ] = GLFW_KEY_A;
        io.KeyMap[ ImGuiKey_C ] = GLFW_KEY_C;
        io.KeyMap[ ImGuiKey_V ] = GLFW_KEY_V;
        io.KeyMap[ ImGuiKey_X ] = GLFW_KEY_X;
        io.KeyMap[ ImGuiKey_Y ] = GLFW_KEY_Y;
        io.KeyMap[ ImGuiKey_Z ] = GLFW_KEY_Z;

        ImGui_ImplOpenGL3_Init( "#version 450" );
    }



    void imgui_Layer::on_detach( void )
    {}



    void imgui_Layer::on_update( void )
    {

        auto& io = ImGui::GetIO();

        auto& app = Application::get();
        io.DisplaySize = ImVec2( app.window().width(), app.window().height() );

        auto time = static_cast<float>( glfwGetTime() );
        io.DeltaTime = time_ > 0.0f ? ( time - time_ ) : ( 1.0f / 60.0f );
        time_ = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show{ true };
        ImGui::ShowDemoWindow( &show );

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );
    }



    void imgui_Layer::on_event( Event& e )
    {
        Event_Dispatch dispatcher( e );
        dispatcher.dispatch<Mouse_Button_Press_Event>( BR_BIND_EVENT_FUNCTION( imgui_Layer::on_mouse_button_pressed ) );
        dispatcher.dispatch<Mouse_Button_Release_Event>( BR_BIND_EVENT_FUNCTION( imgui_Layer::on_mouse_button_released ) );
        dispatcher.dispatch<Mouse_Move_Event>( BR_BIND_EVENT_FUNCTION( imgui_Layer::on_mouse_move ) );
        dispatcher.dispatch<Mouse_Scroll_Event>( BR_BIND_EVENT_FUNCTION( imgui_Layer::on_mouse_scroll ) );
        dispatcher.dispatch<Key_Press_Event>( BR_BIND_EVENT_FUNCTION( imgui_Layer::on_key_pressed ) );
        dispatcher.dispatch<Key_Release_Event>( BR_BIND_EVENT_FUNCTION( imgui_Layer::on_key_released ) );
        dispatcher.dispatch<Typing_Event>( BR_BIND_EVENT_FUNCTION( imgui_Layer::on_typing ) );
        dispatcher.dispatch<Window_Resize_Event>( BR_BIND_EVENT_FUNCTION( imgui_Layer::on_window_resize ) );
    }



    bool imgui_Layer::on_mouse_button_pressed( Mouse_Button_Press_Event& e )
    {
        auto& io = ImGui::GetIO();
        io.MouseDown[ e.button ] = true;

        return false;
    }



    bool imgui_Layer::on_mouse_button_released( Mouse_Button_Release_Event& e )
    {
        auto& io = ImGui::GetIO();
        io.MouseDown[ e.button ] = false;

        return false;
    }



    bool imgui_Layer::on_mouse_move( Mouse_Move_Event& e )
    {
        auto& io = ImGui::GetIO();
        io.MousePos = ImVec2( e.x, e.y );

        return false;
    }



    bool imgui_Layer::on_mouse_scroll( Mouse_Scroll_Event& e )
    {
        auto& io = ImGui::GetIO();
        io.MouseWheel += e.y_offset;
        io.MouseWheelH += e.x_offset;

        return false;
    }



    bool imgui_Layer::on_key_pressed( Key_Press_Event& e )
    {
        auto& io = ImGui::GetIO();
        io.KeysDown[ e.keycode ] = true;

        return false;
    }



    bool imgui_Layer::on_key_released( Key_Release_Event& e )
    {
        auto& io = ImGui::GetIO();
        io.KeysDown[ e.keycode ] = false;

        io.KeyCtrl = io.KeysDown[ GLFW_KEY_LEFT_CONTROL ] || io.KeysDown[ GLFW_KEY_RIGHT_CONTROL ];
        io.KeyAlt = io.KeysDown[ GLFW_KEY_LEFT_ALT ] || io.KeysDown[ GLFW_KEY_RIGHT_ALT ];
        io.KeyShift = io.KeysDown[ GLFW_KEY_LEFT_SHIFT ] || io.KeysDown[ GLFW_KEY_RIGHT_SHIFT ];
        io.KeySuper = io.KeysDown[ GLFW_KEY_LEFT_SUPER ] || io.KeysDown[ GLFW_KEY_RIGHT_SUPER ];

        return false;
    }



    bool imgui_Layer::on_typing( Typing_Event& e )
    {
        auto& io = ImGui::GetIO();
        auto keycode = e.keycode;
        if( keycode > 0 && keycode < 0x10000 )
        {
            io.AddInputCharacter( static_cast<unsigned short>( keycode ) );
        }

        return false;
    }



    bool imgui_Layer::on_window_resize( Window_Resize_Event& e )
    {
        auto& io = ImGui::GetIO();
        io.DisplaySize = ImVec2( e.w, e.h );
        io.DisplayFramebufferScale = ImVec2( 1.0, 1.0 );
        glViewport( 0, 0, e.w, e.h );

        return false;
    }
}