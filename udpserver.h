#ifndef _UDPSERVER_H
#define _UDPSERVER_H

#include "gsnet.h"
#include "server.h"
#include "socket.h"
#include "udpsocket.h"

namespace GSNet {

	class GSNET_API CUdpServer : public CUdpSocket, public IServer {
	public:
		CUdpServer(int32_t port, int32_t connections, ESocketType type = ST_BLOCKING);

		virtual ISocket* Accept() override;
	};

}

#endif /* _UDPSERVER_H */
