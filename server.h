#ifndef _SERVER_H
#define _SERVER_H

#include "gsnet.h"

namespace GSNet {

	class ISocket;

	class GSNET_API IServer {
	public:
		virtual ~IServer() { }

		virtual ISocket* Accept() = 0;

	protected:
		IServer() { }
	};

}

#endif /* _SERVER_H */
