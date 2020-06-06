#pragma once



namespace Brain
{
    class Render_Context
    {
    public:
        virtual void init( void ) = 0;
        virtual void swap_buffers( void ) = 0;

        static Scope<Render_Context> create( void* window );
    };
}