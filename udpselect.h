#ifndef _UDPSELECT_H
#define _UDPSELECT_H

#include "gsnet.h"
#include "select.h"
#include "socket.h"
#include "udpsocket.h"

#if defined(WIN32) || defined(_MSC_VER)

#else

#include <sys/select.h>

#endif

namespace gsnet {

#if defined(WIN32) || defined(_MSC_VER) 

	class GSNET_API udpselect : public iselect {
	public:
		udpselect(const udpsocket* const s1, const udpsocket* const s2 = nullptr, ESocketType type = ST_BLOCKING);

		virtual bool readable(const isocket* const s) override;

	private:
		fd_set _fds;
	};

#else

	class GSNET_API udpselect : public iselect {
	public:
		udpselect(const udpsocket* const s1, const udpsocket* const s2 = nullptr, ESocketType type = ST_BLOCKING);

		virtual bool readable(const isocket* const s) override;

	private:
		fd_set _fds;
	};

#endif

}

#endif /* _UDPSELECT_H */
