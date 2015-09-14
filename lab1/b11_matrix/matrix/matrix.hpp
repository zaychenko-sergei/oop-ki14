// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

/*****************************************************************************/

#include <iostream>
#include <stdexcept> 

/*****************************************************************************/


class Matrix
{

/*-----------------------------------------------------------------*/

public:

/*------------------------------------------------------------------*/

	template< typename _MatrixType >
	class MatrixRowAccessor
	{
		_MatrixType & m_matrix;
		const int m_rowIndex;

	public:

		MatrixRowAccessor ( _MatrixType & _matrix, int _rowIndex )
			:	m_matrix( _matrix )
			,	m_rowIndex( _rowIndex )
		{
		}

		double operator[] ( int _columnIndex ) const
		{
			// TODO ...
		}

		double& operator[] ( int _columnIndex )
		{
			// TODO ...
		}
	};


/*****************************************************************************/

	template< typename > friend class MatrixRowAccessor;

/*------------------------------------------------------------------*/

	
	MatrixRowAccessor< const Matrix > operator[] ( int _rowIndex ) const;

	MatrixRowAccessor< Matrix > operator[] ( int _rowIndex );

	// TODO ...

/*------------------------------------------------------------------*/

};


/*****************************************************************************/

#endif //  _MATRIX_HPP_
