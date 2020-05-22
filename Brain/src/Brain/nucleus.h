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