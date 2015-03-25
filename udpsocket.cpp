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

#include "udpsocket.h"

#include <iostream>

#include "init.h"


#if !defined(WIN32) & !defined(_MSC_VER)

#include <unistd.h>
#include <sys/ioctl.h>

static int32_t(*closesocket)(int32_t s) = close;
static int32_t(*ioctlsocket)(int32_t s, unsigned long cmd, ...) = ioctl;

#endif


namespace GSNet {

  CUdpSocket::CUdpSocket() : _s(0), _lastError(SE_SUCCESS) {
    CInit::Instance()->Start();

    _s = socket(AF_INET, SOCK_DGRAM, 0);

    if (_s == INVALID_SOCKET) {
      _lastError = SE_ERROR_CREATE;
      return;
    }

    _refCounter = new int32_t(1);
  }

  CUdpSocket::CUdpSocket(SOCKET s) : _s(s), _lastError(SE_SUCCESS) {
    CInit::Instance()->Start();
    _refCounter = new int32_t(1);
  }

  CUdpSocket::~CUdpSocket() {
    if (--(*_refCounter) == 0) {
      Close();
      delete _refCounter;
    }

    CInit::Instance()->End();
  }

  CUdpSocket::CUdpSocket(const CUdpSocket& other) {
    _refCounter = other._refCounter;
    (*_refCounter)++;
    _s = other._s;
    _lastError = other._lastError;

    CInit::Instance()->Start();
  }

  CUdpSocket& CUdpSocket::operator=(const CUdpSocket& rhs) {
    (*rhs._refCounter)++;
    _refCounter = rhs._refCounter;
    _s = rhs._s;
    _lastError = rhs._lastError;

    CInit::Instance()->Start();

    return *this;
  }

  ESocketError CUdpSocket::Close() {
    if (closesocket(_s) == SOCKET_ERROR) {
      _lastError = SE_ERROR_CLOSE;
      return SE_ERROR_CLOSE;
    }

    _lastError = SE_SUCCESS;
    return SE_SUCCESS;
  }

  std::string CUdpSocket::ReceiveBytes() {
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

  size_t CUdpSocket::ReceiveBytes(byte** buf) {
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

  std::string CUdpSocket::ReceiveLine() {
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

  ESocketError CUdpSocket::SendLine(std::string line) {
    line += '\n';
    if (send(_s, line.c_str(), line.length(), 0) == SOCKET_ERROR) {
      _lastError = SE_ERROR_SEND;
      return SE_ERROR_SEND;
    }

    _lastError = SE_SUCCESS;
    return SE_SUCCESS;
  }

  ESocketError CUdpSocket::SendBytes(const std::string& bytes) {
    if (send(_s, bytes.c_str(), bytes.length(), 0) == SOCKET_ERROR) {
      _lastError = SE_ERROR_SEND;
      return SE_ERROR_SEND;
    }

    _lastError = SE_SUCCESS;
    return SE_SUCCESS;
  }

  ESocketError CUdpSocket::SendBytes(const byte* bytes, size_t size) {
    if (send(_s, (const char*)bytes, size, 0) == SOCKET_ERROR) {
      _lastError = SE_ERROR_SEND;
      return SE_ERROR_SEND;
    }

    _lastError = SE_SUCCESS;
    return SE_SUCCESS;
  }

  bool CUdpSocket::HasError() const {
    return (_lastError != SE_SUCCESS);
  }

  ESocketError CUdpSocket::GetLastError() const {
    return _lastError;
  }

}