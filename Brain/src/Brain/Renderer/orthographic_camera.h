#pragma once



#include<glm/glm.hpp>



namespace Brain
{
    class Orthographic_Camera
    {
    public:
        Orthographic_Camera( float left, float right, float bottom, float top );
        void set_projection( float left, float right, float bottom, float top );

        void set_position( const glm::vec3& pos );
        void set_rotation( const float& rotz );

        const glm::mat4& projection{ projection_ };
        const glm::mat4& view{ view_ };
        const glm::mat4& vp{ view_projection_ };
        const glm::vec3& position{ position_ };
        const float& rotation{ rotation_ };


    private:

        void calculate_vp_matrix( void );
        void recalculate_view_matrix( void );

        glm::mat4 projection_{ glm::mat4( 1.0f ) };
        glm::mat4 view_{ glm::mat4( 1.0f ) };
        glm::mat4 view_projection_{ glm::mat4( 1.0f ) };

        glm::vec3 position_{ glm::vec3( 0.0f ) };
        float rotation_{ 0.0 };
    };
}