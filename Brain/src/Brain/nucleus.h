#pragma once



#if defined(BR_PLATFORM_WINDOWS)
# if defined(BR_BUILD_DLL)
#  define BRAIN_API __declspec( dllexport )
# else
#  define BRAIN_API __declspec( dllimport )
# endif // defined(BR_BUILD_DLL)
#else
# error Brain only supports Windows!
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