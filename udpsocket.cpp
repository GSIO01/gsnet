#include "udpsocket.h"

#include <iostream>

#include "init.h"


#if defined(WIN32) || defined(_MSC_VER)

#else

#include <unistd.h>
#include <sys/ioctl.h>

#endif


namespace gsnet {

#if defined(WIN32) || defined(_MSC_VER)

  udpsocket::udpsocket() : _s(0) {
    init::instance()->start();

    _s = socket(AF_INET, SOCK_DGRAM, 0);

    if (_s == INVALID_SOCKET) {
      return;
    }

    _refCounter = new int32_t(1);
  }

  udpsocket::udpsocket(SOCKET s) : _s(s) {
    init::instance()->start();
    _refCounter = new int32_t(1);
  }

  udpsocket::~udpsocket() {
    if (--(*_refCounter) == 0) {
      close();
      delete _refCounter;
    }

    init::instance()->end();
  }

  udpsocket::udpsocket(const udpsocket& other) {
    _refCounter = other._refCounter;
    (*_refCounter)++;
    _s = other._s;

    init::instance()->start();
  }

  udpsocket& udpsocket::operator=(const udpsocket& rhs) {
    (*rhs._refCounter)++;
    _refCounter = rhs._refCounter;
    _s = rhs._s;

    init::instance()->start();

    return *this;
  }

  void udpsocket::close() {
    closesocket(_s);
  }

  std::string udpsocket::receiveBytes() {
    std::string ret;
    char buffer[1024];

    for (;;) {
      u_long arg = 0;

      if (ioctlsocket(_s, FIONREAD, &arg) != 0) {
        break;
      }

      if (arg == 0) {
        break;
      }

      if (arg > 1024) {
        arg = 1024;
      }

      int32_t rv = recv(_s, buffer, arg, 0);
      if (rv <= 0) {
        break;
      }

      std::string t;
      t.assign(buffer, rv);
      ret += t;
    }

    return ret;
  }

  std::string udpsocket::receiveLine() {
    std::string ret;

    for (;;) {
      char r;

      switch (recv(_s, &r, 1, 0)) {
        case 0:
          return ret;
        case -1:
          return "";
      }

      ret += r;
      if (r == '\n') {
        return ret;
      }
    }

    return ret;
  }

  void udpsocket::sendLine(std::string line) {
    line += '\n';
    send(_s, line.c_str(), line.length(), 0);
  }

  void udpsocket::sendBytes(const std::string& bytes) {
    send(_s, bytes.c_str(), bytes.length(), 0);
  }

#else

  udpsocket::udpsocket() : _s(0) {
    init::instance()->start();

    _s = socket(AF_INET, SOCK_DGRAM, 0);

    if (_s == -1) {
      return;
    }

    _refCounter = new int32_t(1);
  }

  udpsocket::udpsocket(int32_t s) : _s(s) {
    init::instance()->start();
    _refCounter = new int32_t(1);
  }

  udpsocket::~udpsocket() {
    if (--(*_refCounter) == 0) {
      close();
      delete _refCounter;
    }

    init::instance()->end();
  }

  udpsocket::udpsocket(const udpsocket& other) {
    _refCounter = other._refCounter;
    (*_refCounter)++;
    _s = other._s;

    init::instance()->start();
  }

  udpsocket& udpsocket::operator=(const udpsocket& rhs) {
    (*rhs._refCounter)++;
    _refCounter = rhs._refCounter;
    _s = rhs._s;

    init::instance()->start();

    return *this;
  }

  void udpsocket::close() {
    ::close(_s);
  }

  std::string udpsocket::receiveBytes() {
    std::string ret;
    char buffer[1024];

    for (;;) {
      u_long arg = 0;

      if (ioctl(_s, FIONREAD, &arg) != 0) {
        break;
      }

      if (arg == 0) {
        break;
      }

      if (arg > 1024) {
        arg = 1024;
      }

      int32_t rv = recv(_s, buffer, arg, 0);
      if (rv <= 0) {
        break;
      }

      std::string t;
      t.assign(buffer, rv);
      ret += t;
    }

    return ret;
  }

  std::string udpsocket::receiveLine() {
    std::string ret;

    for (;;) {
      char r;

      switch (recv(_s, &r, 1, 0)) {
        case 0:
          return ret;
        case -1:
          return "";
      }

      ret += r;
      if (r == '\n') {
        return ret;
      }
    }

    return ret;
  }

  void udpsocket::sendLine(std::string line) {
    line += '\n';
    send(_s, line.c_str(), line.length(), 0);
  }

  void udpsocket::sendBytes(const std::string& bytes) {
    send(_s, bytes.c_str(), bytes.length(), 0);
  }

#endif

}