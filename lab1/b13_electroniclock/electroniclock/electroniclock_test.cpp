// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "testslib.hpp"

#include "electroniclock.hpp"

/*****************************************************************************/


DECLARE_OOP_TEST( electroniclock_test_constructor )
{
	ElectronicLock lock( 123 );
	assert( lock.isInProgrammingMode() );
}


/*****************************************************************************/


DECLARE_OOP_TEST( electroniclock_test_toggle_programming_mode )
{
	ElectronicLock lock( 123 );

	bool res = lock.toggleProgrammingMode( 123 );
	assert( res );
	assert( ! lock.isInProgrammingMode() );

	res &= lock.toggleProgrammingMode( 123 );
	assert( res );
	assert( lock.isInProgrammingMode() );

	res = lock.toggleProgrammingMode( 54321 /* wrong */ );
	assert( ! res );
	assert( lock.isInProgrammingMode() );
}


/*****************************************************************************/


DECLARE_OOP_TEST( electroniclock_test_register_single_code )
{
	ElectronicLock lock( 123 );
	lock.registerCode( 11111 );
	lock.toggleProgrammingMode( 123 );

	bool accepted = lock.tryUnlocking( 11111 );
	assert( accepted );

	accepted = lock.tryUnlocking( 22222 );
	assert( ! accepted );
}


/*****************************************************************************/


DECLARE_OOP_TEST( electroniclock_test_register_few_codes )
{
	ElectronicLock lock( 123 );
	lock.registerCode( 11111 );
	lock.registerCode( 22222 );
	lock.registerCode( 33333 );
	lock.toggleProgrammingMode( 123 );

	bool accepted = lock.tryUnlocking( 11111 );
	assert( accepted );

	accepted = lock.tryUnlocking( 22222 );
	assert( accepted );

	accepted = lock.tryUnlocking( 33333 );
	assert( accepted );

	accepted = lock.tryUnlocking( 44444 );
	assert( ! accepted );
}


/*****************************************************************************/


DECLARE_OOP_TEST( electroniclock_test_register_unregister )
{
	ElectronicLock lock( 123 );
	lock.registerCode( 11111 );
	lock.registerCode( 22222 );
	lock.registerCode( 33333 );
	lock.toggleProgrammingMode( 123 );

	bool accepted;
	accepted = lock.tryUnlocking( 11111 );
	assert( accepted );
	accepted = lock.tryUnlocking( 22222 );
	assert( accepted );
	accepted = lock.tryUnlocking( 33333 );
	assert( accepted );

	lock.toggleProgrammingMode( 123 );
	lock.unregisterCode( 22222 );
	lock.toggleProgrammingMode( 123 );

	accepted = lock.tryUnlocking( 11111 );
	assert( accepted );
	accepted = lock.tryUnlocking( 22222 );
	assert( ! accepted );
	accepted = lock.tryUnlocking( 33333 );
	assert( accepted );
}


/*****************************************************************************/


DECLARE_OOP_TEST( electroniclock_test_register_duplicate_code )
{
	ElectronicLock lock( 123 );
	lock.registerCode( 11111 );
	lock.registerCode( 22222 );
	lock.registerCode( 22222 );
	lock.toggleProgrammingMode( 123 );

	bool accepted;
	accepted = lock.tryUnlocking( 11111 );
	assert( accepted );
	accepted = lock.tryUnlocking( 22222 );
	assert( accepted );
}


/*****************************************************************************/


