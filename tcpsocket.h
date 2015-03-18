#ifndef _TCPSOCKET_H
#define _TCPSOCKET_H

#include "gsnet.h"
#include "socket.h"

#include <string>
#include <cinttypes>

namespace GSNet {

#if defined(WIN32) || defined(_MSC_VER)

	class GSNET_API CTcpSocket : public ISocket {
	public:
		CTcpSocket(const CTcpSocket& other);
		virtual ~CTcpSocket();

		CTcpSocket& operator=(const CTcpSocket& rhs);

		virtual std::string ReceiveLine() override;
		virtual std::string ReceiveBytes() override;
		virtual ESocketError Close() override;
		virtual ESocketError SendLine(std::string line) override;
		virtual ESocketError SendBytes(const std::string& bytes) override;
		virtual bool HasError() const override;
		virtual ESocketError GetLastError() const override;

	protected:
		friend class CTcpServer;
		friend class CTcpSelect;

		CTcpSocket(SOCKET s);
		CTcpSocket();

		SOCKET _s;
		int32_t* _refCounter;
		ESocketError _lastError;
	};


#else

	class GSNET_API CTcpSocket : public ISocket {
	public:
		CTcpSocket(const CTcpSocket& other);
		virtual ~CTcpSocket();

		CTcpSocket& operator=(const CTcpSocket& rhs);

		virtual std::string ReceiveLine() override;
		virtual std::string ReceiveBytes() override;
		virtual ESocketError Close() override;
		virtual ESocketError SendLine(std::string line) override;
		virtual ESocketError SendBytes(const std::string& bytes) override;
		virtual bool HasError() const override;
		virtual ESocketError GetLastError() const override;

	protected:
		friend class CTcpServer;
		friend class CTcpSelect;

		CTcpSocket(int32_t s);
		CTcpSocket();

		int32_t _s;
		int32_t* _refCounter;
		ESocketError _lastError;
	};

	// TODO POSIX implementation here

#endif

}

#endif /* _TCPSOCKET_H */
