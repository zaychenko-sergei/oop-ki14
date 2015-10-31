// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MESSAGES_HPP_
#define _MESSAGES_HPP_

/*****************************************************************************/

namespace Messages
{
	const char * const IncorrectHistoryPeriodIndex = "Index of history periods is incorrect";
	const char * const HistoryPeriodIsNegative = "Year range of history period is negative";
	const char * const LeaderNameIsEmpty = "Leader name is empty";
	const char * const LeaderPositionIsEmpty = "Leader position is empty";
	const char * const LeaderUncorrectLivingYears = "Leader death date is greater than his birth date";
	const char * const LeaderAlreadyExists = "Leader already exists";
	const char * const CountryAlreadyExists = "Country already exists";
	const char * const LeaderDoesNotExist = "Leader with such name doesn't exist";
	const char * const CountryDoesNotExist = "Country with such name doesn't exist";
	const char * const CountryNameIsEmpty = "Country name is empty";
	const char * const CountryPopulationIsNonPositive = "Country population is non-positive";
}

/*****************************************************************************/

#endif // _MESSAGES_HPP_