#include <netinet/in.h>
#include <sys/ioctl.h>

#include "tcpserver.h"

#if defined(WIN32) || defined(_MSC_VER)

#else

#include <unistd.h>
#include <cstring>

#endif


namespace gsnet {

#if defined(WIN32) || defined(_MSC_VER)

  tcpserver::tcpserver(int32_t port, int32_t connections, ESocketType type /* = ST_BLOCKING */) {
    sockaddr_in sa;

    memset(&sa, 0, sizeof (sockaddr_in));

    sa.sin_family = PF_INET;
    sa.sin_port = htons(port);
    _s = socket(AF_INET, SOCK_STREAM, 0);
    if (_s == INVALID_SOCKET) {
      return;
    }

    if (type == ST_NON_BLOCKING) {
      u_long arg = 1;
      ioctlsocket(_s, FIONBIO, &arg);
    }

    if (bind(_s, (sockaddr*) & sa, sizeof (sockaddr_in)) == SOCKET_ERROR) {
      closesocket(_s);
      return;
    }

    listen(_s, connections);
  }

  isocket* tcpserver::accept() {
    SOCKET new_sock = ::accept(_s, 0, 0);

    if (new_sock == INVALID_SOCKET) {
      return nullptr;
    }

    tcpsocket* r = new tcpsocket(new_sock);
    return r;
  }

#else

  tcpserver::tcpserver(int32_t port, int32_t connections, ESocketType type) {
    sockaddr_in sa;
    
    memset(&sa, 0, sizeof(sockaddr_in));
    
    sa.sin_family = PF_INET;
    sa.sin_port = htons(port);
    _s = socket(AF_INET, SOCK_STREAM, 0);
    if(_s == -1) {
      return;
    }
    
    if(type == ST_NON_BLOCKING) {
      int32_t arg = 1;
      ioctl(_s, FIONBIO, &arg);
    }
    
    if(bind(_s, (sockaddr*)&sa, sizeof(sockaddr_in)) == -1) {
      ::close(_s);
      return;
    }
    
    listen(_s, connections);
  }
  
  isocket* tcpserver::accept() {
    int32_t new_sock = ::accept(_s, 0, 0);
    
    if(new_sock == -1) {
      return nullptr;
    }
    
    tcpsocket* r = new tcpsocket(new_sock);
    return r;
  }


#endif

}