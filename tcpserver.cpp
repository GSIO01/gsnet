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

#include "tcpserver.h"

#if !defined(WIN32) & !defined(_MSC_VER)

#include <netinet/in.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstring>

static int32_t(*closesocket)(int32_t s) = close;
static int32_t(*ioctlsocket)(int32_t s, unsigned long cmd, ...) = ioctl;

#endif


namespace GSNet {

  CTcpServer::CTcpServer(int32_t port, int32_t connections, ESocketType type /* = ST_BLOCKING */) {
    sockaddr_in sa;

    _lastError = SE_SUCCESS;

    memset(&sa, 0, sizeof(sockaddr_in));
    sa.sin_family = PF_INET;
    sa.sin_port = htons(port);
    _s = socket(AF_INET, SOCK_STREAM, 0);
    if (_s == INVALID_SOCKET) {
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

    if (bind(_s, (sockaddr*)& sa, sizeof(sockaddr_in)) == SOCKET_ERROR) {
      _lastError = SE_ERROR_BIND;
      closesocket(_s);
      return;
    }

    if (listen(_s, connections) == SOCKET_ERROR) {
      _lastError = SE_ERROR_LISTEN;
    }
  }

  ISocket* CTcpServer::Accept() {
    SOCKET new_sock = ::accept(_s, 0, 0);

    if (new_sock == INVALID_SOCKET) {
      _lastError = SE_ERROR_CREATE;
      return nullptr;
    }

    CTcpSocket* r = new CTcpSocket(new_sock);
    _lastError = SE_SUCCESS;
    return r;
  }

}