#ifndef _TCPSELECT_H
#define _TCPSELECT_H

#include "gsnet.h"
#include "select.h"
#include "socket.h"
#include "tcpsocket.h"

#if defined(WIN32) || defined(_MSC_VER)

#else

#include <sys/select.h>

#endif

namespace GSNet {

  class GSNET_API CTcpSelect : public ISelect {
  public:
    CTcpSelect(const CTcpSocket * const s1, const CTcpSocket * const s2 = nullptr, ESocketType type = ST_BLOCKING);

    virtual bool Readable(const ISocket * const s) override;
    virtual bool HasError() const override;
    virtual ESocketError GetLastError() const override;

  private:
    fd_set _fds;
    ESocketError _lastError;
  };

}

#endif /* _TCPSELECT_H */
