// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "controller.hpp"
#include "messages.hpp"

#include "testslib.hpp"

/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_simple_account )
{
	Controller c;
	int accountID = c.createAccount( "Wasya", 100.0 );
	
	assert( c.getAccountOwnerName( accountID ) == "Wasya" );
	assert( c.getAccountBalance( accountID ) == 100.0 );
	assert( ! c.isOverdraftAllowed( accountID ) );
	assert( c.getOverdraftLimit( accountID ) == 0.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_overdraft_account )
{
	Controller c;
	int accountID = c.createOverdraftAccount( "Wasya", 100.0, 50.0 );

	assert( c.getAccountOwnerName( accountID ) == "Wasya" );
	assert( c.getAccountBalance( accountID ) == 100.0 );
	assert( c.isOverdraftAllowed( accountID ) );
	assert( c.getOverdraftLimit( accountID ) == 50.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_two_accounts_different_properties )
{
	Controller c;
	int WASYA_ID = c.createAccount( "Wasya", 100.0 );
	int PETYA_ID = c.createAccount( "Petya", 200.0 );

	assert( c.getAccountOwnerName( WASYA_ID ) == "Wasya" );
	assert( c.getAccountOwnerName( PETYA_ID ) == "Petya" );

	assert( c.getAccountBalance( WASYA_ID ) == 100.0 );
	assert( c.getAccountBalance( PETYA_ID ) == 200.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_create_two_accounts_for_same_owner )
{
	Controller c;
	c.createAccount( "Wasya", 100.0 );

	ASSERT_THROWS(
			c.createAccount( "Wasya", 200.0 )
		,	Messages::OwnerNameNotUnique
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_create_account_empty_name )
{
	Controller c;

	ASSERT_THROWS(
			c.createAccount( "", 0.0 )
		,	Messages::OwnerNameIsEmpty
	);

	ASSERT_THROWS(
			c.createOverdraftAccount( "", 0.0, 1.0 )
		,	Messages::OwnerNameIsEmpty
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_create_account_negative_initial_balance )
{
	Controller c;

	ASSERT_THROWS(
			c.createAccount( "Wasya", -1.0 )
		,	Messages::NegativeInitialBalance
	);

	ASSERT_THROWS(
			c.createOverdraftAccount( "Wasya", -1.0, 1.0 )
		,	Messages::NegativeInitialBalance
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_create_account_negative_overdraft_limit )
{
	Controller c;

	ASSERT_THROWS(
			c.createOverdraftAccount( "Wasya", 0.0, -1.0 )
		,	Messages::NegativeOverdraft
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_simple_deposit )
{
	Controller c;
	int WASYA_ID = c.createAccount( "Wasya",   0.0 );
	int PETYA_ID = c.createAccount( "Petya", 100.0 );

	c.deposit( WASYA_ID, 150.0 );

	assert( c.getAccountBalance( WASYA_ID ) == 150.0 );
	assert( c.getAccountBalance( PETYA_ID ) == 100.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_few_deposits )
{
	Controller c;
	int WASYA_ID = c.createAccount( "Wasya", 0.0 );
	int PETYA_ID = c.createAccount( "Petya", 100.0 );

	c.deposit( WASYA_ID, 70.0 );
	c.deposit( PETYA_ID, 20.0 );
	c.deposit( PETYA_ID, 25.0 );
	c.deposit( WASYA_ID, 40.0 );

	assert( c.getAccountBalance( WASYA_ID ) == 110.0 ); // 70 + 40
	assert( c.getAccountBalance( PETYA_ID ) == 145.0 ); // 100 + 20 + 25
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_deposit_zero )
{
	Controller c;
	int WASYA_ID = c.createAccount( "Wasya", 0.0 );

	ASSERT_THROWS(
			c.deposit( WASYA_ID, 0.0 )
		,	Messages::NonPositiveDeposit
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_deposit_negative )
{
	Controller c;
	int WASYA_ID = c.createAccount( "Wasya", 0.0 );

	ASSERT_THROWS(
			c.deposit( WASYA_ID, -1.0 )
		,	Messages::NonPositiveDeposit
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_simple_withdraw  )
{
	Controller c;
	int WASYA_ID = c.createAccount( "Wasya",  50.0 );
	int PETYA_ID = c.createAccount( "Petya", 100.0 );

	c.withdraw( WASYA_ID,  15.0 );
	c.withdraw( PETYA_ID, 100.0 );

	assert( c.getAccountBalance( WASYA_ID ) == 35.0 ); // 50 - 15
	assert( c.getAccountBalance( PETYA_ID ) ==  0.0 ); // 100 - 100
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_few_withdraws )
{
	Controller c;
	int WASYA_ID = c.createAccount( "Wasya", 50.0 );
	int PETYA_ID = c.createAccount( "Petya", 100.0 );

	c.withdraw( WASYA_ID, 15.0 );
	c.withdraw( PETYA_ID, 90.0 );
	c.withdraw( WASYA_ID, 25.0 );
	c.withdraw( PETYA_ID, 10.0 );

	assert( c.getAccountBalance( WASYA_ID ) == 10.0 ); // 50 - 15 - 25
	assert( c.getAccountBalance( PETYA_ID ) ==  0.0 ); // 100 - 90 - 10
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_withdraw_zero )
{
	Controller c;
	int WASYA_ID = c.createAccount( "Wasya", 50.0 );

	ASSERT_THROWS(
			c.withdraw( WASYA_ID, 0.0 )
		,	Messages::NonPositiveWithdrawal
	);

	assert( c.getAccountBalance( WASYA_ID ) == 50.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_withdraw_negative )
{
	Controller c;
	int WASYA_ID = c.createAccount( "Wasya", 50.0 );

	ASSERT_THROWS(
			c.withdraw( WASYA_ID, -10.0 )
		,	Messages::NonPositiveWithdrawal
	);

	assert( c.getAccountBalance( WASYA_ID ) == 50.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_withdraw_more_than_balance_on_simple_account )
{
	Controller c;
	int WASYA_ID = c.createAccount( "Wasya", 50.0 );

	ASSERT_THROWS(
			c.withdraw( WASYA_ID, 51.0 )
		,	Messages::WithdrawalLimitExceeded
	);

	assert( c.getAccountBalance( WASYA_ID ) == 50.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_withdraw_more_than_balance_within_overdraft_limit )
{
	Controller c;
	int WASYA_ID = c.createOverdraftAccount( "Wasya", 50.0, 20.0 );

	c.withdraw( WASYA_ID, 51.0 );

	assert( c.getAccountBalance( WASYA_ID ) == -1.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_withdraw_more_than_balance_on_the_overdraft_limit )
{
	Controller c;
	int WASYA_ID = c.createOverdraftAccount( "Wasya", 50.0, 20.0 );

	c.withdraw( WASYA_ID, 70.0 );

	assert( c.getAccountBalance( WASYA_ID ) == -20.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST( test_withdraw_more_than_balance_beyond_overdraft_limit )
{
	Controller c;
	int WASYA_ID = c.createOverdraftAccount( "Wasya", 50.0, 20.0 );

	ASSERT_THROWS(
			c.withdraw( WASYA_ID, 71.0 )
		,	Messages::WithdrawalLimitExceeded
	);

	assert( c.getAccountBalance( WASYA_ID ) == 50.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_transfer_simple_case )
{
	Controller c;
	int WASYA_ID = c.createAccount( "Wasya", 100.0 );
	int PETYA_ID = c.createAccount( "Petya",  50.0 );

	assert( c.getTotalBankDeposits() == 150.0 );

	c.transfer( WASYA_ID, PETYA_ID, 30.0 );

	assert( c.getAccountBalance( WASYA_ID ) == 70.0 );
	assert( c.getAccountBalance( PETYA_ID ) == 80.0 );

	assert( c.getTotalBankDeposits() == 150.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_transfer_more_than_balance_within_overdraft_limit )
{
	Controller c;
	int WASYA_ID = c.createOverdraftAccount( "Wasya", 100.0, 50.0 );
	int PETYA_ID = c.createAccount( "Petya", 50.0 );

	assert( c.getTotalBankDeposits() == 150.0 );
	assert( c.getTotalBankOverdrafts() == 0.0 );

	c.transfer( WASYA_ID, PETYA_ID, 120.0 );

	assert( c.getAccountBalance( WASYA_ID ) == -20.0 );
	assert( c.getAccountBalance( PETYA_ID ) == 170.0 );

	assert( c.getTotalBankDeposits() == 170.0 );
	assert( c.getTotalBankOverdrafts() == 20.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_transfer_more_than_balance_beyond_overdraft_limit )
{
	Controller c;
	int WASYA_ID = c.createOverdraftAccount( "Wasya", 100.0, 50.0 );
	int PETYA_ID = c.createAccount( "Petya", 50.0 );

	assert( c.getTotalBankDeposits() == 150.0 );
	assert( c.getTotalBankOverdrafts() == 0.0 );

	ASSERT_THROWS(
			c.transfer( WASYA_ID, PETYA_ID, 200.0 )
		,	Messages::WithdrawalLimitExceeded
	);

	assert( c.getAccountBalance( WASYA_ID ) == 100.0 );
	assert( c.getAccountBalance( PETYA_ID ) ==  50.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_transfer_negative_or_zero_amount )
{
	Controller c;
	int WASYA_ID = c.createOverdraftAccount( "Wasya", 100.0, 50.0 );
	int PETYA_ID = c.createAccount( "Petya", 50.0 );

	ASSERT_THROWS(
			c.transfer( WASYA_ID, PETYA_ID, -10.0 )
		,	Messages::NonPositiveTransfer
	);

	ASSERT_THROWS(
			c.transfer( WASYA_ID, PETYA_ID, 0.0 )
		,	Messages::NonPositiveTransfer
	);

}



/*****************************************************************************/


DECLARE_OOP_TEST ( test_totals_simple_cases )
{
	Controller c;

	assert( c.getTotalBankBalance() == 0.0 );
	assert( c.getTotalBankDeposits() == 0.0 );
	assert( c.getTotalBankOverdrafts() == 0.0 );
	
	c.createAccount( "Wasya", 100.0 );

	assert( c.getTotalBankBalance() == 100.0 );
	assert( c.getTotalBankDeposits() == 100.0 );
	assert( c.getTotalBankOverdrafts() == 0.0 );

	c.createAccount( "Petya", 200.0 );

	assert( c.getTotalBankBalance() == 300.0 );
	assert( c.getTotalBankDeposits() == 300.0 );
	assert( c.getTotalBankOverdrafts() == 0.0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_totals_with_overdrafts )
{
	Controller c;
	int WASYA_ID = c.createOverdraftAccount( "Wasya", 0.0, 50.0 );
	int PETYA_ID = c.createOverdraftAccount( "Petya", 0.0, 30.0 );

	assert( c.getTotalBankBalance() == 0.0 );
	assert( c.getTotalBankDeposits() == 0.0 );
	assert( c.getTotalBankOverdrafts() == 0.0 );

	c.withdraw( WASYA_ID, 20.0 );

	assert( c.getTotalBankBalance() == -20.0 );
	assert( c.getTotalBankDeposits() == 0.0 );
	assert( c.getTotalBankOverdrafts() == 20.0 );

	c.withdraw( PETYA_ID, 30.0 );

	assert( c.getTotalBankBalance() == -50.0 );
	assert( c.getTotalBankDeposits() == 0.0 );
	assert( c.getTotalBankOverdrafts() == 50.0 );

	c.deposit( WASYA_ID, 100.0 );

	assert( c.getTotalBankBalance() == 50.0 );
	assert( c.getTotalBankDeposits() == 80.0 );
	assert( c.getTotalBankOverdrafts() == 30.0 );

}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_operate_on_unknown_account )
{
	Controller c;

	const int RANDOM_ID = 175;

	ASSERT_THROWS(
			c.getAccountBalance( RANDOM_ID )
		,	Messages::UnknownAccountID
	);

	ASSERT_THROWS(
			c.getAccountOwnerName( RANDOM_ID )
		,	Messages::UnknownAccountID
	);

	ASSERT_THROWS(
			c.isOverdraftAllowed( RANDOM_ID )
		,	Messages::UnknownAccountID
	);

	ASSERT_THROWS(
			c.getOverdraftLimit( RANDOM_ID )
		,	Messages::UnknownAccountID
	);

	ASSERT_THROWS(
			c.deposit( RANDOM_ID, 100.0 )
		,	 Messages::UnknownAccountID
	);

	ASSERT_THROWS(
			c.withdraw( RANDOM_ID, 100.0 )
		,	Messages::UnknownAccountID
	);

	const int WASYA_ID = c.createAccount( "Wasya", 0.0 );

	ASSERT_THROWS(
			c.transfer( RANDOM_ID, WASYA_ID, 100.0 )
		,	Messages::UnknownAccountID
	);

	ASSERT_THROWS(
			c.transfer( WASYA_ID, RANDOM_ID, 100.0 )
		,	Messages::UnknownAccountID
	);
}


/*****************************************************************************/
