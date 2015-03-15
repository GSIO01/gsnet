#include <cstdlib>
#include <cstdio>
#include <cinttypes>
#include <iostream>

#include "tcpclient.h"

int32_t main(int32_t argc, char* argv[]) {
	gsnet::tcpclient s("www.google.com", 80);

	s.sendLine("GET / HTTP/1.0");
	s.sendLine("Host: www.google.com");
	s.sendLine("");

	for (;;) {
		std::string l = s.receiveLine();

		if (l.empty()) {
			break;
		}

		std::cout << l;
		std::cout.flush();
	}

	getchar();
	return EXIT_SUCCESS;
}