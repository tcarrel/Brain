#include "br.pch.h"
#include "Brain/Renderer/renderer_2d.h"



#include "Brain/Renderer/shader.h"
#include "Brain/Renderer/vertex_array.h"
#include "Brain/Renderer/render_command.h"



#include<glm/gtc/matrix_transform.hpp>



namespace Brain
{
    struct Renderer_2D_Storage
    {
        Ref<Vertex_Array> quad_vertex_array;
        Ref<Shader> texture_shader;
        Ref<Texture_2D> white_texture;
    };

    static Renderer_2D_Storage* s_data{ nullptr };

    void Renderer_2D::init( void )
    {
        BR_PROFILE_FUNCTION();

        if( !s_data )
        {
            s_data = new Renderer_2D_Storage;
        }

        s_data->quad_vertex_array = Vertex_Array::create();


        float square[]{
            //xyz                  //uv
            -0.5f, -0.5f, 0.0f,    0.0f, 0.0f, 
             0.5f, -0.5f, 0.0f,    1.0f, 0.0f,
             0.5f,  0.5f, 0.0f,    1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f,    0.0f, 1.0f
        };


        Ref<Vertex_Buffer> g_vb{ Vertex_Buffer::create( square, sizeof( square ) ) };
        g_vb->set_layout(
            {
                {Shader_Data_Type::Float3, "a_position"},
                {Shader_Data_Type::Float2, "a_texture_coordinate" }
            } );
        s_data->quad_vertex_array->add_vertex_buffer( g_vb );

        uint32_t sq_indices[] = { 0, 1, 2, 2, 3, 0 };
        Ref<Index_Buffer> g_ib{ Index_Buffer::create( sq_indices, sizeof( sq_indices ) / sizeof( uint32_t ) ) };
        s_data->quad_vertex_array->set_index_buffer( g_ib );

        s_data->white_texture = Texture_2D::create( 1, 1 );
        uint32_t white_texture_data = 0xFF'FF'FF'FF;
        s_data->white_texture->set_data( &white_texture_data, sizeof( uint32_t ) );

        s_data->texture_shader = Shader::create( "assets\\shaders\\texture.glsl" );
        s_data->texture_shader->bind();
        s_data->texture_shader->set_texture( "u_texture", 0 );
    }



    void Renderer_2D::shutdown( void )
    {
        BR_PROFILE_FUNCTION();

        delete s_data;
        s_data = nullptr;
    }



    void Renderer_2D::begin_scene( const Orthographic_Camera& camera )
    {
        BR_PROFILE_FUNCTION();

        s_data->texture_shader->bind();
        s_data->texture_shader->set( "u_view_projection", camera.vp );
    }



    void Renderer_2D::end_scene( void )
    {
        BR_PROFILE_FUNCTION();
     }



    void Renderer_2D::draw_quad( const glm::vec2& position, const glm::vec2& size, const glm::vec4& color )
    {
        draw_quad( { position.x, position.y, 0.0f }, size, color );
    }



    void Renderer_2D::draw_quad( const glm::vec3& position, const glm::vec2& size, const glm::vec4& color )
    {
        BR_PROFILE_FUNCTION();

        s_data->texture_shader->set( "u_color", color );
        //s_data->texture_shader->set( "u_texture_scale", 1.0f );
        s_data->white_texture->bind();

        auto transform{
            glm::translate( glm::mat4( 1.0f ), position )
            * glm::scale( glm::mat4( 1.0f ), { size.x, size.y, 1.0f } ) };
        s_data->texture_shader->set( "u_transform", transform );

        s_data->quad_vertex_array->bind();
        Render_Command::draw_indexed( s_data->quad_vertex_array );
    }



    void Renderer_2D::draw_quad( const glm::vec2& position, const glm::vec2& size, const Ref<Texture_2D>& texture, float texture_scale, const glm::vec4& tint )
    {
        draw_quad( { position.x, position.y, 0.0f }, size, texture, texture_scale, tint );
    }



    void Renderer_2D::draw_quad( const glm::vec3& position, const glm::vec2& size, const Ref<Texture_2D>& texture, float texture_scale, const glm::vec4& tint )
    {
        BR_PROFILE_FUNCTION();

        s_data->texture_shader->set( "u_color", tint );
        s_data->texture_shader->set( "u_texture_scale", texture_scale );
        texture->bind();

        auto transform{
            glm::translate( glm::mat4( 1.0f ), position )
            * glm::scale( glm::mat4( 1.0f ), { size.x, size.y, 1.0f } ) };
        s_data->texture_shader->set( "u_transform", transform );

        s_data->quad_vertex_array->bind();
        Render_Command::draw_indexed( s_data->quad_vertex_array );
    }






    void Renderer_2D::draw_rotated_quad( const glm::vec2& position, const glm::vec2& size, float radians, const glm::vec4& color )
    {
        draw_rotated_quad( { position.x, position.y, 0.0f }, size, radians, color );
    }



    void Renderer_2D::draw_rotated_quad( const glm::vec3& position, const glm::vec2& size, float radians, const glm::vec4& color )
    {
        BR_PROFILE_FUNCTION();

        s_data->texture_shader->set( "u_color", color );
        //s_data->texture_shader->set( "u_texture_scale", 1.0f );
        s_data->white_texture->bind();

        auto transform{
            glm::translate( glm::mat4( 1.0f ), position )
            * glm::rotate( glm::mat4( 1.0f ), radians, {0, 0, 1.0f} )
            * glm::scale( glm::mat4( 1.0f ), { size.x, size.y, 1.0f } ) };
        s_data->texture_shader->set( "u_transform", transform );

        s_data->quad_vertex_array->bind();
        Render_Command::draw_indexed( s_data->quad_vertex_array );
    }



    void Renderer_2D::draw_rotated_quad( const glm::vec2& position, const glm::vec2& size, float radians, const Ref<Texture_2D>& texture, float texture_scale, const glm::vec4& tint )
    {
        draw_rotated_quad( { position.x, position.y, 0.0f }, size, radians, texture, texture_scale, tint );
    }



    void Renderer_2D::draw_rotated_quad( const glm::vec3& position, const glm::vec2& size, float radians, const Ref<Texture_2D>& texture, float texture_scale, const glm::vec4& tint )
    {
        BR_PROFILE_FUNCTION();

        s_data->texture_shader->set( "u_color", tint );
        s_data->texture_shader->set( "u_texture_scale", texture_scale );
        texture->bind();

        auto transform{
            glm::translate( glm::mat4( 1.0f ), position )
            * glm::rotate( glm::mat4( 1.0f ), radians, {0, 0, 1.0f} )
            * glm::scale( glm::mat4( 1.0f ), { size.x, size.y, 1.0f } ) };
        s_data->texture_shader->set( "u_transform", transform );

        s_data->quad_vertex_array->bind();
        Render_Command::draw_indexed( s_data->quad_vertex_array );
    }
}