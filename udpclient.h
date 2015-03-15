#ifndef _UDPCLIENT_H
#define _UDPCLIENT_H

#include "gsnet.h"
#include "udpsocket.h"
#include "client.h"

namespace gsnet {

	class GSNET_API udpclient : public udpsocket, public iclient {
	public:
		udpclient(const std::string& host, int32_t port);
	};

}

#endif /* _UDPCLIENT_H */
