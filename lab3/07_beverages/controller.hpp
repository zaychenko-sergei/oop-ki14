// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

/*****************************************************************************/

#include <string>

/*****************************************************************************/

class Controller
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Controller ();

	Controller ( const Controller & ) = delete;

	Controller & operator = ( const Controller & ) = delete;

	~ Controller ();

/*-----------------------------------------------------------------*/

	void createCustomer ( 
			std::string const & _name
		,	int _age
		,	double _money
	);

	void makeCustomerAllergicTo (
			std::string const & _name
		,	std::string const & _ingredient 
	);

	double getCustomerBalance ( std::string const & _customerName ) const;

	int getCustomerAge ( std::string const & _customerName ) const;

	std::string getCustomerAllergicIngredient ( std::string const & _customerName ) const;

/*-----------------------------------------------------------------*/

	void createJuice (
			std::string const & _name
		,	int _volumeMl
		,	double _price
		,	std::string const & _mainIngredient
	);

	void createBeer (
			std::string const & _name
		,	int _volumeMl
		,	double _price
	);

	void createPoison (
			std::string const & _name
		,	int _volumeMl
		,	double _price
	);

	std::string getBeverageMainIngredient ( std::string const & _beverageName ) const;

	int getBeverageVolumeMl( std::string const & _beverageName ) const;

	double getBeveragePrice( std::string const & _beverageName ) const;

/*-----------------------------------------------------------------*/

	bool trySelling (
			std::string const & _customerName
		,	std::string const & _beverageName
	);

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	// TODO ...

/*-----------------------------------------------------------------*/


};

/*****************************************************************************/

#endif // _CONTROLLER_HPP_
