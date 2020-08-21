#pragma once
#include "ArrayClass.h"

#ifndef __MATRIX__H
#define __MATRIX__H
// Recall the standard procedure for instantiating matrices via C++
// int matrix[5][5]	// for a 5x5 matrix of type int
// int* matrix = new int[5][5] // to allocate a 5x5 matrix in memory

//###########################################################
//#                 Exception Classes                       #
//###########################################################
class MatrixIncompatibleException;
class MatrixInvalidDimensionException;

//###########################################################
//#           Row-Major Implementation of Matrix            #
//###########################################################
template<class DT> class Matrix_RowMajor
{
protected:
	ArrayClass<DT>* myMat;	// a Row Major matrix
	int _rows, _cols;
public:
	Matrix_RowMajor(int rows, int cols)
	{
		_rows = rows;
		_cols = cols;
		myMat = new ArrayClass<DT>(rows * cols);
	};
	DT& operator()(int i, int j)
	{
		return myMat[i * _cols + j];
	}
};
//###########################################################
//#           Col-Major Implementation of Matrix            #
//###########################################################
template<class DT> class Matrix_ColMajor
{
protected:
	ArrayClass<DT>* myMat;	// a Col Major matrix
	int _rows, _cols;
public:
	Matrix_ColMajor(int rows, int cols)
	{
		_rows = rows;
		_cols = cols;
		myMat = new ArrayClass<DT>(rows * cols);
	};
	DT& operator()(int i, int j)
	{
		return myMat[j * _rows + i];
	}
};
//###########################################################
//#             Sparse Matrix Implementation                #
//###########################################################


#endif __MATRIX__H



//###########################################################
//#   ArrayClass of ArrayClass Implementation of Matrix     #
//###########################################################
#ifndef __MATRIXCLASS__H
#define __MATRIXCLASS__H
#include "ArrayClass.h"

// Operation could not be performed on this Matrix
class MatrixIncompatibleException : public ArrayException {};
// Invalid dimension was given
class MatrixInvalidDimensionException : public ArrayException {};

template<class DT>
class MatrixClass : public AbstractArrayClass<ArrayClass<DT>>
{
protected:
	ArrayClass<ArrayClass<DT>*>* theRows;
	void copy(const MatrixClass<DT>&);
	void deleteRows();
public:
	MatrixClass();
	MatrixClass(size_t rows, size_t cols);
	MatrixClass(size_t rows, size_t cols, const DT&);
	MatrixClass(const MatrixClass&);
	virtual ~MatrixClass();
	virtual ArrayClass<DT>& operator[](size_t k);
	void operator= (const MatrixClass&);
	virtual size_t size() const;
	size_t rows() const;
	size_t columns() const;
};
template<class DT> ArrayClass<DT>& MatrixClass<DT>::operator[](size_t k)
{
	if (k >= theRows->size()) throw ArrayBoundsException();
	return *(*theRows)[k];
};
template<class DT> void MatrixClass<DT>::copy(const MatrixClass<DT>& matrix)
{
	deleteRows();
	theRows = new ArrayClass<ArrayClass<DT>*>(matrix.rows(), NULL);
	for (size_t i = 0; i < theRows->size(); i++)
	{
		if ((*matrix.theRows)[i] != NULL)
		{
			(*theRows)[i] = new ArrayClass<DT>(*(*matrix.theRows)[i]);
			if ((*theRows)[i] == NULL) throw ArrayMemoryException();
		}
	}
};
template<class DT> void MatrixClass<DT>::deleteRows()
{
	if (theRows != NULL)
	{
		for (size_t i = 0; i < theRows->size(); i++)
		{
			if ((*theRows)[i] != NULL)
			{
				delete (*theRows)[i];
				(*theRows)[i] = NULL;
			}
		}
		delete theRows;
		theRows = NULL;
	}
};
template<class DT> MatrixClass<DT>::MatrixClass()
{
	theRows = new ArrayClass<ArrayClass<DT>*>(1, NULL);
	(*(theRows))[0] = new ArrayClass<DT>(1, 0);
	if ((*(theRows))[0] == NULL) throw ArrayMemoryException();
};
template<class DT> MatrixClass<DT>::MatrixClass(size_t rows, size_t cols)
{
	theRows = new ArrayClass<ArrayClass<DT>*>(rows, NULL);
	for (size_t i = 0; i < theRows->size(); i++)
	{
		(*(theRows))[i] = new ArrayClass<DT>(cols);
		if ((*(theRows))[i] == NULL) throw ArrayMemoryException();
	}
};
template<class DT> MatrixClass<DT>::MatrixClass(size_t rows, size_t cols, const DT& defaultVal)
{
	{
		theRows = new ArrayClass<ArrayClass<DT>*>(rows, NULL);
		for (size_t i = 0; i < rows; i++)
		{
			(*(theRows))[i] = new ArrayClass<DT>(cols, defaultVal);
			if ((*(theRows))[i] == NULL) throw ArrayMemoryException();
		}
	}
}
template<class DT> MatrixClass<DT>::MatrixClass(const MatrixClass& matrix)
{
	theRows = NULL;
	copy(matrix);
};
template<class DT> MatrixClass<DT>::~MatrixClass()
{
	deleteRows();
};
template<class DT> void MatrixClass<DT>::operator= (const MatrixClass& matrix)
{
	copy(matrix);
};
template<class DT> size_t MatrixClass<DT>::size() const
{
	return theRows->size();
};
template<class DT> size_t MatrixClass<DT>::rows() const
{
	return size();
};
template<class DT> size_t MatrixClass<DT>::columns() const
{
	return (*theRows)[0]->size();
};
#endif // __MATRIX__H

