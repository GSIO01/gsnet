#ifndef _TCPSOCKET_H
#define _TCPSOCKET_H

#include "gsnet.h"
#include "socket.h"
#include "server.h"
#include "client.h"

#include <string>
#include <cinttypes>

namespace gsnet {

#if defined(WIN32) || defined(_MSC_VER)

	class GSNET_API tcpsocket : public isocket {
	public:
		tcpsocket(const tcpsocket& other);
		virtual ~tcpsocket();

		tcpsocket& operator=(const tcpsocket& rhs);

		virtual std::string receiveLine() override;
		virtual std::string receiveBytes() override;
		virtual void close() override;
		virtual void sendLine(std::string line) override;
		virtual void sendBytes(const std::string& bytes) override;

	protected:
		friend class tcpserver;
		friend class tcpselect;

		tcpsocket(SOCKET s);
		tcpsocket();

		SOCKET _s;
		int32_t* _refCounter;

	private:
		static bool start();
		static void end();
		static int32_t _nofSockets;
	};


#else

	// TODO POSIX implementation here

#endif

}

#endif /* _TCPSOCKET_H */
