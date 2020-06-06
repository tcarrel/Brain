#include "br.pch.h"
#include "Brain/Core/window.h"



#if defined(BR_PLATFORM_WINDOWS)
# include "Platform/Windows/windows_window.h"
#endif



namespace Brain
{
    Scope<Window> Window::create( const Window_Properties& props )
    {
#ifdef BR_PLATFORM_WINDOWS
        return create_scope<Windows_Window>( props );
#else
        BR_CORE_ASSERT( false, "Unknown Platform." );
        return nullptr;
#endif
    }
}
