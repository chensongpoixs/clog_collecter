/***********************************************************************************************
created: 		2019-02-26

author:			chensong

purpose:		noncopyable

Copyright boost
************************************************************************************************/

#ifndef _C_NONCOPYTABLE_H_
#define _C_NONCOPYTABLE_H_

namespace chen
{

	class cnoncopytable
	{
	public:
		cnoncopytable() {}
		~cnoncopytable() {}
	private:
		//cnoncopyable(cnoncopyable&&);
		cnoncopytable(const cnoncopytable&);
		//cnoncopyable &operator =(cnoncopyable &&);
		cnoncopytable& operator=(const cnoncopytable&);
	};

} //namespace chen
#endif // _C_NONCOPYABLE_H_

