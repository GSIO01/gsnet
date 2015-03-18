#ifndef _GSNET_INIT_H
#define _GSNET_INIT_H

#include "gsnet.h"

#include <cinttypes>

namespace GSNet {

#if defined(WIN32) || defined(_MSC_VER)

	class CInit {
	public:
		virtual ~CInit() { }

		static CInit* Instance() {
			return &_s_instance;
		}

		bool Start();
		void End();

	protected:
		CInit() : _nofSockets(0) { }

		static CInit _s_instance;
		int32_t _nofSockets;
	};

#else

	class CInit {
	public:
		virtual ~CInit() { }

		static CInit* Instance() {
			return &_s_instance;
		}

		bool Start() {
			return true;
		}
		
		void End() { }

	protected:
		CInit() {}
                
                static CInit _s_instance;
	};

#endif

}

#endif /* _GSNET_INIT_H */
