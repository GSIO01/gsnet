#ifndef _UDPSERVER_H
#define _UDPSERVER_H

#include "gsnet.h"
#include "server.h"
#include "socket.h"
#include "udpsocket.h"

namespace gsnet {

	class GSNET_API udpserver : public udpsocket, public iserver {
	public:
		udpserver(int32_t port, int32_t connections, ESocketType type = ST_BLOCKING);

		virtual isocket* accept() override;
	};

}

#endif /* _UDPSERVER_H */
