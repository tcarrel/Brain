#pragma once



#include "brain.h"



class Sandbox_2D : public Brain::Layer 
{
public:
    Sandbox_2D();
    virtual ~Sandbox_2D( void ) = default;

    void on_attach( void ) override;
    void on_detach( void ) override;
    void on_update( Brain::Time_Step ts ) override;
    void on_imgui_render( void ) override;
    void on_event( Brain::Event& e ) override;



private:

    Brain::Orthographic_Camera_Controller camera_controller_;

    // Temp
    Brain::Ref<Brain::Vertex_Array> vertex_array_;
    Brain::Ref<Brain::Shader> flat_color_shader_;

    Brain::Ref<Brain::Texture_2D> checkerboard_;

    glm::vec4 square_color_{ 0.2f, 0.3f, 0.8f, 1.0f };
};
