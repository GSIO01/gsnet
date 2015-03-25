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

#include "tcpselect.h"

#if !defined(WIN32) & !defined(_MSC_VER)

typedef timeval TIMEVAL;

#endif

namespace GSNet {

  CTcpSelect::CTcpSelect(const CTcpSocket * const s1, const CTcpSocket * const s2 /* = nullptr */, ESocketType type /* = ST_BLOCKING */) : _lastError(SE_SUCCESS) {
    FD_ZERO(&_fds);
    FD_SET(const_cast<CTcpSocket*> (s1)->_s, &_fds);
    if (s2 != nullptr) {
      FD_SET(const_cast<CTcpSocket*> (s1)->_s, &_fds);
    }

    TIMEVAL tval;
    tval.tv_sec = 0;
    tval.tv_usec = 1;

    TIMEVAL* ptval = (type == ST_NON_BLOCKING) ? &tval : nullptr;

    if (select(0, &_fds, nullptr, nullptr, ptval) == SOCKET_ERROR) {
      _lastError = SE_ERROR_SELECT;
    }
  }

  bool CTcpSelect::Readable(const ISocket * const s) {
    const CTcpSocket * const sock = static_cast<const CTcpSocket * const> (s);

    _lastError = SE_SUCCESS;
    return (FD_ISSET(sock->_s, &_fds)) ? true : false;
  }

  bool CTcpSelect::HasError() const {
    return (_lastError != SE_SUCCESS);
  }

  ESocketError CTcpSelect::GetLastError() const {
    return _lastError;
  }

}