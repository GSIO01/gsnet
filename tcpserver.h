#ifndef _TCPSERVER_H
#define _TCPSERVER_H

#include "gsnet.h"
#include "server.h"
#include "socket.h"
#include "tcpsocket.h"

namespace GSNet {

	class GSNET_API CTcpServer : public CTcpSocket, public IServer {
	public:
		CTcpServer(int32_t port, int32_t connections, ESocketType type = ST_BLOCKING);

		virtual ISocket* Accept() override;
	};

}

#endif /* _TCPSERVER_H */
