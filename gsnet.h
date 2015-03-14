#if defined(WIN32) || defined(_MSC_VER)

#ifdef GSNET_EXPORTS
#define GSNET_API __declspec(dllexport)
#else
#define GSNET_API __declspec(dllimport)
#endif

#include <winsock2.h>

#else

#define GSNET_API

#endif


