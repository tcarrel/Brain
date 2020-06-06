#pragma once



#include "brain.h"




class Example_Layer : public Brain::Layer
{
public:
    Example_Layer( void );
    virtual ~Example_Layer( void ) = default;

    void on_attach( void ) override;
    void on_detach( void ) override;

    void on_update( Brain::Time_Step ts ) override;
    void on_imgui_render() override;
    void on_event( Brain::Event& e ) override;


private:
    Brain::Shader_Library shader_lib_;

    Brain::Ref<Brain::Shader> shader_;
    Brain::Ref<Brain::Vertex_Array> vertex_array_;

    Brain::Ref<Brain::Shader> flat_color_shader_, texture_shader_;
    Brain::Ref<Brain::Vertex_Array> square_vertex_array_;

    Brain::Ref<Brain::Texture_2D> texture_, lina_;


    Brain::Orthographic_Camera_Controller camera_controller_;

    glm::vec3 square_color_{ 0.2f, 0.3f, 0.8f };
};
