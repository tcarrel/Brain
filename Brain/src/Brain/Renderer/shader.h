#pragma once



#include<string>
#include<glm/glm.hpp>



namespace Brain
{
    class Shader
    {
    public:
        ~Shader() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void set_texture( const std::string& name, int sample ) = 0;
        virtual void set( const std::string& name, int value ) = 0;
        virtual void set( const std::string& name, float value ) = 0;
        virtual void set( const std::string& name, const glm::vec3& vector ) = 0;
        virtual void set( const std::string& name, const glm::vec4& vector ) = 0;
        virtual void set( const std::string& name, const glm::mat4& matrix ) = 0;

        virtual const std::string& get_name( void ) const = 0;

        static Ref<Shader> create( const std::string& filepath );
        static Ref<Shader> create( const std::string& name, const std::string& vert_source, const std::string& frag_source );
    };



    class Shader_Library
    {
    public:
        void add( const std::string& name, const Ref<Shader>& shader );
        void add( const Ref<Shader>& shader );
        Ref<Shader> load( const std::string& filepath );
        Ref<Shader> load( const std::string& name, const std::string& filepath );

        Ref<Shader> get( const std::string& name );

        bool exists( const std::string name ) const;
    private:
        std::unordered_map<std::string, Ref<Shader>> shaders_;
    };
}