// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "nodepath.hpp"

/*****************************************************************************/


NodePath::NodePath ( int _firstIndex )
	:	m_indexes( { _firstIndex } )
{
}


/*****************************************************************************/


NodePath::~NodePath() = default;


/*****************************************************************************/


NodePath &
NodePath::pushIndex ( int _nextIndex )
{
	m_indexes.push_back( _nextIndex );
	return * this;
}


/*****************************************************************************/


int
NodePath::getLevelsCount () const
{
	return m_indexes.size();
}


/*****************************************************************************/


int
NodePath::getIndexAtLevel ( int _level ) const
{
	return m_indexes.at( _level );
}


/*****************************************************************************/
