#ifndef _CLIENT_H
#define _CLIENT_H

#include "gsnet.h"

namespace GSNet {

	class GSNET_API IClient {
	public:
		virtual ~IClient() { }

	protected:
		IClient() { }
	};

}

#endif /* _CLIENT_H */
