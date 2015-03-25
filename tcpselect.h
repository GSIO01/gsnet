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

#ifndef _TCPSELECT_H
#define _TCPSELECT_H

#include "gsnet.h"
#include "select.h"
#include "socket.h"
#include "tcpsocket.h"

#if !defined(WIN32) & !defined(_MSC_VER)

#include <sys/select.h>

#endif

namespace GSNet {

  class GSNET_API CTcpSelect : public ISelect {
  public:
    CTcpSelect(const CTcpSocket * const s1, const CTcpSocket * const s2 = nullptr, ESocketType type = ST_BLOCKING);

    virtual bool Readable(const ISocket * const s) override;
    virtual bool HasError() const override;
    virtual ESocketError GetLastError() const override;

  private:
    fd_set _fds;
    ESocketError _lastError;
  };

}

#endif /* _TCPSELECT_H */
