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

#if defined(WIN32) | defined(_MSC_VER)

#ifdef GSNET_EXPORTS

#define GSNET_API __declspec(dllexport)

#else

#define GSNET_API __declspec(dllimport)

#endif

#include <winsock2.h>

#else

#define GSNET_API

#include <sys/socket.h>

#endif

#ifndef _GSNET_H
#define _GSNET_H

#if !defined(WIN32) & !defined(_MSC_VER)

typedef int32_t SOCKET;
static const int32_t SOCKET_ERROR = -1;
static const int32_t INVALID_SOCKET = -1;

#endif

enum ESocketError {
  SE_SUCCESS,
  SE_ERROR,
  SE_ERROR_CLOSE,
  SE_ERROR_IOCTL,
  SE_ERROR_RECV,
  SE_ERROR_CONNECT,
  SE_ERROR_SEND,
  SE_ERROR_CREATE,
  SE_ERROR_BIND,
  SE_ERROR_LISTEN,
  SE_ERROR_SELECT,
  SE_ERROR_GETADDR
};

#endif /* _GSNET_H */

