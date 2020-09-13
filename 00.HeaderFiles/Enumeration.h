#ifndef __ITERATOR__H
#define __ITERATOR__H
#include <exception>

class EnumerationException : public std::exception {};

template<class DT>
class Enumeration
{
public:
	// boolean method which determines if there are any more element in the data structure being enumerated
	virtual bool hasMoreElements() = 0;
	// returns the object which is the next element
	virtual DT& nextElement() = 0;
};
#endif // !__ITERATOR__H