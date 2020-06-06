#pragma once
#include "Brain/Renderer/shader.h"



#include<glm/glm.hpp>

// TODO  REMOVE!
typedef unsigned int GLenum;

namespace Brain
{
    class OpenGL_Shader : public Shader
    {
    public:
        OpenGL_Shader( const std::string& filepath );
        OpenGL_Shader( const std::string& name, const std::string& vert_source, const std::string& frag_source );
        virtual ~OpenGL_Shader();

        void bind() const override;
        void unbind() const override;

        void set_texture( const std::string& name, int sample ) override;
        void set( const std::string& name, int value ) override;
        void set( const std::string& name, float value ) override;
        void set( const std::string& name, const glm::vec3& vector ) override;
        void set( const std::string& name, const glm::vec4& vector ) override;
        void set( const std::string& name, const glm::mat4& matrix ) override;

        const std::string& get_name( void ) const override;

        void upload_uniform( const std::string& name, int value );
        void upload_uniform( const std::string& name, float value );
        void upload_uniform( const std::string& name, const glm::vec2& vector );
        void upload_uniform( const std::string& name, const glm::vec3& vector );
        void upload_uniform( const std::string& name, const glm::vec4& vector );
        void upload_uniform( const std::string& name, const glm::mat3& matrix );
        void upload_uniform( const std::string& name, const glm::mat4& matrix );

    private:
        std::string read_file( const std::string& filepath );
        std::unordered_map<GLenum, std::string> preprocess( const std::string& source );
        void compile( const std::unordered_map<GLenum, std::string>& shader_sources );


        uint32_t renderer_id_{ 0 };
        std::string name_{ "" };
    };
}