DECLARE_OOP_TEST( electroniclock_test_trying_changes_without_programming_mode )
{
	ElectronicLock lock( 123 );
	lock.registerCode( 11111 );
	lock.toggleProgrammingMode( 123 );

	try
	{
		lock.registerCode( 22222 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Not in programming mode" ) );
	}

	try
	{
		lock.unregisterCode( 11111 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Not in programming mode" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( electroniclock_test_trying_remove_unregistered_code )
{
	ElectronicLock lock( 123 );
	lock.registerCode( 11111 );

	lock.unregisterCode( 22222 );

	lock.toggleProgrammingMode( 123 );
	
	bool accepted;
	accepted = lock.tryUnlocking( 11111 );
	assert( accepted );
	accepted = lock.tryUnlocking( 22222 );
	assert( ! accepted );
}


/*****************************************************************************/


DECLARE_OOP_TEST( electroniclock_test_change_programming_code )
{
	ElectronicLock lock( 123 );
	lock.changeProgrammingCode( 54321 );
	assert( lock.isInProgrammingMode() );

	bool res = lock.toggleProgrammingMode( 54321 );
	assert( res );
	assert( ! lock.isInProgrammingMode() );

	res = lock.toggleProgrammingMode( 123 );
	assert( ! res );
	assert( ! lock.isInProgrammingMode() );
}


/*****************************************************************************/


DECLARE_OOP_TEST( electroniclock_test_change_programming_code_during_operations )
{
	ElectronicLock lock( 123 );
	lock.toggleProgrammingMode( 123 );
	assert( ! lock.isInProgrammingMode() );

	try
	{
		lock.changeProgrammingCode( 54321 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Not in programming mode" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( electroniclock_test_try_unlocking_during_programming )
{
	ElectronicLock lock( 123 );
	lock.registerCode( 12345 );
	assert( lock.isInProgrammingMode() );

	try
	{
		lock.tryUnlocking( 12345 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Not in operational mode" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( electroniclock_test_try_unlocking_via_string )
{
	ElectronicLock lock( 123 );
	lock.registerCode( 12345 );
	lock.toggleProgrammingMode( 123 );

	bool accepted;
	accepted = lock.tryUnlocking( "12345" );
	assert( accepted );
	accepted = lock.tryUnlocking( "54321" );
	assert( ! accepted );

	try
	{
		lock.tryUnlocking( "I'm a bad key" );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Bad format" ) );
	}
}


/*****************************************************************************/


DECLARE_OOP_TEST( electroniclock_test_equality_inequality )
{
	ElectronicLock lock1( 123 );
	lock1.registerCode( 11111 );
	lock1.registerCode( 22222 );

	ElectronicLock lock2( 123 );
	lock2.registerCode( 11111 );
	lock2.registerCode( 22222 );

	ElectronicLock lock3( 123 );
	lock3.registerCode( 11111 );
	lock3.registerCode( 22222 );
	lock3.registerCode( 33333 );

	ElectronicLock lock4( 234 );
	lock4.registerCode( 11111 );
	lock4.registerCode( 22222 );

	assert( lock1 == lock2 );
	assert( !( lock1 != lock2 ) );

	assert( lock1 != lock3 );
	assert( !( lock1 == lock3 ) );

	assert( lock1 != lock4 );
	assert( !( lock1 == lock4 ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST( electroniclock_test_copying_moving )
{
	ElectronicLock lock1( 123 );
	lock1.registerCode( 11111 );
	lock1.registerCode( 22222 );
	lock1.toggleProgrammingMode( 123 );

	ElectronicLock lock2 = lock1;
	assert( ! lock2.isInProgrammingMode() );
	
	bool accepted;
	accepted = lock2.tryUnlocking( 11111 );
	assert( accepted );
	accepted = lock2.tryUnlocking( 22222 );
	assert( accepted );
	accepted = lock2.tryUnlocking( 33333 );
	assert( ! accepted );

	ElectronicLock lock3( 456 );
	lock3 = lock2;
	assert( ! lock3.isInProgrammingMode() );

	accepted = lock3.tryUnlocking( 11111 );
	assert( accepted );
	accepted = lock3.tryUnlocking( 22222 );
	assert( accepted );
	accepted = lock3.tryUnlocking( 33333 );
	assert( ! accepted );

	ElectronicLock lock4 = std::move( lock3 );

	accepted = lock4.tryUnlocking( 11111 );
	assert( accepted );
	accepted = lock4.tryUnlocking( 22222 );
	assert( accepted );
	accepted = lock4.tryUnlocking( 33333 );
	assert( ! accepted );
	accepted = lock3.tryUnlocking( 11111 );
	assert( !accepted );
	accepted = lock3.tryUnlocking( 22222 );
	assert( !accepted );
	accepted = lock3.tryUnlocking( 33333 );
	assert( !accepted );

	ElectronicLock lock5( 123 );
	lock5.registerCode( 33333 );
	lock5.toggleProgrammingMode( 123 );

	lock2 = std::move( lock5 );

	accepted = lock2.tryUnlocking( 33333 );
	assert( accepted );
	accepted = lock2.tryUnlocking( 22222 );
	assert( !accepted );
	accepted = lock5.tryUnlocking( 33333 );
	assert( !accepted );
}


/*****************************************************************************/
