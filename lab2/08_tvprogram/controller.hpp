// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

/*****************************************************************************/

#include "day.hpp"
#include "datetime.hpp"
#include "genre.hpp"

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

	void addChannel ( const std::string & _channelName );

/*-----------------------------------------------------------------*/

	void addProgram (
			const std::string & _channelName
		,	Day _day
		,	const std::string & _programName
		,	const DateTime & _startTime
		,	Genre _genre
		,	int _rating
	);

	std::vector< std::string > getPrograms (
			const std::string & _channelName
		,	Day _day
	) const;

	std::vector< std::vector< std::string > > getPrograms ( const std::string & _channelName ) const;

/*-----------------------------------------------------------------*/

	std::vector< std::string > getAllSportPrograms () const;

	std::string getChannelWithHighestAverageRating () const;

	std::string getLongestProgram () const;

	// NOTE: First - channel name, second - program name
	std::pair< std::string, std::string > getBestProgramChoiceFor ( Day _day, int _hour ) const;

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

    // TODO: place private methods here

/*-----------------------------------------------------------------*/

    // TODO: place private fields here

/*-----------------------------------------------------------------*/ 

};

/*****************************************************************************/

#endif // _CONTROLLER_HPP_
