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

#ifndef _SOCKET_H
#define _SOCKET_H

#include "gsnet.h"

#include <string>
#include <cinttypes>


namespace GSNet {

  enum ESocketType {
    ST_BLOCKING,
    ST_NON_BLOCKING
  };

  class GSNET_API ISocket {
  public:
    virtual ~ISocket() { }

    virtual std::string ReceiveLine() = 0;
    virtual std::string ReceiveString() = 0;
    virtual std::string ReceiveBytes() = 0;
    virtual size_t ReceiveBytes(byte** buffer) = 0;
    virtual bool Close() = 0;
    virtual bool SendLine(const std::string& line) = 0;
    virtual bool SendString(const std::string& str) = 0;
    virtual bool SendBytes(const std::string& bytes) = 0;
    virtual bool SendBytes(const byte* bytes, size_t size) = 0;
    virtual bool HasError() const = 0;
    virtual ESocketError GetLastError() const = 0;

  protected:
    ISocket() { }
  };

}

#endif /* _SOCKET_H */
