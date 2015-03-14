#ifndef _TCPCLIENT_H
#define _TCPCLIENT_H

#include "gsnet.h"
#include "tcpsocket.h"
#include "client.h"

namespace gsnet {

	class GSNET_API tcpclient : public tcpsocket, public iclient {
	public:
		tcpclient(const std::string& host, int32_t port);
	};

}

#endif /* _TCPCLIENT_H */
