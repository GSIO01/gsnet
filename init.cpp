#include "init.h"

namespace gsnet {

	init init::_s_instance;

	bool init::start() {
		if (_nofSockets == 0) {
			WSADATA info;
			if (WSAStartup(MAKEWORD(2, 2), &info) != 0) {
				return false;
			}
		}

		++_nofSockets;
		return true;
	}

	void init::end() {
		--_nofSockets;

		if (_nofSockets == 0) {
			WSACleanup();
		}
	}

}