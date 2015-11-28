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

	// @return ID of the created account
	int createAccount (
			std::string const & _ownerName
		,	double _initialBalance
	);

	// @return ID of the created account
	int createOverdraftAccount (
			std::string const & _ownerName
		,	double _initialBalance
		,	double _overdraftLimit
	);

	std::string const & getAccountOwnerName ( int _accountID ) const;

	double getAccountBalance ( int _accountID ) const;

	bool isOverdraftAllowed ( int _accountID ) const;

	double getOverdraftLimit ( int _accountID ) const;

	void deposit ( int _accountID, double _amount );

	void withdraw ( int _accountID, double _amount );

	void transfer ( int _sourceAccountID, int _targetAccountID, double _amount );

	double getTotalBankBalance () const;

	double getTotalBankDeposits () const;

	double getTotalBankOverdrafts () const;

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	// TODO
	
/*-----------------------------------------------------------------*/

};


/*****************************************************************************/

#endif //  _CONTROLLER_HPP_
