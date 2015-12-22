// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

/*****************************************************************************/

#include "energyconsumer.hpp"

#include <memory>
#include <unordered_map>

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

	void createPersonConsumer ( int _consumerID );

	void createOrganizationConsumer ( int _consumerID );

	void createSystemConsumer ( int _consumerID );

	void consume ( int _consumerID, int _kiloWatts );

	double getConsumerDebt ( int _consumerID ) const;

	double getTotalDebt () const;

	bool isConsumerBlocked ( int _consumerID ) const;

	void trackConsumerPayment ( int _consumerID, double _payment );

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	// TODO ...

/*-----------------------------------------------------------------*/ 

};


/*****************************************************************************/

#endif //  _CONTROLLER_HPP_