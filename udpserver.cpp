#include "udpserver.h"

namespace gsnet {

#if defined(WIN32) || defined(_MSC_VER)

	udpserver::udpserver(int32_t port, int32_t connections, ESocketType type /* = ST_BLOCKING */) {
		sockaddr_in sa;

		memset(&sa, 0, sizeof(sockaddr_in));
		
		sa.sin_family = PF_INET;
		sa.sin_port = htons(port);
		_s = socket(AF_INET, SOCK_DGRAM, 0);
		if (_s = INVALID_SOCKET) {
			return;
		}

		if (type == ST_NON_BLOCKING) {
			u_long arg = 1;
			ioctlsocket(_s, FIONBIO, &arg);
		}

		if (bind(_s, (sockaddr*)&sa, sizeof(sockaddr_in)) == SOCKET_ERROR) {
			closesocket(_s);
			return;
		}

		listen(_s, connections);
	}

	isocket* udpserver::accept() {
		SOCKET new_sock = ::accept(_s, 0, 0);

		if (new_sock == INVALID_SOCKET) {
			return nullptr;
		}

		udpsocket* r = new udpsocket(new_sock);
		return r;
	}

#else

	// TODO POSIX implementation

#endif

}