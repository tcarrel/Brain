#include "br.pch.h"



#include "Brain/Renderer/shader.h"
#include "Brain/Renderer/renderer.h"
#include "Platform/OpenGL/opengl_shader.h"



namespace Brain
{
    
    
    Ref<Shader> Shader::create( const std::string& filepath )
    {
        switch( Renderer::get_api() )
        {
        case Renderer_API::API::None:
            BR_ASSERT( false, "Renderer_API::None is not currently supported!" );
            return nullptr;
        case Renderer_API::API::OpenGL:
            return create_ref<OpenGL_Shader>( filepath );
        }

        BR_CORE_ASSERT( false, "Renderer_API::?Unknown" );
        return nullptr;
    }



    Ref<Shader> Shader::create( const std::string& name, const std::string& vert_source, const std::string& frag_source )
    {
        switch( Renderer::get_api() )
        {
        case Renderer_API::API::None:
            BR_ASSERT( false, "Renderer_API::None is not currently supported!" );
            return nullptr;
        case Renderer_API::API::OpenGL:
            return create_ref<OpenGL_Shader>( name, vert_source, frag_source );
        }

        BR_CORE_ASSERT( false, "Renderer_API::?Unknown" );
        return nullptr;
    }



    void Shader_Library::add( const std::string& name, const Ref<Shader>& shader )
    {
        BR_CORE_ASSERT( !exists( name ), "Shader already exists." );
        shaders_[ name ] = shader;
    }



    void Shader_Library::add( const Ref<Shader>& shader )
    {
        auto name{ shader->get_name() };
        add( name, shader );
    }



    Ref<Shader> Shader_Library::load( const std::string & filepath )
    {
        auto shader = Shader::create( filepath );
        add( shader );
        return shader;
    }



    Ref<Shader> Shader_Library::load( const std::string& name, const std::string& filepath )
    {
        auto shader = Shader::create( filepath );
        add( name, shader );
        return shader;
    }



    Ref<Shader> Shader_Library::get( const std::string& name )
    {
        BR_CORE_ASSERT( exists( name ), "Shader already exists." );
        return shaders_[ name ];
    }



    bool Shader_Library::exists( const std::string name ) const
    {
        return shaders_.find( name ) != shaders_.end();
    }
}