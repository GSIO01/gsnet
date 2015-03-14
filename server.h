#ifndef _SERVER_H
#define _SERVER_H

#include "gsnet.h"

namespace gsnet {

	class isocket;

	class GSNET_API iserver {
	public:
		virtual ~iserver() { }

		virtual isocket* accept() = 0;

	protected:
		iserver() { }
	};

}

#endif /* _SERVER_H */
