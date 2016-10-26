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

#ifndef _TCPSOCKET_H
#define _TCPSOCKET_H

#include "gsnet.h"
#include "socket.h"

#include <string>
#include <cinttypes>


namespace GSNet {

  class GSNET_API CTcpSocket : public ISocket {
  public:
    CTcpSocket(const std::string& host, uint16_t port, ESocketType type = ST_BLOCKING);
    CTcpSocket(const CTcpSocket& other);
    CTcpSocket(CTcpSocket&& other) noexcept;
    virtual ~CTcpSocket();

    CTcpSocket& operator=(const CTcpSocket& rhs);
    CTcpSocket& operator=(CTcpSocket&& rhs) noexcept;

    virtual std::string ReceiveLine() override;
    virtual std::string ReceiveString() override;
    virtual std::string ReceiveBytes() override;
    virtual size_t ReceiveBytes(byte** buffer) override;
    virtual bool Close() override;
    virtual bool SendLine(const std::string& line) override;
    virtual bool SendString(const std::string& str) override;
    virtual bool SendBytes(const std::string& bytes) override;
    virtual bool SendBytes(const byte* bytes, size_t size) override;
    virtual bool HasError() const override;
    virtual ESocketError GetLastError() const override;

  protected:
    friend class CTcpServer;
    friend class CTcpSelect;

    explicit CTcpSocket(SOCKET s);
    CTcpSocket();

    SOCKET _s;
    int32_t* _refCounter;
    ESocketError _lastError;
  };

}

#endif /* _TCPSOCKET_H */
