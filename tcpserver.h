#ifndef _TCPSERVER_H
#define _TCPSERVER_H

#include "gsnet.h"
#include "server.h"
#include "socket.h"
#include "tcpsocket.h"

namespace gsnet {

	class GSNET_API tcpserver : public tcpsocket, public iserver {
	public:
		tcpserver(int32_t port, int32_t connections, ESocketType type = ST_BLOCKING);

		virtual isocket* accept() override;
	};

}

#endif /* _TCPSERVER_H */
