// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

/*****************************************************************************/

#include "datetime.hpp"

#include <string>
#include <vector>
#include <map>

/*****************************************************************************/


class Controller
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Controller ();

	~ Controller ();

	Controller ( const Controller & ) = delete;

	Controller & operator = ( const Controller & ) = delete;

/*-----------------------------------------------------------------*/

	void addParticipant (
			const std::string & _fullName
		,	const std::string & _email
	);

	const std::string & getParticipantEmail ( const std::string & _fullName ) const;

/*-----------------------------------------------------------------*/

	void addMeeting (
			int _meetingId
		,	const std::string & _name
		,	const DateTime & _startTime
	);

	const std::string & getMeetingName ( int _meetingId ) const;

	const DateTime & getMeetingStartTime ( int _meetingId ) const;

/*-----------------------------------------------------------------*/

	void addMeetingParticipant ( int _meetingId, const std::string & _participantName );

	void removeMeetingParticipant ( int _meetingId, const std::string & _participantName );

	void setMeetingModerator ( int _meetingId, const std::string & _participantName );

	std::string getMeetingModeratorName ( int _meetingId ) const;

	std::vector< std::string > getMeetingParticipants ( int _meetingId ) const;

	void validateMeceting ( int _meetingId ) const;

/*-----------------------------------------------------------------*/

	void addMeetingAgendaRow ( int _meetingId, const std::string & _agendaRow );

	std::vector< std::string > getMeetingAgenda ( int _meetingId ) const;

/*-----------------------------------------------------------------*/

	std::string getMostFrequentModeratorName () const;

	std::string getMeetingWithLongestAgenda () const;

	// NOTE: Key - participant, Value - meetings
	std::map< std::string, std::vector< std::string > > getOverlaps() const;

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
