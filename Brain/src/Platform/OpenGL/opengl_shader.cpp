#include"br.pch.h"
#include "Platform/OpenGL/opengl_shader.h"



#include<fstream>
#include<filesystem>
#include<glad/glad.h>
#include<glm/gtc/type_ptr.hpp>



namespace Brain
{
    static GLenum shader_type_from_string( const std::string& type )
    {
        static const std::unordered_map<std::string, GLenum> lookup_table{
            { "vertex", GL_VERTEX_SHADER },
            { "fragment", GL_FRAGMENT_SHADER },
            { "pixel", GL_FRAGMENT_SHADER }
        };

        auto found = lookup_table.find( type );
        if( found != lookup_table.end() )
        {
            return found->second;
        }

        BR_CORE_ASSERT( false, "Unknown shader type!" );
        return 0;
    } 



    OpenGL_Shader::OpenGL_Shader( const std::string& filepath )
    {
        BR_PROFILE_FUNCTION();

        auto shader_source{ read_file( filepath ) };
        auto sources{ preprocess( shader_source ) };

        compile( sources );


        //Extract name from filepath
        auto last_slash{ filepath.find_last_of( "/\\" ) };
        last_slash = last_slash == std::string::npos ? 0 : last_slash + 1;

        auto last_dot{ filepath.rfind( '.' ) };
        auto count{ ( last_dot == std::string::npos ? filepath.size() : last_dot ) - last_slash };
        name_ = filepath.substr( last_slash, count );
    }



    OpenGL_Shader::OpenGL_Shader( const std::string& name, const std::string& vert_source, const std::string& frag_source )
        :
        name_( name )
    {
        BR_PROFILE_FUNCTION();

        std::unordered_map<GLenum, std::string> sources{
            {GL_VERTEX_SHADER, vert_source },
            {GL_FRAGMENT_SHADER, frag_source}
        };
        compile( sources );
    }



    OpenGL_Shader::~OpenGL_Shader()
    {
        BR_PROFILE_FUNCTION();

        glDeleteProgram( renderer_id_ );
    }



    std::string OpenGL_Shader::read_file( const std::string& filepath )
    {
        BR_PROFILE_FUNCTION();

        std::filesystem::path path{ filepath };
        BR_CORE_ASSERT( std::filesystem::exists( path ), "Shader file '{0}' does not exist", filepath );

        std::ifstream in( filepath.c_str(), std::ios::in | std::ios::binary );
        if( in )
        {
            auto size{ std::filesystem::file_size( path ) };

            BR_CORE_ASSERT( size != -1, "Could not read from file '{0}'", filepath );

            std::string result{ "" };
            result.resize( size );
            in.read( result.data(), size );
            in.close();
            return result;
        }
        else
        {
            BR_ERROR( "Could not open file '{0}'", filepath );
            return "";
        }
    }



    std::unordered_map<GLenum, std::string> OpenGL_Shader::preprocess( const std::string& source )
    {
        BR_PROFILE_FUNCTION();

        std::unordered_map<GLenum, std::string> sources;

        const char* type_token = "@type";
        auto type_token_length{ strlen( type_token ) };
        auto pos{ source.find( type_token, 0 ) };
        while( pos != std::string::npos )
        {
            auto eol{ source.find_first_of( "\r\n", pos ) };
            BR_CORE_ASSERT( eol != std::string::npos, "Syntax Error" );
            auto begin{ pos + type_token_length + 1 };
            auto type{ source.substr( begin, eol - begin ) };
            BR_CORE_ASSERT( type == "vertex" || type == "fragment" || type == "pixel", "Invalid shader type specifier." );

            auto next_line_pos{ source.find_first_not_of( "\r\n", eol ) };
            BR_CORE_ASSERT( next_line_pos != std::string::npos, "Syntax Error" );
            pos = source.find( type_token, next_line_pos );
            sources[ shader_type_from_string( type ) ] =
                ( pos == std::string::npos ) ?
                source.substr( next_line_pos )
                :
                source.substr( next_line_pos, pos - next_line_pos );
        }

        return sources;
    }



