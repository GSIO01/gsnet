#ifndef _TCPSELECT_H
#define _TCPSELECT_H

#include "gsnet.h"
#include "select.h"
#include "socket.h"
#include "tcpsocket.h"

namespace gsnet {

#if defined(WIN32) || defined(_MSC_VER)

	class GSNET_API tcpselect : public iselect {
	public:
		tcpselect(const tcpsocket* const s1, const tcpsocket* const s2 = nullptr, ESocketType type = ST_BLOCKING);

		virtual bool readable(const isocket* const s) override;

	private:
		fd_set _fds;
	};

#else

	// TODO POSIX implementation

#endif

}

#endif /* _TCPSELECT_H */
