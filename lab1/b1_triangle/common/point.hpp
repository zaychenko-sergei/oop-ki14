// (C) 2013-2014, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _POINT_HPP_
#define _POINT_HPP_

/*****************************************************************************/

#include "utils.hpp"

#include <cmath>

/*****************************************************************************/


struct Point
{
    const double m_x, m_y;

    Point ()
        :    m_x( 0.0 ), m_y( 0.0 )
    {}

    Point ( double _x, double _y )
        :    m_x( _x ), m_y( _y )
    {}

    bool operator == ( Point const & _p ) const
    {
        return equalDoubles( m_x, _p.m_x ) && equalDoubles( m_y, _p.m_y );
    }

    double distanceTo ( Point const & _p ) const
    {
        double diffX = _p.m_x - this->m_x;
        double diffY = _p.m_y - this->m_y;
        return sqrt( diffX * diffX + diffY * diffY );
    }
};


/*****************************************************************************/

#endif //  _POINT_HPP_
