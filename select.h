#ifndef _SELECT_H
#define _SELECT_H

#include "gsnet.h"

namespace GSNet {

	class ISocket;

	class GSNET_API ISelect {
	public:
		virtual ~ISelect() { }

		virtual bool Readable(const ISocket* const s) = 0;
    virtual bool HasError() const = 0;
    virtual ESocketError GetLastError() const = 0;

	protected:
		ISelect() { }
	};

}

#endif /* _SELECT_H */
