#include "tcpsocket.h"
#include <iostream>

namespace gsnet {

#if defined(WIN32) || defined(_MSC_VER)

	int32_t tcpsocket::_nofSockets = 0;

	bool tcpsocket::start() {
		if (_nofSockets == 0) {
			WSADATA info;
			if (WSAStartup(MAKEWORD(2, 2), &info) != 0) {
				return false;
			}
		}

		++_nofSockets;
		return true;
	}

	void tcpsocket::end() {
		WSACleanup();
	}

	tcpsocket::tcpsocket() : _s(0) {
		start();

		_s = socket(AF_INET, SOCK_STREAM, 0);

		if (_s == INVALID_SOCKET) {
			return;
		}

		_refCounter = new int32_t(1);
	}

	tcpsocket::tcpsocket(SOCKET s) : _s(s) {
		start();
		_refCounter = new int32_t(1);
	}

	tcpsocket::~tcpsocket() {
		if (--(*_refCounter) == 0) {
			close();
			delete _refCounter;
		}

		--_nofSockets;
		if (_nofSockets == 0) {
			end();
		}
	}

	tcpsocket::tcpsocket(const tcpsocket& other) {
		_refCounter = other._refCounter;
		(*_refCounter)++;
		_s = other._s;

		_nofSockets++;
	}

	tcpsocket& tcpsocket::operator =(const tcpsocket& rhs) {
		(*rhs._refCounter)++;
		_refCounter = rhs._refCounter;
		_s = rhs._s;

		_nofSockets++;

		return *this;
	}

	void tcpsocket::close() {
		closesocket(_s);
	}

	std::string tcpsocket::receiveBytes() {
		std::string ret;
		char buffer[1024];

		for (;;) {
			u_long arg = 0;
			if (ioctlsocket(_s, FIONREAD, &arg) != 0) {
				break;
			}

			if (arg == 0) {
				break;
			}

			if (arg > 1024) {
				arg = 1024;
			}

			int32_t rv = recv(_s, buffer, arg, 0);
			if (rv <= 0) {
				break;
			}

			std::string t;
			t.assign(buffer, rv);
			ret += t;
		}

		return ret;
	}

	std::string tcpsocket::receiveLine() {
		std::string ret;

		for (;;) {
			char r;

			switch (recv(_s, &r, 1, 0)) {
			case 0:
				return ret;
			case -1:
				return "";
			}

			ret += r;
			if (r == '\n') {
				return ret;
			}
		}

		return ret;
	}

	void tcpsocket::sendLine(std::string line) {
		line += '\n';
		send(_s, line.c_str(), line.length(), 0);
	}

	void tcpsocket::sendBytes(const std::string& bytes) {
		send(_s, bytes.c_str(), bytes.length(), 0);
	}

#else

	// TODO POSIX implementation

#endif

}