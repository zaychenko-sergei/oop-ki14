// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _COFFEEMACHINE_HPP_
#define _COFFEEMACHINE_HPP_

/*****************************************************************************/


class CoffeeMachine
{

/*-----------------------------------------------------------------*/

public:

/*------------------------------------------------------------------*/

	enum Recipe { Espresso, Americano };

	enum Strength { Light, Medium, Strong };

	static const int WATER_FOR_ESPRESSO = 120, WATER_FOR_AMERICANO = 200;
	static const int WATER_FOR_WASHING = 500;
	static const int BEANS_FOR_LIGHT = 4, BEANS_FOR_MEDIUM = 8, BEANS_FOR_STRONG = 12;

/*------------------------------------------------------------------*/

	// TODO ...

/*------------------------------------------------------------------*/

};


/*****************************************************************************/

#endif //  _COFFEEMACHINE_HPP_
