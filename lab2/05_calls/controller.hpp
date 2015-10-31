// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

/*****************************************************************************/

#include "calltype.hpp"

#include <vector>
#include <string>

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

	void addContact (
			const std::string & _fullName
		,	const std::string & _phoneNumber
	);

	const std::string & getFullName ( const std::string & _phoneNumber ) const;

/*-----------------------------------------------------------------*/

	void addCall (
			const std::string & _phoneNumber
		,	CallType _callType
		,	const DateTime & _callTime
		,	int _callDuration
	);

/*-----------------------------------------------------------------*/

	int getCallsCount () const;

	const std::string & getContactName ( int _callIndex ) const;

	const std::string & getPhoneNumber ( int _callIndex ) const;

	CallType getCallType ( int _callIndex ) const;

	const DateTime & getCallTime ( int _callIndex ) const;

	int getCallDuration ( int _callIndex ) const;

/*-----------------------------------------------------------------*/

	double getAverageBusinessTimeCallsDuration ( const DateTime & _day ) const;

	std::vector< std::string > getUnregisteredContactsFromCalls () const;

	std::string getMostFrequentIncomingContact () const;

	std::string getLongestOutgoingContact () const;

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
