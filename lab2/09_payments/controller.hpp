// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

/*****************************************************************************/

#include "datetime.hpp"

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

	void addOrganization (
			const std::string & _name
		,	const std::string & _registrationNumber
		,	int _balance
	);

	const std::string & getRegistrationNumber ( const std::string & _organizationName ) const;

	int getBalance ( const std::string & _organizationName ) const;

/*-----------------------------------------------------------------*/

	void addPayment (
			const std::string & _senderOrganizationName
		,	const std::string & _recieverOrganizationName
		,	const std::string & _uniqueNumber
		,	const std::string & _purpose
		,	const DateTime & _dateTime
		,	int _sum
	);

/*-----------------------------------------------------------------*/

	const std::string & getPaymentSenderOrganizationName ( const std::string & _paymentUniqueNumber ) const;

	const std::string & getPaymentRecieverOrganizationName ( const std::string & _paymentUniqueNumber ) const;

	const std::string & getPaymentPurpose ( const std::string & _paymentUniqueNumber ) const;

	const DateTime & getPaymentDateTime ( const std::string & _paymentUniqueNumber ) const;

	int getPaymentSum ( const std::string & _paymentUniqueNumber ) const;

/*-----------------------------------------------------------------*/

	// NOTE: First - organization name, second - balance
	std::vector< std::pair< std::string, int > > getFinalBalances () const;

	std::vector< std::string > getOrganizationsWithNegativeSaldo () const;

	std::vector< std::string > getBiggestPaymentData () const;

	Date getDateWithBiggestTotalPaymentsAmount () const;

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
