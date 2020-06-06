#include "example_layer.h"




#include<imgui/imgui.h>

#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>




Example_Layer::Example_Layer( void )
    :
    camera_controller_( 1280.0f / 720.0f, true ),
    Layer( "Example" )
{
    vertex_array_ = Brain::Vertex_Array::create();

    float verts[]
    {
        -0.5f,  -0.5f, 0.0f,     1.0f, 0.0f, 1.0f, 1.0f,
        0.5f,  -0.5f, 0.0f,     1.0f, 1.0f, 0.0f, 1.0f,
        0.0f,   0.5f, 0.0f,     0.0f, 1.0f, 1.0f, 1.0f
    };

    Brain::Ref<Brain::Vertex_Buffer> vertex_buffer{ Brain::Vertex_Buffer::create( verts, sizeof( verts ) ) };

    Brain::Buffer_Layout layout{ {
        { Brain::Shader_Data_Type::Float3, "a_position" },
        { Brain::Shader_Data_Type::Float4, "a_color" }
        } };
    vertex_buffer->set_layout( layout );
    vertex_array_->add_vertex_buffer( vertex_buffer );

    uint32_t indices[]{ 0, 1, 2 };
    Brain::Ref<Brain::Index_Buffer> index_buffer{ Brain::Index_Buffer::create( indices, sizeof( indices ) / sizeof( uint32_t ) ) };
    vertex_array_->set_index_buffer( index_buffer );

    std::string vert{
        R"(
#version 450 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec4 a_color;

uniform mat4 u_view_projection;
uniform mat4 u_transform;

out vec4 col;

void main()
{
    col = a_color;
    gl_Position = u_view_projection * u_transform * vec4(a_position, 1.0);
}

 )"
    };

    std::string frag{
        R"(
#version 450 core

in vec4 col;

out vec4 color;

void main()
{
    color = col;
}

 )"
    };

    shader_ = Brain::Shader::create( "triangle", vert, frag );

    float square[]{
        //xyz                  //uv
        -0.5f, -0.5f, 0.0f,    0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,    1.0f, 0.0f,
        0.5f,  0.5f, 0.0f,    1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f,    0.0f, 1.0f
    };

    square_vertex_array_ = Brain::Vertex_Array::create();

    Brain::Ref<Brain::Vertex_Buffer> g_vb{ Brain::Vertex_Buffer::create( square, sizeof( square ) ) };
    g_vb->set_layout( {
        { Brain::Shader_Data_Type::Float3, "a_position" },
                      { Brain::Shader_Data_Type::Float2, "a_texture_coordinate" }
                      } );
    square_vertex_array_->add_vertex_buffer( g_vb );

    uint32_t sq_indices[] = { 0, 1, 2, 2, 3, 0 };
    Brain::Ref<Brain::Index_Buffer> g_ib{ Brain::Index_Buffer::create( sq_indices, sizeof( sq_indices ) / sizeof( uint32_t ) ) };
    square_vertex_array_->set_index_buffer( g_ib );

    std::string flat_color_vert{
        R"(
#version 450 core

layout (location = 0) in vec3 a_position;

uniform mat4 u_view_projection;
uniform mat4 u_transform;

out vec3 v_position;

void main()
{
    gl_Position = u_view_projection * u_transform * vec4(a_position, 1.0);
}
 )"
    };
    std::string flat_color_frag{
        R"(
#version 450 core

uniform vec3 u_color;

out vec4 color;

void main()
{
    color = vec4(u_color, 1.0);
}
 )"
    };

    flat_color_shader_ = Brain::Shader::create( "flat", flat_color_vert, flat_color_frag );


    auto tex_shader = shader_lib_.load( "C:\\dev\\Brain\\Sandbox\\assets\\shaders\\texture.glsl" );

    //shader_lib_.load( "assets\\textures\\checkerboard.png" );

    texture_ = Brain::Texture_2D::create( "assets\\textures\\checkerboard.png" );
    lina_ = Brain::Texture_2D::create( "assets\\textures\\lina.png" );

    tex_shader->bind();
    tex_shader->set_texture( "u_texture", 0 );
}



void Example_Layer::on_attach( void )
{}



void Example_Layer::on_detach( void )
{}



void Example_Layer::on_update( Brain::Time_Step ts )
{
    camera_controller_.on_update( ts );

    Brain::Render_Command::set_clear_color( { 37.0 / 255.0, 37.0 / 255.0, 37.0 / 255.0, 1.0 } );


    Brain::Render_Command::clear();

    Brain::Renderer::begin_scene( camera_controller_.get_camera() );

    static const glm::mat4 scale = glm::scale( glm::mat4( 1.0f ), glm::vec3( 0.1f ) );

    static const glm::vec4 colors[ 3 ]{ glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f },
        glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f },
        glm::vec4{ 0.0f, 0.0f, 1.0f, 1.0f } };
    int c = 0;

    flat_color_shader_->bind();
    flat_color_shader_->set( "u_color", square_color_ );

    for( int y = 0; y < 20; y++ )
    {
        for( int x = 0; x < 20; x++ )
        {
            glm::vec3 pos{ x * 0.105f, y * 0.105f, 0.0f };
            glm::mat4 transform = glm::translate( glm::mat4( 1.0f ), pos ) * scale;
            Brain::Renderer::submit( flat_color_shader_, square_vertex_array_, transform );
        }
    }

    auto texture = shader_lib_.get( "texture" );

    texture_->bind();
    Brain::Renderer::submit( texture, square_vertex_array_, glm::scale( glm::mat4( 1.0f ), glm::vec3( 1.5f ) ) );
    lina_->bind();
    Brain::Renderer::submit( texture, square_vertex_array_, glm::scale( glm::mat4( 1.0f ), glm::vec3( 1.5f ) ) );

    Brain::Renderer::end_scene();
}



void Example_Layer::on_imgui_render()
{
    ImGui::Begin( "Settin's" );
    ImGui::ColorPicker3( "Square Color", glm::value_ptr( square_color_ ) );
    ImGui::End();
}



void Example_Layer::on_event( Brain::Event& e )
{
    camera_controller_.on_event( e );
}
