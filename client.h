#ifndef _CLIENT_H
#define _CLIENT_H

#include "gsnet.h"

namespace gsnet {

	class GSNET_API iclient {
	public:
		virtual ~iclient() { }

	protected:
		iclient() { }
	};

}

#endif /* _CLIENT_H */
