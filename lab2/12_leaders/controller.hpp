// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

/*****************************************************************************/

#include "messages.hpp"

#include <vector>
#include <string>

/*****************************************************************************/


class Controller
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Controller ();

	~Controller ();

	Controller ( const Controller & ) = delete;

	Controller & operator = ( const Controller & ) = delete;

/*-----------------------------------------------------------------*/

	void addLeader (
			std::string const & _fullName
		,	std::string const & _position
		,	int _birthDate
		,	int _deathDate
	);

	void addCountry ( std::string const & _name );

	void addHistoryPeriod (
			std::string const & _countryName
		,	int _beginYear
		,	int _endYear
		,	std::string const & _leaderName
		,	int _population
	);

/*-----------------------------------------------------------------*/

	std::string const & getLeaderPosition ( std::string const & _name ) const;

	int getLeaderBirthDate ( std::string const & _name ) const;

	int getLeaderDeathDate ( std::string const & _name ) const;

/*-----------------------------------------------------------------*/

	int getHistoryPeriodPopulation (
			std::string const & _country
		,	std::string const & _leader
		,	int _beginDate
	) const;

	int getHistoryPeriodsCount ( std::string const & _country ) const;

/*-----------------------------------------------------------------*/

	std::pair< std::string, std::string > getLongestRunningCountryLeader () const;

	std::pair< std::string, std::string > getCaseWithBiggestPopulationPercentageGrowth () const;

	std::string getCountryWithMostFrequentLeaderChangesDuringLastYears ( int _range ) const;

	std::vector< std::string > getCurrentLeadersNotCalled ( std::string const & _position ) const;

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

    // TODO: place private methods here

/*-----------------------------------------------------------------*/

    // TODO: place private fields here

/*-----------------------------------------------------------------*/  

};


/*****************************************************************************/

#endif //  _CONTROLLER_HPP_
