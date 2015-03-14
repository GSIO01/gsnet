#ifndef _SOCKET_H
#define _SOCKET_H

#include "gsnet.h"

#include <string>
#include <cinttypes>


namespace gsnet {

	enum ESocketType {
		ST_BLOCKING,
		ST_NON_BLOCKING
	};

	class GSNET_API isocket {
	public:
		virtual ~isocket() { }

		virtual std::string receiveLine() = 0;
		virtual std::string receiveBytes() = 0;
		virtual void close() = 0;
		virtual void sendLine(std::string line) = 0;
		virtual void sendBytes(const std::string& bytes) = 0;

	protected:
		isocket() { }
	};

}

#endif /* _SOCKET_H */
