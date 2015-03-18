#include <cstdlib>
#include <cstdio>
#include <cinttypes>
#include <iostream>

#include "tcpclient.h"

int32_t main(int32_t argc, char* argv[]) {
	GSNet::CTcpClient s("www.google.com", 80);

  if (s.HasError()) {
    return EXIT_FAILURE;
  }

  if (s.SendLine("GET / HTTP/1.0") > SE_SUCCESS || s.SendLine("Host: www.google.com") > SE_SUCCESS || s.SendLine("") > SE_SUCCESS) {
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