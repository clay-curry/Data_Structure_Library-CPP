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
		if (n == -1) return s << "{}";
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

#ifndef __ABSTRACTVECTOR__H
#define __ABSTRACTVECTOR__H
template<typename DT> class AbstractVector : virtual public AbstractArrayClass<DT> {
public:
	virtual void insert(const DT& item, int index) = NULL;
	// insert a new object at position index in the vector
	virtual void remove(int index) = NULL;
	// remove the object at position index in the vector
	virtual void add(const DT& item) = NULL;
	// adds item at the end of the Vector
};
#endif

#ifndef __VECTOR__H
#define __VECTOR__h
template<typename DT> class Vector : public ArrayClass<DT>, virtual public AbstractVector<DT> {
protected:
	int _currSize;
	int _incFactor;
public:
	Vector();
	Vector(int n);
	Vector(int n, DT& val);
	Vector(const Vector<DT>& v);
	Vector(const ArrayClass<DT>& ac);
	virtual ~Vector();
	void operator= (const Vector<DT>& v);
	void operator= (const ArrayClass<DT>& ac);
	virtual void insert(const DT& item, int index);
	virtual void remove(int index);
	virtual void add(const DT& item);
	virtual int size() const;
	virtual int capacity() const;
	virtual int incFactor() const;
	virtual void setIncFactor(int f);
	void setCapacity(int c);
};
template<typename DT> Vector<DT>::Vector() : ArrayClass<DT>()
{
	_currSize = 0;
	_incFactor = 5;
};
template<typename DT> Vector<DT>::Vector(int n) : ArrayClass<DT>(n) 
{
	_currSize = 0;
	_incFactor = (n + 1) / 2;	// this is arbitary and one can use a different increment;
}
template<typename DT> Vector<DT>::Vector(int n, DT& val) : ArrayClass<DT>(n, val)
{
	_currSize = 0;
	_incFactor = n / 2;
}
template<typename DT> Vector<DT>::Vector(const Vector<DT>& v) : ArrayClass<DT>(v)
{
	_currSize = 0;
	_incFactor = v.incFactor();
}
template<typename DT> Vector<DT>::Vector(const ArrayClass<DT>& ac) : ArrayClass<DT>(ac)
{
	_currSize = ac.size();
	_incFactor = (_currSize + 1) / 2;
}
template<typename DT> Vector<DT>::~Vector() {}
template<typename DT> void Vector<DT>::operator= (const Vector<DT>& v)
{
	ArrayClass<DT>::copy(v);
	_currSize = v._currSize;
	_incFactor = v.incFactor;
}
template<typename DT> void Vector<DT>::operator= (const ArrayClass<DT>& ac)
{
	ArrayClass<DT>::copy(ac);
	_currSize = ac.size();
	_incFactor = (_currSize + 1) / 2;
}
template<typename DT> int Vector<DT>::size() const
{
	return _currSize;
}
template<typename DT> int Vector<DT>::capacity() const
{
	return ArrayClass<DT>::_size;
}
template<typename DT> int Vector<DT>::incFactor() const
{
	return _incFactor;
}
template<typename DT> void Vector<DT>::setIncFactor(int f)
{
	if (f >= 0) _incFactor = f;
}
template<typename DT> void Vector<DT>::setCapacity(int c)
{
	int len = _currSize;
	if (len > c) len = c;
	DT* paNew = new DT[c];
	if (paNew == NULL) throw ArrayMemoryException();
	for (int i = 0; i < len; i++) paNew[i] = ArrayClass<DT>::paObject[i];
	if (ArrayClass<DT>::paObject != NULL) delete[] ArrayClass<DT>::paObject;
	ArrayClass<DT>::paObject = paNew;
	ArrayClass<DT>::_size = c;
	if (_currSize > len) _currSize = len;
}
template<typename DT> void Vector<DT>::insert(const DT& item, int index)
{
	if ((index < 0) || (index > _currSize)) throw ArrayBoundsException();
	if (_currSize + 1 == ArrayClass<DT>::_size) setCapacity(ArrayClass<DT>::_size + _incFactor);
	_currSize++;
	for (int i = _currSize - 1; i > index; i--) (*this)[i] = (*this)[i - 1];
	(*this)[index] = item;
}
template<typename DT> void Vector<DT>::add(const DT& item)
{
	insert(item, _currSize);
}
template<typename DT> void Vector<DT>::remove(int index)
{
	if ((index < 0) || (index >= _currSize)) throw ArrayBoundsException();
	if (_currSize <= ArrayClass<DT>::_size - _incFactor) setCapacity(ArrayClass<DT>::_size - _incFactor);
	for (int i = index; i < _currSize - 1; i++) (*this)[i] = (*this)[i + 1];
	_currSize--;
}


#endif