#ifndef __ABSTRACTARRAY_H
#define __ABSTRACTARRAY_H
#include <iostream>
using namespace std;
class Exception {};
class ArrayException : public Exception {};
class ArrayMemoryException : public ArrayException {};
class ArrayBoundsException : public ArrayException {};
template<typename DT> class AbstractArrayClass
{
	friend ostream& operator << (ostream& s, AbstractArrayClass<DT>& ac)
	{
		int n = ac.size() - 1;
		s << "{";
		for (int i = 0; i < n; i++) s << ac[i] << ",";
		s << ac[n] << "}";
		return s;
	};
public:
	virtual int size() const = NULL;
	virtual DT& operator[] (int k) = NULL;
};
#endif

#ifndef __ARRAYCLASS__H
#define __ARRAYCLASS__H
const int ARRAY_CLASS_DEFAULT_SIZE = 1;
template<typename DT>
class ArrayClass : virtual public AbstractArrayClass<DT>
{
protected:
	DT* paObject;
	int _size;
	void copy(const ArrayClass<DT>&);
public:
	ArrayClass();
	ArrayClass(int);
	ArrayClass(int, const DT&);
	ArrayClass(const ArrayClass<DT>&);
	virtual ~ArrayClass();
	virtual int size() const;
	virtual DT& operator[] (int);
	void operator= (const ArrayClass<DT>&);
};
template<typename DT> ArrayClass<DT>::ArrayClass()
{
	_size = 0;
	paObject = new DT[ARRAY_CLASS_DEFAULT_SIZE];
	if (paObject == NULL) throw ArrayMemoryException();
	_size = ARRAY_CLASS_DEFAULT_SIZE;
};
template<typename DT> ArrayClass<DT>::ArrayClass(int n)
{
	_size = 0;	// default size in case allocation fails
	paObject = new DT[n];
	if (paObject == NULL) throw ArrayMemoryException();
	_size = n;
};
template<typename DT> ArrayClass<DT>::ArrayClass(int n, const DT& val)
{
	_size = 0;	// default size in case allocation fails
	paObject = new DT[n];
	if (paObject == NULL) throw ArrayMemoryException();
	_size = n;
	for (int i = 0; i < n; i++)
		paObject[i] = val;
};
template<typename DT> ArrayClass<DT>::ArrayClass(const ArrayClass<DT>& ac)
{
	if (&ac != this)
		copy(ac);
};
template<typename DT> ArrayClass<DT>::~ArrayClass()
{
	if (paObject != NULL) delete[] paObject;
	paObject = NULL;
	_size = 0;
};
template<typename DT> void ArrayClass<DT>::copy(const ArrayClass<DT>& ac)
{
	_size = 0;
	paObject = new DT[ac.size()];
	if (paObject == NULL) throw ArrayMemoryException();
	_size = ac.size();
	for (int i = 0; i < _size; i++)
	{
		paObject[i] = ac.paObject[i];
	}
};
template<typename DT> int ArrayClass<DT>::size() const
{
	return _size;
};
template<typename DT> DT& ArrayClass<DT>::operator[] (int k)
{
	if ((k < 0) || (k >= size())) throw ArrayBoundsException();
	return paObject[k];
};
template<typename DT> void ArrayClass<DT>::operator= (const ArrayClass<DT>& ac)
{
	if (this != &ac) {
		if (paObject != NULL) delete[] paObject;
		copy(ac);
	}
};
#endif