#ifndef _UDPCLIENT_H
#define _UDPCLIENT_H

#include "gsnet.h"
#include "udpsocket.h"
#include "client.h"

namespace GSNet {

	class GSNET_API CUdpClient : public CUdpSocket, public IClient {
	public:
		CUdpClient(const std::string& host, int32_t port);
	};

}

#endif /* _UDPCLIENT_H */
