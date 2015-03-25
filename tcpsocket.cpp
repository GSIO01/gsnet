#include "tcpsocket.h"

#include <iostream>
#include <cstring>

#include "init.h"

#if defined(WIN32) || defined(_MSC_VER)

#else

#include <unistd.h>
#include <sys/ioctl.h>

int32_t(*closesocket)(SOCKET s) = close;
int32_t(*ioctlsocket)(SOCKET s, long cmd, int32_t* argp) = ioctl;

#endif

namespace GSNet {

  CTcpSocket::CTcpSocket() : _s(0), _lastError(SE_SUCCESS) {
    CInit::Instance()->Start();

    _s = socket(AF_INET, SOCK_STREAM, 0);

    if (_s == INVALID_SOCKET) {
      _lastError = SE_ERROR_CREATE;
      return;
    }

    _refCounter = new int32_t(1);
  }

  CTcpSocket::CTcpSocket(SOCKET s) : _s(s), _lastError(SE_SUCCESS) {
    CInit::Instance()->Start();
    _refCounter = new int32_t(1);
  }

  CTcpSocket::~CTcpSocket() {
    if (--(*_refCounter) == 0) {
      Close();
      delete _refCounter;
    }

    CInit::Instance()->End();
  }

  CTcpSocket::CTcpSocket(const CTcpSocket& other) {
    _refCounter = other._refCounter;
    (*_refCounter)++;
    _s = other._s;
    _lastError = other._lastError;

    CInit::Instance()->Start();
  }

  CTcpSocket& CTcpSocket::operator=(const CTcpSocket& rhs) {
    (*rhs._refCounter)++;
    _refCounter = rhs._refCounter;
    _s = rhs._s;
    _lastError = rhs._lastError;

    CInit::Instance()->Start();

    return *this;
  }

  ESocketError CTcpSocket::Close() {
    if (closesocket(_s) == SOCKET_ERROR) {
      _lastError = SE_ERROR_CLOSE;
      return SE_ERROR_CLOSE;
    }

    _lastError = SE_SUCCESS;
    return SE_SUCCESS;
  }

  std::string CTcpSocket::ReceiveBytes() {
    std::string ret;
    char buffer[1024];

    for (;;) {
      u_long arg = 0;

      if (ioctlsocket(_s, FIONREAD, &arg) == SOCKET_ERROR) {
        _lastError = SE_ERROR_IOCTL;
        return "";
      }

      if (arg == 0) {
        break;
      }

      if (arg > 1024) {
        arg = 1024;
      }

      int32_t rv = recv(_s, buffer, arg, 0);
      if (rv == 0) {
        break;
      } else if (rv == SOCKET_ERROR) {
        _lastError = SE_ERROR_RECV;
        return "";
      }

      std::string t;
      t.assign(buffer, rv);
      ret += t;
    }

    _lastError = SE_SUCCESS;
    return ret;
  }

  size_t CTcpSocket::ReceiveBytes(byte** buf) {
    std::string rb;
    char buffer[1024];

    for (;;) {
      u_long arg = 0;

      if (ioctlsocket(_s, FIONREAD, &arg) == SOCKET_ERROR) {
        _lastError = SE_ERROR_IOCTL;
        return 0;
      }

      if (arg == 0) {
        break;
      }

      if (arg > 1024) {
        arg = 1024;
      }

      int32_t rv = recv(_s, buffer, arg, 0);
      if (rv == 0) {
        break;
      } else if (rv == SOCKET_ERROR) {
        _lastError = SE_ERROR_RECV;
        return 0;
      }

      std::string t;
      t.assign(buffer, rv);
      rb += t;
    }

    *buf = new byte[rb.length()];
    memcpy(*buf, rb.c_str(), rb.length());

    _lastError = SE_SUCCESS;
    return rb.length();
  }

  std::string CTcpSocket::ReceiveLine() {
    std::string ret;

    for (;;) {
      char r;

      switch (recv(_s, &r, 1, 0)) {
      case 0:
        return ret;
      case -1:
        _lastError = SE_ERROR_RECV;
        return "";
      }

      ret += r;
      if (r == '\n') {
        _lastError = SE_SUCCESS;
        return ret;
      }
    }

    _lastError = SE_SUCCESS;
    return ret;
  }

  ESocketError CTcpSocket::SendLine(std::string line) {
    line += '\n';
    if (send(_s, line.c_str(), line.length(), 0) == SOCKET_ERROR) {
      _lastError = SE_ERROR_SEND;
      return SE_ERROR_SEND;
    }

    _lastError = SE_SUCCESS;
    return SE_SUCCESS;
  }

  ESocketError CTcpSocket::SendBytes(const std::string& bytes) {
    if (send(_s, bytes.c_str(), bytes.length(), 0) == SOCKET_ERROR) {
      _lastError = SE_ERROR_SEND;
      return SE_ERROR_SEND;
    }

    _lastError = SE_SUCCESS;
    return SE_SUCCESS;
  }

  ESocketError CTcpSocket::SendBytes(const byte* bytes, size_t size) {
    if (send(_s, (const char*)bytes, size, 0) == SOCKET_ERROR) {
      _lastError = SE_ERROR_SEND;
      return SE_ERROR_SEND;
    }

    _lastError = SE_SUCCESS;
    return SE_SUCCESS;
  }

  bool CTcpSocket::HasError() const {
    return (_lastError != SE_SUCCESS);
  }

  ESocketError CTcpSocket::GetLastError() const {
    return _lastError;
  }

}