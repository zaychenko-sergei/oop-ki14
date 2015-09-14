// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _UTILS_HPP_
#define _UTILS_HPP_

/*****************************************************************************/

#include <cmath>

/*****************************************************************************/


inline
bool equalDoubles ( double _d1, double _d2, double _allowedDifference = 0.001 )
{
    return fabs( _d1 - _d2 ) <= _allowedDifference;
}


/*****************************************************************************/

#endif //  _UTILS_HPP_
