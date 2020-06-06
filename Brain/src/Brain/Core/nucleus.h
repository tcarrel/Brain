#pragma once



#include<memory>



#if defined(_WIN32)
// x86/x64
# if defined(_WIN64)
#  define BR_PLATFORM_WINDOWS
# else
#  error "x86 builds are not supported!"
# endif
#elif defined(__APPLE__) || defined(__MACH__)
# include<TargetConditionals.h>
# if TARGET_IPHONE_SIMULATOR == 1
#  error "IOS simulator is not supported!"
# elif TARGET_OS_IPHONE == 1
#  define BR_PLATFORM_IOS
#  error "IOS is not yet supported!"
# elif TARGET_OS_MACOS == 1
#  define BR_PLATFORM_MACOS
#  error "MacOS is not yet supported!"
# else
#  error "Unknown Apple platform!"
# endif
#elif defined(__ANDROID__)
# define BR_PLATFORM_ANDROID
# error "Andriod is not yet supported!"
#elif defined(__linux__)
# define BR_PLATFORM_LINUX
# error "Linux is not yet supported!"
#else
// Unknown compiler platform
# error "Unknown platform"
#endif



#if defined(BR_DEBUG)
# define BR_ENABLE_ASSERTS
#endif



#if defined(BR_ENABLE_ASSERTS)
# define BR_ASSERT(x, ...) { if( !( x ) ) { BR_FATAL( "Assertion Failed: {0}", __VA_ARGS__ ); __debugbreak(); } }
# define BR_CORE_ASSERT(x, ...) { if( !( x ) ) { BR_CORE_FATAL( "Assertion Failed: {0}", __VA_ARGS__ ); __debugbreak(); } }
#else
# define BR_ASSERT(...)
# define BR_CORE_ASSERT(...)
#endif // defined(BR_ENABLE_ASSERTS)



#define BR_BIND_EVENT_FUNCTION(fn) std::bind( &fn, this, std::placeholders::_1 )



constexpr int BIT( int shift )
{
    return 1 << shift;
}


namespace Brain
{
    template<typename T>
    using Scope = std::unique_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Scope<T> create_scope( Args&& ... args )
    {
        return std::make_unique<T>( std::forward<Args>( args )... );
    }


    template<typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Ref<T> create_ref( Args&& ... args )
    {
        return std::make_shared<T>( std::forward<Args>( args )... );
    }
}