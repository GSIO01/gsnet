#include "tcpselect.h"

namespace gsnet {

#if defined(WIN32) || defined(_MSC_VER)

  tcpselect::tcpselect(const tcpsocket * const s1, const tcpsocket * const s2 /* = nullptr */, ESocketType type /* = ST_BLOCKING */) {
    FD_ZERO(&_fds);
    FD_SET(const_cast<tcpsocket*> (s1)->_s, &_fds);
    if (s2 != nullptr) {
      FD_SET(const_cast<tcpsocket*> (s1)->_s, &_fds);
    }

    TIMEVAL tval;
    tval.tv_sec = 0;
    tval.tv_usec = 1;

    TIMEVAL* ptval = (type == ST_NON_BLOCKING) ? &tval : nullptr;

    if (select(0, &_fds, nullptr, nullptr, ptval) == SOCKET_ERROR) {
    }
  }

  bool tcpselect::readable(const isocket * const s) {
    const tcpsocket * const sock = static_cast<const tcpsocket * const> (s);

    return (FD_ISSET(sock->_s, &_fds)) ? true : false;
  }

#else

  tcpselect::tcpselect(const tcpsocket * const s1, const tcpsocket * const s2, ESocketType type) {
    FD_ZERO(&_fds);
    FD_SET(const_cast<tcpsocket*>(s1)->_s, &_fds);
    if(s2 != nullptr) {
      FD_SET(const_cast<tcpsocket*>(s2)->_s, &_fds);
    }
    
    timeval tval;
    tval.tv_sec = 0;
    tval.tv_usec = 1;
    
    timeval* ptval = (type == ST_NON_BLOCKING) ? &tval : nullptr;
    
    if(select(0, &_fds, nullptr, nullptr, ptval) == -1) {
    }
  }
  
  bool tcpselect::readable(const isocket* const s) {
    const tcpsocket* const sock = static_cast<const tcpsocket* const>(s);
    
    return (FD_ISSET(sock->_s, &_fds)) ? true : false;
  }


#endif

}