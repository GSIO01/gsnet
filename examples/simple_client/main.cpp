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

#include <cstdlib>
#include <cstdio>
#include <cinttypes>
#include <iostream>

#include "tcpclient.h"

int32_t main(int32_t argc, char* argv[]) {
  GSNet::CTcpClient s("duckduckgo.com", 80);

  if (s.HasError()) {
    return EXIT_FAILURE;
  }

  if (s.SendLine("GET / HTTP/1.0") > SE_SUCCESS || s.SendLine("Host: duckduckgo.com") > SE_SUCCESS || s.SendLine("") > SE_SUCCESS) {
    return EXIT_FAILURE;
  }

  for (;;) {
    std::string l = s.ReceiveLine();

    if (s.HasError()) {
      return EXIT_FAILURE;
    }

    if (l.empty()) {
      break;
    }

    std::cout << l;
    std::cout.flush();
  }

  getchar();
  return EXIT_SUCCESS;
}