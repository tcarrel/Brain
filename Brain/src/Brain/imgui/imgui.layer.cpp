


#include "br.pch.h"
#include "Brain/imgui/imgui.layer.h"



//#define IMGUI_IMPL_API
#include<examples/imgui_impl_glfw.h>
#include<examples/imgui_impl_opengl3.h>



#include "Brain/Core/application.h"



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
        BR_PROFILE_FUNCTION();

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        auto& io{ ImGui::GetIO() };
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        // Setup style
        ImGui::StyleColorsDark();

        auto& style{ ImGui::GetStyle() };
        if( io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable )
        {
            style.WindowRounding = 0.0f;
            style.Colors[ ImGuiCol_WindowBg ].w = 1.0f;
        }

        auto& app{ Application::get() };
        auto window{ static_cast<GLFWwindow*>( app.window().get_native_window() ) };

        ImGui_ImplGlfw_InitForOpenGL( window, true );
        ImGui_ImplOpenGL3_Init( "#version 450" );
    }



    void imgui_Layer::on_detach( void )
    {
        BR_PROFILE_FUNCTION();

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }



    void imgui_Layer::begin( void )
    {
        BR_PROFILE_FUNCTION();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }



    void imgui_Layer::end( void )
    {
        BR_PROFILE_FUNCTION();

        auto& io{ ImGui::GetIO() };
        auto& app{ Application::get() };

        io.DisplaySize = ImVec2( static_cast<float>( app.window().width() ), static_cast<float>( app.window().height() ) );

        // Rendering

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );

        if( io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable )
        {
            auto current_context_backup{ glfwGetCurrentContext() };
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent( current_context_backup );
        }
    }



}