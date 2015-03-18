#ifndef _TCPCLIENT_H
#define _TCPCLIENT_H

#include "gsnet.h"
#include "tcpsocket.h"
#include "client.h"

namespace GSNet {

	class GSNET_API CTcpClient : public CTcpSocket, public IClient {
	public:
		CTcpClient(const std::string& host, int32_t port);
	};

}

#endif /* _TCPCLIENT_H */
