#include "udpserver.h"

#if defined(WIN32) || defined(_MSC_VER)

#else

#include <netinet/in.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstring>

int32_t(*closesocket)(SOCKET s) = close;
int32_t(*ioctlsocket)(SOCKET s, long cmd, int32_t* argp) = ioctl;

#endif

namespace GSNet {

  CUdpServer::CUdpServer(int32_t port, int32_t connections, ESocketType type /* = ST_BLOCKING */) {
    sockaddr_in sa;

    _lastError = SE_SUCCESS;

    memset(&sa, 0, sizeof (sockaddr_in));
    sa.sin_family = PF_INET;
    sa.sin_port = htons(port);
    _s = socket(AF_INET, SOCK_DGRAM, 0);
    if (_s = INVALID_SOCKET) {
      _lastError = SE_ERROR_CREATE;
      return;
    }

    if (type == ST_NON_BLOCKING) {
      u_long arg = 1;
      if (ioctlsocket(_s, FIONBIO, &arg) == SOCKET_ERROR) {
        _lastError = SE_ERROR_IOCTL;
        return;
      }
    }

    if (bind(_s, (sockaddr*) & sa, sizeof (sockaddr_in)) == SOCKET_ERROR) {
      _lastError = SE_ERROR_BIND;
      closesocket(_s);
      return;
    }

    if (listen(_s, connections) == SOCKET_ERROR) {
      _lastError = SE_ERROR_LISTEN;
      return;
    }

    _lastError = SE_SUCCESS;
  }

  ISocket* CUdpServer::Accept() {
    SOCKET new_sock = accept(_s, 0, 0);

    if (new_sock == INVALID_SOCKET) {
      _lastError = SE_ERROR_CREATE;
      return nullptr;
    }

    CUdpSocket* r = new CUdpSocket(new_sock);
    _lastError = SE_SUCCESS;
    return r;
  }

}