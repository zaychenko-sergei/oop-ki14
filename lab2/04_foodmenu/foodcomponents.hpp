// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _FOODCOMPONENTS_HPP_
#define _FOODCOMPONENTS_HPP_

/*****************************************************************************/

#include <string>

/*****************************************************************************/


class FoodComponents
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	FoodComponents ( double _proteins, double _fat, double _carbo );

	double getProteins () const;

	double getFat () const;

	double getCarbo () const;

	bool operator == ( FoodComponents _c ) const;

	bool operator != ( FoodComponents _c ) const;

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	const double m_proteins, m_fat, m_carbo;

/*-----------------------------------------------------------------*/

};


/*****************************************************************************/


inline double
FoodComponents::getProteins () const
{
	return m_proteins;
}


/*****************************************************************************/


inline double
FoodComponents::getFat () const
{
	return m_fat;
}


/*****************************************************************************/


inline double
FoodComponents::getCarbo () const
{
	return m_carbo;
}


/*****************************************************************************/

#endif //  _FOODCOMPONENTS_HPP_
