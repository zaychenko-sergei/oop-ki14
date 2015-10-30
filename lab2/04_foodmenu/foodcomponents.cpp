// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "foodcomponents.hpp"

#include "messages.hpp"

/*****************************************************************************/


FoodComponents::FoodComponents ( double _proteins, double _fat, double _carbo )
	:	m_proteins( _proteins )
	,	m_fat( _fat )
	,	m_carbo( _carbo )
{
	if ( m_proteins < 0 )
		throw std::logic_error( Messages::NegativeProteins );

	if ( m_fat < 0 )
		throw std::logic_error( Messages::NegativeFat );

	if ( m_carbo < 0 )
		throw std::logic_error( Messages::NegativeCarbohydrates );
}


/*****************************************************************************/


bool FoodComponents::operator == ( FoodComponents _c ) const
{
	return m_proteins == _c.m_proteins &&
		   m_fat      == _c.m_fat &&
		   m_carbo    == _c.m_carbo ;
}


/*****************************************************************************/


bool FoodComponents::operator != ( FoodComponents _c ) const
{
	return !( * this == _c );
}


/*****************************************************************************/
