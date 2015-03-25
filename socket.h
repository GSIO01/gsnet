#ifndef _SOCKET_H
#define _SOCKET_H

#include "gsnet.h"

#include <string>
#include <cinttypes>


namespace GSNet {

	enum ESocketType {
		ST_BLOCKING,
		ST_NON_BLOCKING
	};

	class GSNET_API ISocket {
	public:
		virtual ~ISocket() { }

		virtual std::string ReceiveLine() = 0;
		virtual std::string ReceiveBytes() = 0;
    virtual size_t ReceiveBytes(byte** buffer) = 0;
		virtual ESocketError Close() = 0;
		virtual ESocketError SendLine(std::string line) = 0;
		virtual ESocketError SendBytes(const std::string& bytes) = 0;
    virtual ESocketError SendBytes(const byte* bytes, size_t size) = 0;
		virtual bool HasError() const = 0;
		virtual ESocketError GetLastError() const = 0;

	protected:
		ISocket() { }
	};

}

#endif /* _SOCKET_H */
