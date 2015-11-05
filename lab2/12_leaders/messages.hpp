// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MESSAGES_HPP_
#define _MESSAGES_HPP_

/*****************************************************************************/

namespace Messages
{
	const char * const IncorrectHistoryPeriodIndex = "Index of history periods is incorrect";
	const char * const PeriodRangeInvalid = "Starting year in the period is bigger than finishing year";
	const char * const PeriodOverlap = "Specified history period overlaps with already existing period";
	const char * const LeaderNameEmpty = "Leader name is empty";
	const char * const LeaderPositionEmpty = "Leader position is empty";
	const char * const LeaderBadLivingYears = "Leader death date is greater than his birth date";
	const char * const LeaderAlreadyExists = "Leader already exists";
	const char * const CountryAlreadyExists = "Country already exists";
	const char * const LeaderDoesNotExist = "Leader with such name doesn't exist";
	const char * const CountryDoesNotExist = "Country with such name doesn't exist";
	const char * const CountryNameEmpty = "Country name is empty";
	const char * const NonPositivePopulation = "Country population is non-positive";
}

/*****************************************************************************/

#endif // _MESSAGES_HPP_