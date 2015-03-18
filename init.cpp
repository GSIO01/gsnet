#include "init.h"

namespace GSNet {

	CInit CInit::_s_instance;

#if defined(WIN32) || defined(_MSC_VER)

	bool CInit::Start() {
		if (_nofSockets == 0) {
			WSADATA info;
			if (WSAStartup(MAKEWORD(2, 2), &info) != 0) {
				return false;
			}
		}

		++_nofSockets;
		return true;
	}

	void CInit::End() {
		--_nofSockets;

		if (_nofSockets == 0) {
			WSACleanup();
		}
	}

#endif

}