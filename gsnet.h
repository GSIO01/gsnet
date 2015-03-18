#if defined(WIN32) || defined(_MSC_VER)

#ifdef GSNET_EXPORTS
#define GSNET_API __declspec(dllexport)
#else
#define GSNET_API __declspec(dllimport)
#endif

#include <winsock2.h>

#else

#define GSNET_API

#include <sys/socket.h>

#endif

#ifndef _GSNET_H
#define _GSNET_H

enum ESocketError {
	SE_SUCCESS,
	SE_ERROR,
  SE_ERROR_CLOSE,
  SE_ERROR_IOCTL,
  SE_ERROR_RECV,
  SE_ERROR_CONNECT,
  SE_ERROR_SEND,
  SE_ERROR_CREATE,
  SE_ERROR_BIND,
  SE_ERROR_LISTEN,
  SE_ERROR_SELECT
};

#endif /* _GSNET_H */

