#ifndef _UDPSOCKET_H
#define _UDPSOCKET_H

#include "gsnet.h"
#include "socket.h"

#include <string>
#include <cinttypes>

namespace gsnet {

#if defined(WIN32) || defined(_MSC_VER)

	class GSNET_API udpsocket : public isocket {
	public:
		udpsocket(const udpsocket& other);
		virtual ~udpsocket();

		udpsocket& operator=(const udpsocket& rhs);

		virtual std::string receiveLine() override;
		virtual std::string receiveBytes() override;
		virtual void close() override;
		virtual void sendLine(std::string line) override;
		virtual void sendBytes(const std::string& bytes) override;
	protected:
		friend class udpserver;
		friend class udpselect;

		udpsocket(SOCKET s);
		udpsocket();

		SOCKET _s;
		int32_t* _refCounter;
	};

#else

	class GSNET_API udpsocket : public isocket {
	public:
		udpsocket(const udpsocket& other);
		virtual ~udpsocket();

		udpsocket& operator=(const udpsocket& rhs);

		virtual std::string receiveLine() override;
		virtual std::string receiveBytes() override;
		virtual void close() override;
		virtual void sendLine(std::string line) override;
		virtual void sendBytes(const std::string& bytes) override;

	protected:
		friend class udpserver;
		friend class udpselect;

		udpsocket(int32_t s);
		udpsocket();

		int32_t _s;
		int32_t* _refCounter;
	};

#endif

}

#endif /* _UDPSOCKET_H */
