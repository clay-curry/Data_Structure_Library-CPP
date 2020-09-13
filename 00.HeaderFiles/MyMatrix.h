#include "ArrayClass.h"

// Recall the standard procedure for instantiating matrices via C++
// int matrix[5][5]	// for a 5x5 matrix of type int
// int* matrix = new int[5][5] // to allocate a 5x5 matrix in memory

//###########################################################
//#                 Exception Classes                       #
//###########################################################
class MatrixIncompatibleException : ArrayException {};
class MatrixInvalidDimensionException : ArrayException {};

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
//#   ArrayClass of ArrayClass Implementation of Matrix     #
//###########################################################
template<class DT> class Matrix_ArrayClassOfArrayClass
{
protected:
	ArrayClass<ArrayClass<DT>*>* myMat;
	int _rows, _cols;
public:
	Matrix_ArrayClassOfArrayClass(int rows, int cols)
	{
		myMat = new ArrayClass<ArrayClass<DT>*>(rows);
		for (int i = 0; i < rows; i++)
		{
			myMat[i] = new ArrayClass<DT>(cols);
		}
	}
	ArrayClass<DT>& operator[] (int i)
	{
		return (*(myMat[i]));
	}
};
//###########################################################
//#             Sparse Matrix Implementation                #
//###########################################################

template<class DT> class SparseRow
{
	friend class Matrix_Sparse<DT>;
protected:
	int row;
	int col;
	DT info;
};
template<class DT> class Matrix_Sparse
{
protected:
	ArrayClass<SparseRow<DT>*>* myMat;
public:
	Matrix_Sparse(int rows, int cols, const DT& defaultValue)
	{
		myMat = new ArrayClass<SparseRow<DT>*>(rows * cols);
	}

	void transpose()
	{
		ArrayClass<int>* temp = _rows;
		_rows = _cols;
		_cols = _rows;
	};
};

#ifndef __MATRIX__H
#define __MATRIX__H

#endif __MATRIX__H