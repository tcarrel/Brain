#pragma once



#include "Brain/Renderer/texture.h"
#include "Brain/Renderer/orthographic_camera.h"



namespace Brain
{
    class Renderer_2D
    {
    public:
        static void init( void );
        static void shutdown( void );

        static void begin_scene( const Orthographic_Camera& camera );
        static void end_scene( void );

        // Primatives
        static void draw_quad( const glm::vec2& position, const glm::vec2& size, const glm::vec4& color );
        static void draw_quad( const glm::vec3& position, const glm::vec2& size, const glm::vec4& color );
        static void draw_quad( const glm::vec2& position, const glm::vec2& size, const Ref<Texture_2D>& texture, float texture_scale = 1.0f, const glm::vec4& tint = glm::vec4( 1.0f ) );
        static void draw_quad( const glm::vec3& position, const glm::vec2& size, const Ref<Texture_2D>& texture, float texture_scale = 1.0f, const glm::vec4& tint = glm::vec4( 1.0f ) );

        static void draw_rotated_quad( const glm::vec2& position, const glm::vec2& size, float radians, const glm::vec4& color );
        static void draw_rotated_quad( const glm::vec3& position, const glm::vec2& size, float radians, const glm::vec4& color );
        static void draw_rotated_quad( const glm::vec2& position, const glm::vec2& size, float radians, const Ref<Texture_2D>& texture, float texture_scale = 1.0f, const glm::vec4& tint = glm::vec4( 1.0f ) );
        static void draw_rotated_quad( const glm::vec3& position, const glm::vec2& size, float radians, const Ref<Texture_2D>& texture, float texture_scale = 1.0f, const glm::vec4& tint = glm::vec4( 1.0f ) );
    };
}