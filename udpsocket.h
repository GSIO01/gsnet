#ifndef _UDPSOCKET_H
#define _UDPSOCKET_H

#include "gsnet.h"
#include "socket.h"

#include <string>
#include <cinttypes>

namespace GSNet {

	class GSNET_API CUdpSocket : public ISocket {
	public:
		CUdpSocket(const CUdpSocket& other);
		virtual ~CUdpSocket();

		CUdpSocket& operator=(const CUdpSocket& rhs);

		virtual std::string ReceiveLine() override;
		virtual std::string ReceiveBytes() override;
    virtual size_t ReceiveBytes(byte** buffer) override;
		virtual ESocketError Close() override;
		virtual ESocketError SendLine(std::string line) override;
		virtual ESocketError SendBytes(const std::string& bytes) override;
    virtual ESocketError SendBytes(const byte* bytes, size_t size) override;
		virtual bool HasError() const override;
		virtual ESocketError GetLastError() const override;

	protected:
		friend class CUdpServer;
		friend class CUdpSelect;

		CUdpSocket(SOCKET s);
		CUdpSocket();

		SOCKET _s;
		int32_t* _refCounter;
		ESocketError _lastError;
	};

}

#endif /* _UDPSOCKET_H */
