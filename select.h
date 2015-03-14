#ifndef _SELECT_H
#define _SELECT_H

#include "gsnet.h"

namespace gsnet {

	class isocket;

	class GSNET_API iselect {
	public:
		virtual ~iselect() { }

		virtual bool readable(const isocket* const s) = 0;

	protected:
		iselect() { }
	};

}

#endif /* _SELECT_H */
