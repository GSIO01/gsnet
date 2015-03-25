#ifndef _UDPSELECT_H
#define _UDPSELECT_H

#include "gsnet.h"
#include "select.h"
#include "socket.h"
#include "udpsocket.h"

#if !defined(WIN32) & !defined(_MSC_VER)

#include <sys/select.h>

#endif

namespace GSNet {

  class GSNET_API CUdpSelect : public ISelect {
  public:
    CUdpSelect(const CUdpSocket* const s1, const CUdpSocket* const s2 = nullptr, ESocketType type = ST_BLOCKING);

    virtual bool Readable(const ISocket* const s) override;
    virtual bool HasError() const override;
    virtual ESocketError GetLastError() const override;

  private:
    fd_set _fds;
    ESocketError _lastError;
  };

}

#endif /* _UDPSELECT_H */