    void OpenGL_Shader::compile( const std::unordered_map<GLenum, std::string>& shader_sources )
    {
        BR_PROFILE_FUNCTION();

        constexpr auto MAX_SHADERS{ 2 };
        auto program{ glCreateProgram() };
        BR_CORE_ASSERT( shader_sources.size() <= MAX_SHADERS, "Too many shaders." );

        std::array<GLenum, MAX_SHADERS> shader_ids;

        int index{ 0 };
        for( const auto& [type, source] : shader_sources )
        {
            auto shader = glCreateShader( type );

            const auto c_str{ source.c_str() };
            glShaderSource( shader, 1, &c_str, 0 );

            glCompileShader( shader );

            GLint is_compiled{ 0 };
            glGetShaderiv( shader, GL_COMPILE_STATUS, &is_compiled );
            if( is_compiled == GL_FALSE )
            {
                GLint maxl{ 0 };
                glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxl );

                std::vector<GLchar> log( maxl );
                glGetShaderInfoLog( shader, maxl, &maxl, log.data() );

                glDeleteShader( shader );

                BR_CORE_ERROR( "{0}", log.data() );
                BR_CORE_ASSERT( false, "Shader compilation failed." );
                break;
            }

            glAttachShader( program, shader );
            shader_ids[ index++ ] = shader;
        }

        glLinkProgram( program );

        GLint linked{ 0 };
        glGetProgramiv( program, GL_LINK_STATUS, reinterpret_cast<int*> ( &linked ) );
        if( linked == GL_FALSE )
        {
            GLint maxl{ 0 };
            glGetProgramiv( program, GL_INFO_LOG_LENGTH, &maxl );

            std::vector<GLchar> log( maxl );
            glGetProgramInfoLog( program, maxl, &maxl, log.data() );

            glDeleteProgram( program );

            for( auto id : shader_ids )
            {
                glDeleteShader( id );
            }

            BR_CORE_ERROR( "{0}", log.data() );
            BR_CORE_ASSERT( false, "Final shader linking failed." );

            return;
        }

        for( auto id : shader_ids )
        {
            glDetachShader( program, id );
            glDeleteShader( id );
        }

        renderer_id_ = program;
    }



    void OpenGL_Shader::bind() const
    {
        BR_PROFILE_FUNCTION();

        glUseProgram( renderer_id_ );
    }



    void OpenGL_Shader::unbind() const
    {
        BR_PROFILE_FUNCTION();

        glUseProgram( 0 );
    }



    void OpenGL_Shader::set_texture( const std::string& name, int sample )
    {
        BR_PROFILE_FUNCTION();

        upload_uniform( name, sample );
    }


    void OpenGL_Shader::set( const std::string& name, int value )
    {
        BR_PROFILE_FUNCTION();

        upload_uniform( name, value );
    }



    void OpenGL_Shader::set( const std::string& name, float value )
    {
        BR_PROFILE_FUNCTION();

        upload_uniform( name, value );
    }



    void OpenGL_Shader::set( const std::string& name, const glm::vec3& vector )
    {
        BR_PROFILE_FUNCTION();

        upload_uniform( name, vector );
    }



    void OpenGL_Shader::set( const std::string& name, const glm::vec4& vector )
    {
        BR_PROFILE_FUNCTION();

        upload_uniform( name, vector );
    }



    void OpenGL_Shader::set( const std::string& name, const glm::mat4& matrix )
    {
        BR_PROFILE_FUNCTION();

        upload_uniform( name, matrix );
    }



    const std::string& OpenGL_Shader::get_name( void ) const
    {
        return name_;
    }



    void OpenGL_Shader::upload_uniform( const std::string& name, int value )
    {
        const auto location = glGetUniformLocation( renderer_id_, name.c_str() );
        glUniform1i( location, value );
    }



    void OpenGL_Shader::upload_uniform( const std::string& name, float value )
    {
        const auto location = glGetUniformLocation( renderer_id_, name.c_str() );
        glUniform1f( location, value );
    }



    void OpenGL_Shader::upload_uniform( const std::string& name, const glm::vec2& vector )
    {
        const auto location = glGetUniformLocation( renderer_id_, name.c_str() );
        glUniform2f( location, vector.x, vector.y );
    }

    void OpenGL_Shader::upload_uniform( const std::string& name, const glm::vec3& vector )
    {
        const auto location = glGetUniformLocation( renderer_id_, name.c_str() );
        glUniform3f( location, vector.x, vector.y, vector.z );
    }



    void OpenGL_Shader::upload_uniform( const std::string& name, const glm::vec4& vector )
    {
        const auto location = glGetUniformLocation( renderer_id_, name.c_str() );
        glUniform4f( location, vector.x, vector.y, vector.z, vector.w );
    }



    void OpenGL_Shader::upload_uniform( const std::string& name, const glm::mat3& matrix )
    {
        const auto location = glGetUniformLocation( renderer_id_, name.c_str() );
        glUniformMatrix3fv( location, 1, GL_FALSE, glm::value_ptr( matrix ) );
    }



    void OpenGL_Shader::upload_uniform( const std::string& name, const glm::mat4& matrix )
    {
        const auto location = glGetUniformLocation( renderer_id_, name.c_str() );
        glUniformMatrix4fv( location, 1, GL_FALSE, glm::value_ptr( matrix ) );
    }
}