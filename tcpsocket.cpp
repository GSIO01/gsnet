/*
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Walter Julius Hennecke
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "tcpsocket.h"

#include <iostream>

#include "init.h"

#if !defined(WIN32) & !defined(_MSC_VER)

#include <unistd.h>
#include <sys/ioctl.h>

static int32_t(*closesocket)(int32_t s) = close;
static int32_t(*ioctlsocket)(int32_t s, unsigned long cmd, ...) = ioctl;

#else

#include <WS2tcpip.h>

#endif

namespace GSNet {

  CTcpSocket::CTcpSocket()
    : _s(0)
    , _lastError(SE_SUCCESS)
  {
    CInit::Instance()->Start();

    _s = socket(AF_INET, SOCK_STREAM, 0);

    if(_s == INVALID_SOCKET)
    {
      _lastError = SE_ERROR_CREATE;
      return;
    }

    _refCounter = new int32_t(1);
  }


  CTcpSocket::CTcpSocket(SOCKET s)
    : _s(s)
    , _lastError(SE_SUCCESS)
  {
    CInit::Instance()->Start();
    _refCounter = new int32_t(1);
  }


  CTcpSocket::~CTcpSocket() {
    if (--(*_refCounter) == 0) {
      CTcpSocket::Close();
      delete _refCounter;
    }

    CInit::Instance()->End();
  }


  CTcpSocket::CTcpSocket(const std::string& host, uint16_t port, ESocketType type)
  {
    CInit::Instance()->Start();

    _s = socket(AF_INET, SOCK_STREAM, 0);

    if(_s == INVALID_SOCKET)
    {
      _lastError = SE_ERROR_CREATE;
      return;
    }

    u_long arg = type == ST_BLOCKING ? 0 : 1;
    if (ioctlsocket(_s, FIONBIO, &arg) == SOCKET_ERROR) {
      _lastError = SE_ERROR_IOCTL;
      return;
    }

    struct addrinfo* result = nullptr;
    struct addrinfo hints;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if (getaddrinfo(host.c_str(), std::to_string(port).c_str(), &hints, &result) == SOCKET_ERROR) {
      _lastError = SE_ERROR_GETADDR;
      return;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr = reinterpret_cast<sockaddr_in*>(result->ai_addr)->sin_addr;
    memset(&addr.sin_zero, 0, 8);

    if (connect(_s, reinterpret_cast<sockaddr*>(& addr), sizeof(sockaddr)) == SOCKET_ERROR) {
      _lastError = SE_ERROR_CONNECT;
    }

    _refCounter = new int32_t(1);
  }


  CTcpSocket::CTcpSocket(const CTcpSocket& other)
    : _s(other._s)
    , _refCounter(other._refCounter)
    , _lastError(other._lastError)
  {
    (*_refCounter)++;

    CInit::Instance()->Start();
  }


  CTcpSocket::CTcpSocket(CTcpSocket&& other) noexcept
    : _s(other._s)
    , _refCounter(std::move(_refCounter))
    , _lastError(other._lastError)
  {
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


  CTcpSocket& CTcpSocket::operator=(CTcpSocket&& rhs) noexcept
  {
    (*rhs._refCounter)++;
    _refCounter = std::move(_refCounter);
    _s = rhs._s;
    _lastError = rhs._lastError;

    CInit::Instance()->Start();

    return *this;
  }


  bool CTcpSocket::Close() {
    if (closesocket(_s) == SOCKET_ERROR) {
      _lastError = SE_ERROR_CLOSE;
      return false;
    }

    _lastError = SE_SUCCESS;
    return true;
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
      }
      
      if (rv == SOCKET_ERROR) {
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
      }
      
      if (rv == SOCKET_ERROR) {
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
      default:
        break;
      }

      ret += r;
      if (r == '\n') {
        _lastError = SE_SUCCESS;
        return ret;
      }
    }
  }


  std::string CTcpSocket::ReceiveString()
  {
    std::string ret;

    for (;;) {
      char r;

      switch (recv(_s, &r, 1, 0)) {
      case 0:
        return ret;
      case -1:
        _lastError = SE_ERROR_RECV;
        return "";
      default:
        break;
      }
            
      if (r == '\0') {
        _lastError = SE_SUCCESS;
        return ret;
      }

      ret += r;
    }
  }


  bool CTcpSocket::SendString(const std::string& str)
  {
    if(send(_s, str.c_str(), str.length() + 1, 0) == SOCKET_ERROR)
    {
      _lastError = SE_ERROR_SEND;
      return false;
    }

    _lastError = SE_SUCCESS;
    return true;
  }

  
  bool CTcpSocket::SendLine(const std::string& line) {
    auto cline = line + '\n';
    if (send(_s, cline.c_str(), cline.length(), 0) == SOCKET_ERROR) {
      _lastError = SE_ERROR_SEND;
      return false;
    }

    _lastError = SE_SUCCESS;
    return true;
  }

  bool CTcpSocket::SendBytes(const std::string& bytes) {
    if (send(_s, bytes.c_str(), bytes.length(), 0) == SOCKET_ERROR) {
      _lastError = SE_ERROR_SEND;
      return false;
    }

    _lastError = SE_SUCCESS;
    return true;
  }

  bool CTcpSocket::SendBytes(const byte* bytes, size_t size) {
    if (send(_s, reinterpret_cast<const char*>(bytes), size, 0) == SOCKET_ERROR) {
      _lastError = SE_ERROR_SEND;
      return false;
    }

    _lastError = SE_SUCCESS;
    return true;
  }

  bool CTcpSocket::HasError() const {
    return _lastError != SE_SUCCESS;
  }

  ESocketError CTcpSocket::GetLastError() const {
    return _lastError;
  }

}