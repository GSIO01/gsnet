#include "udpclient.h"

#if defined(WIN32) || defined(_MSC_VER)

#include <WS2tcpip.h>

#else

#include <cstring>
#include <netdb.h>

#endif

namespace GSNet {

	CUdpClient::CUdpClient(const std::string& host, int32_t port)
		: CUdpSocket() {
		struct addrinfo* result = nullptr;
		struct addrinfo hints;

		memset(&hints, 0, sizeof(addrinfo));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_DGRAM;
		hints.ai_protocol = IPPROTO_UDP;

		if (getaddrinfo(host.c_str(), std::to_string(port).c_str(), &hints, &result) == SOCKET_ERROR) {
      _lastError = SE_ERROR_GETADDR;
			return;
		}

		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr = ((sockaddr_in*)result->ai_addr)->sin_addr;
		memset(&addr.sin_zero, 0, 8);

		if (connect(_s, (sockaddr*)&addr, sizeof(sockaddr)) == SOCKET_ERROR) {
      _lastError = SE_ERROR_CONNECT;
		}
	}

}