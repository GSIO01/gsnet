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

#include "tcpclient.h"

#if defined(WIN32) | defined(_MSC_VER)

#include <WS2tcpip.h>

#else

#include <cstring>
#include <netdb.h>

#endif

namespace GSNet {

  CTcpClient::CTcpClient(const std::string& host, int32_t port, ESocketType type) : CTcpSocket() {
    u_long arg = type == ST_BLOCKING ? 0 : 1;
    if (ioctlsocket(_s, FIONBIO, &arg) == SOCKET_ERROR) {
      _lastError = SE_ERROR_IOCTL;
      return;
    }

    struct addrinfo* result = nullptr;
    struct addrinfo hints;

    memset(&hints, 0, sizeof(hints));
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
    addr.sin_addr = ((sockaddr_in*)result->ai_addr)->sin_addr;
    memset(&addr.sin_zero, 0, 8);

    if (connect(_s, (sockaddr*)& addr, sizeof(sockaddr)) == SOCKET_ERROR) {
      _lastError = SE_ERROR_CONNECT;
    }
  }

}