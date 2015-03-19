#include "udpselect.h"

#if !defined(WIN32) & !defined(_MSC_VER)

typedef timeval TIMEVAL;

#endif

namespace GSNet {

  CUdpSelect::CUdpSelect(const CUdpSocket * const s1, const CUdpSocket * const s2 /* = nullptr */, ESocketType type /* = ST_BLOCKING */) : _lastError(SE_SUCCESS) {
    FD_ZERO(&_fds);
    FD_SET(const_cast<CUdpSocket*> (s1)->_s, &_fds);
    if (s2 != nullptr) {
      FD_SET(const_cast<CUdpSocket*> (s1)->_s, &_fds);
    }

    TIMEVAL tval;
    tval.tv_sec = 0;
    tval.tv_usec = 1;

    TIMEVAL* ptval = (type == ST_NON_BLOCKING) ? &tval : nullptr;

    if (select(0, &_fds, nullptr, nullptr, ptval) == SOCKET_ERROR) {
      _lastError = SE_ERROR_SELECT;
    }
  }

  bool CUdpSelect::Readable(const ISocket * const s) {
    const CUdpSocket * const sock = static_cast<const CUdpSocket * const> (s);

    _lastError = SE_SUCCESS;
    return (FD_ISSET(sock->_s, &_fds)) ? true : false;
  }

  bool CUdpSelect::HasError() const {
    return (_lastError != SE_SUCCESS);
  }

  ESocketError CUdpSelect::GetLastError() const {
    return _lastError;
  }

}