#ifndef _GSNET_INIT_H
#define _GSNET_INIT_H

#include "gsnet.h"

#include <cinttypes>

namespace gsnet {

	class init {
	public:
		virtual ~init() { }

		static init* instance() {
			return &_s_instance;
		}

		bool start();
		void end();

	protected:
		init() : _nofSockets(0) { }

		static init _s_instance;
		int32_t _nofSockets;
	};

}

#endif /* _GSNET_INIT_H */
