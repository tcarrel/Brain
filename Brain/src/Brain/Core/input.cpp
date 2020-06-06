#include "br.pch.h"
#include "Brain/Core/input.h"



#if defined(BR_PLATFORM_WINDOWS)
# include "Platform/Windows/windows_input.h"
#endif



namespace Brain
{
    Scope<Input> Input::instance_{ Input::create() };



    Scope<Input> Input::create( void )
    {
#if defined(BR_PLATFORM_WINDOWS)
        return create_scope<Windows_Input>();
#else
        BR_CORE_ASSERT( false, "Unknown platform." );
        return nullptr;
#endif
    }
}
