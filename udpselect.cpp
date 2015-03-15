#include "udpselect.h"

namespace gsnet {

#if defined(WIN32) || defined(_MSC_VER)

	udpselect::udpselect(const udpsocket* const s1, const udpsocket* const s2 /* = nullptr */, ESocketType type /* = ST_BLOCKING */) {
		FD_ZERO(&_fds);
		FD_SET(const_cast<udpsocket*>(s1)->_s, &_fds);
		if (s2 != nullptr) {
			FD_SET(const_cast<udpsocket*>(s1)->_s, &_fds);
		}

		TIMEVAL tval;
		tval.tv_sec = 0;
		tval.tv_usec = 1;

		TIMEVAL* ptval = (type == ST_NON_BLOCKING) ? &tval : nullptr;

		if (select(0, &_fds, nullptr, nullptr, ptval) == SOCKET_ERROR) {
		}
	}

	bool udpselect::readable(const isocket* const s) {
		const udpsocket* const sock = static_cast<const udpsocket* const>(s);

		return (FD_ISSET(sock->_s, &_fds)) ? true : false;
	}

#else



#endif

}