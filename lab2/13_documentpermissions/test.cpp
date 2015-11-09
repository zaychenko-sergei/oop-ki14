// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "controller.hpp"
#include "messages.hpp"

#include "testslib.hpp"

/*****************************************************************************/


void createCommonConfiguration ( Controller & c )
{
	c.addUser( "winstons", "Winston Smith" );
	c.addUser( "julia", "Julia" );
	c.addUser( "emmanuelg", "Emmanuel Goldstein" );

	const int DOC_ID1 = 1, DOC_ID2 = 2, DOC_ID3 = 3, DOC_ID4 = 4;

	c.addDocument( DOC_ID1, "Daily Telegraph #16.txt", "/party/minitruth/magazine/dt/1984", OwnershipRights::ReadAndWrite );
	c.addDocument( DOC_ID2, "Guardian #22.txt", "/party/minitruth/magazine/guardian/1984", OwnershipRights::NoAccess );
	c.addDocument( DOC_ID3, "The Sun #14.txt", "/party/minitruth/magazine/sun/1984", OwnershipRights::ReadOnly );
	c.addDocument( DOC_ID4, "Resistance.txt", "/party/minilove/rooms/101", OwnershipRights::NoAccess );

	c.addDocumentRightsForUser( "winstons", DOC_ID1, OwnershipRights::ReadAndWrite );
	c.addDocumentRightsForUser( "winstons", DOC_ID2, OwnershipRights::ReadAndWrite );
	c.addDocumentRightsForUser( "winstons", DOC_ID3, OwnershipRights::ReadAndWrite );

	c.addDocumentRightsForUser( "julia", DOC_ID2, OwnershipRights::ReadOnly );
	c.addDocumentRightsForUser( "julia", DOC_ID3, OwnershipRights::ReadAndWrite );

}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_document_trace_properties )
{
	const int DOC_UID = 12345;

	Controller c;
	c.addDocument( DOC_UID, "passwords.txt", "D:\\Work\\Important stuff", OwnershipRights::ReadAndWrite );

	assert( c.getDocumentName( DOC_UID ) == "passwords.txt" );
	assert( c.getDocumentPath( DOC_UID ) == "D:\\Work\\Important stuff" );
	assert( c.getDocumentDefaultRights( DOC_UID ) == OwnershipRights::ReadAndWrite );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_document_empty_name )
{
	const int DOC_UID = 12345;

	Controller c;
	ASSERT_THROWS(
			c.addDocument( DOC_UID, "", "D:\\Work\\Important stuff", OwnershipRights::ReadAndWrite )
		,	Messages::DocumentNameIsEmpty
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_document_empty_path )
{
	const int DOC_UID = 12345;

	Controller c;
	ASSERT_THROWS(
			c.addDocument( DOC_UID, "passwords.txt", "", OwnershipRights::NoAccess )
		,	Messages::DocumentPathIsEmpty
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_document_duplicating_id )
{
	const int DOC_UID = 12345;
	Controller c;

	c.addDocument( DOC_UID, "passwords.txt", "C:\\Work\\Important stuff", OwnershipRights::NoAccess );

	ASSERT_THROWS(
			c.addDocument( DOC_UID, "emails.txt", "C:\\Friends", OwnershipRights::ReadOnly )
		,	Messages::DocumentAlreadyExists
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_document_duplicating_file_name_and_path_name )
{
	const int DOC_UID1 = 1, DOC_UID2 = 2, DOC_UID3 = 3;
	Controller c;

	c.addDocument( DOC_UID1, "passwords.txt", "C:\\Work\\Important stuff", OwnershipRights::NoAccess );
	c.addDocument( DOC_UID3, "passwords.txt", "C:\\Friends", OwnershipRights::ReadAndWrite );
	c.addDocument( DOC_UID2, "interests.txt", "C:\\Friends", OwnershipRights::ReadOnly );

}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_user_trace_properties )
{
	Controller c;

	c.addUser( "test", "Test Account" );

	assert( c.getUserFullName( "test" ) == "Test Account" );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_user_empty_login )
{
	Controller c;

	ASSERT_THROWS(
			c.addUser( "", "Test Account" )
		,	Messages::UserLoginIsEmpty
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_user_empty_full_name )
{
	Controller c;

	ASSERT_THROWS(
			c.addUser( "test", "" )
		,	Messages::UserFullNameEmpty
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_user_with_existing_login )
{
	Controller c;

	c.addUser( "test", "Test Account" );

	ASSERT_THROWS(
			c.addUser( "test", "Official Bulletproof Test" )
		,	Messages::UserLoginAlreadyExists
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_user_with_existing_full_name )
{
	Controller c;

	c.addUser( "test", "Test Account" );
	c.addUser( "test_acc", "Test Account" );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_adding_document_rights )
{
	Controller c;

	c.addUser( "winstons", "Winston Smith" );

	const int DOC_ID1 = 1, DOC_ID2 = 2, DOC_ID3 = 3;

	c.addDocument( DOC_ID1, "Daily Telegraph #16.txt", "/party/minitruth/magazine/dt/1984", OwnershipRights::ReadAndWrite );
	c.addDocument( DOC_ID2, "Guardian #22.txt", "/party/minitruth/magazine/guardian/1984", OwnershipRights::NoAccess );
	c.addDocument( DOC_ID3, "The Sun #14.txt", "/party/minitruth/magazine/sun/1984", OwnershipRights::ReadOnly );

	c.addDocumentRightsForUser( "winstons", DOC_ID1, OwnershipRights::ReadAndWrite );
	c.addDocumentRightsForUser( "winstons", DOC_ID2, OwnershipRights::ReadOnly );
	c.addDocumentRightsForUser( "winstons", DOC_ID3, OwnershipRights::ReadAndWrite );

	assert( c.getDocumentRightsForUser( "winstons", DOC_ID1 ) == OwnershipRights::ReadAndWrite );
	assert( c.getDocumentRightsForUser( "winstons", DOC_ID2 ) == OwnershipRights::ReadOnly );
	assert( c.getDocumentRightsForUser( "winstons", DOC_ID3 ) == OwnershipRights::ReadAndWrite );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_adding_document_for_unexisting_user )
{
	Controller c;

	c.addUser( "winstons", "Winston Smith" );

	const int DOC_ID1 = 1;

	c.addDocument( DOC_ID1, "Daily Telegraph #16.txt", "/party/minitruth/magazine/dt/1984", OwnershipRights::ReadAndWrite );

	ASSERT_THROWS(
			c.addDocumentRightsForUser( "julia", DOC_ID1, OwnershipRights::ReadAndWrite )
		,	Messages::UserLoginDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_adding_document_for_empty_name_user )
{
	Controller c;

	c.addUser( "winstons", "Winston Smith" );

	const int DOC_ID1 = 1;

	c.addDocument( DOC_ID1, "Daily Telegraph #16.txt", "/party/minitruth/magazine/dt/1984", OwnershipRights::ReadAndWrite );

	ASSERT_THROWS(
			c.addDocumentRightsForUser( "", DOC_ID1, OwnershipRights::ReadAndWrite )
		,	Messages::UserLoginDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_adding_unexisting_document_rights )
{
	Controller c;

	c.addUser( "winstons", "Winston Smith" );

	const int DOC_ID1 = 1, DOC_ID2 = 2;

	c.addDocument( DOC_ID1, "Daily Telegraph #16.txt", "/party/minitruth/magazine/dt/1984", OwnershipRights::ReadAndWrite );

	ASSERT_THROWS(
			c.addDocumentRightsForUser( "winstons", DOC_ID2, OwnershipRights::ReadAndWrite )
		,	Messages::DocumentDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_adding_already_existing_document_rights )
{
	Controller c;

	c.addUser( "winstons", "Winston Smith" );

	const int DOC_ID1 = 1, DOC_ID2 = 2;

	c.addDocument( DOC_ID1, "Daily Telegraph #16.txt", "/party/minitruth/magazine/dt/1984", OwnershipRights::ReadAndWrite );

	c.addDocumentRightsForUser( "winstons", DOC_ID1, OwnershipRights::ReadAndWrite );

	ASSERT_THROWS(
			c.addDocumentRightsForUser( "winstons", DOC_ID1, OwnershipRights::NoAccess )
		,	Messages::DocumentRightsAlreadyDefined
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_set_document_rights )
{
	Controller c;

	c.addUser( "winstons", "Winston Smith" );

	const int DOC_ID1 = 1;

	c.addDocument( DOC_ID1, "Daily Telegraph #16.txt", "/party/minitruth/magazine/dt/1984", OwnershipRights::ReadAndWrite );

	c.addDocumentRightsForUser( "winstons", DOC_ID1, OwnershipRights::ReadAndWrite );
	c.changeDocumentRightsForUser( "winstons", DOC_ID1, OwnershipRights::NoAccess );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_set_document_rights_for_unexisting_document )
{
	Controller c;

	c.addUser( "winstons", "Winston Smith" );

	const int DOC_ID1 = 1, DOC_ID2 = 2;

	c.addDocument( DOC_ID1, "Daily Telegraph #16.txt", "/party/minitruth/magazine/dt/1984", OwnershipRights::ReadAndWrite );

	c.addDocumentRightsForUser( "winstons", DOC_ID1, OwnershipRights::ReadAndWrite );

	ASSERT_THROWS(
			c.changeDocumentRightsForUser( "winstons", DOC_ID2, OwnershipRights::NoAccess )
		,	Messages::DocumentDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_set_document_rights_for_unexisting_user )
{
	Controller c;

	c.addUser( "winstons", "Winston Smith" );

	const int DOC_ID1 = 1;

	c.addDocument( DOC_ID1, "Daily Telegraph #16.txt", "/party/minitruth/magazine/dt/1984", OwnershipRights::ReadAndWrite );

	c.addDocumentRightsForUser( "winstons", DOC_ID1, OwnershipRights::ReadAndWrite );

	ASSERT_THROWS(
			c.changeDocumentRightsForUser( "julia", DOC_ID1, OwnershipRights::NoAccess )
		,	Messages::UserLoginDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_set_document_rights_for_empty_user_name )
{
	Controller c;

	c.addUser( "winstons", "Winston Smith" );

	const int DOC_ID1 = 1;

	c.addDocument( DOC_ID1, "Daily Telegraph #16.txt", "/party/minitruth/magazine/dt/1984", OwnershipRights::ReadAndWrite );

	c.addDocumentRightsForUser( "winstons", DOC_ID1, OwnershipRights::ReadAndWrite );

	ASSERT_THROWS(
			c.changeDocumentRightsForUser( "", DOC_ID1, OwnershipRights::NoAccess )
		,	Messages::UserLoginDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_erase_document_rights )
{
	Controller c;

	c.addUser( "winstons", "Winston Smith" );

	const int DOC_ID1 = 1, DOC_ID2 = 2, DOC_ID3 = 3;

	c.addDocument( DOC_ID1, "Daily Telegraph #16.txt", "/party/minitruth/magazine/dt/1984", OwnershipRights::ReadAndWrite );
	c.addDocument( DOC_ID2, "Guardian #22.txt", "/party/minitruth/magazine/guardian/1984", OwnershipRights::ReadOnly );
	c.addDocument( DOC_ID3, "The Sun #14.txt", "/party/minitruth/magazine/sun/1984", OwnershipRights::ReadOnly );

	c.addDocumentRightsForUser( "winstons", DOC_ID1, OwnershipRights::ReadAndWrite );
	c.addDocumentRightsForUser( "winstons", DOC_ID2, OwnershipRights::ReadAndWrite );
	c.addDocumentRightsForUser( "winstons", DOC_ID3, OwnershipRights::ReadAndWrite );

	c.eraseDocumentRightsForUser( "winstons", DOC_ID2 );

	assert( c.getDocumentRightsForUser( "winstons", DOC_ID1 ) == OwnershipRights::ReadAndWrite );
	assert( c.getDocumentRightsForUser( "winstons", DOC_ID2 ) == OwnershipRights::ReadOnly );
	assert( c.getDocumentRightsForUser( "winstons", DOC_ID3 ) == OwnershipRights::ReadAndWrite );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_erase_document_rights_with_empty_login )
{
	Controller c;

	c.addUser( "winstons", "Winston Smith" );

	const int DOC_ID1 = 1;

	c.addDocument( DOC_ID1, "Daily Telegraph #16.txt", "/party/minitruth/magazine/dt/1984", OwnershipRights::ReadOnly );

	c.addDocumentRightsForUser( "winstons", DOC_ID1, OwnershipRights::ReadAndWrite );

	ASSERT_THROWS(
			c.eraseDocumentRightsForUser( "", DOC_ID1 )
		,	Messages::UserLoginDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_erase_document_rights_with_unexisting_login )
{
	Controller c;

	c.addUser( "winstons", "Winston Smith" );

	const int DOC_ID1 = 1;

	c.addDocument( DOC_ID1, "Daily Telegraph #16.txt", "/party/minitruth/magazine/dt/1984", OwnershipRights::ReadOnly );

	c.addDocumentRightsForUser( "winstons", DOC_ID1, OwnershipRights::ReadAndWrite );

	ASSERT_THROWS(
			c.eraseDocumentRightsForUser( "julia", DOC_ID1 )
		,	Messages::UserLoginDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_erase_document_rights_with_unexisting_document_id )
{
	Controller c;

	c.addUser( "winstons", "Winston Smith" );

	const int DOC_ID1 = 1, DOC_ID2 = 2;

	c.addDocument( DOC_ID1, "Daily Telegraph #16.txt", "/party/minitruth/magazine/dt/1984", OwnershipRights::ReadOnly );

	c.addDocumentRightsForUser( "winstons", DOC_ID1, OwnershipRights::ReadAndWrite );

	ASSERT_THROWS(
			c.eraseDocumentRightsForUser( "winstons", DOC_ID2 )
		,	Messages::DocumentDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_user_permissions_report_query )
{
	Controller c;

	createCommonConfiguration( c );

	Controller::AllRights expectedResult =
		{
				{
						"winstons"
					,	{
								{ 1, OwnershipRights::ReadAndWrite }
							,	{ 2, OwnershipRights::ReadAndWrite }
							,	{ 3, OwnershipRights::ReadAndWrite }
							,	{ 4, OwnershipRights::NoAccess }
						}
				}
			,	{
						"julia"
					,	{
								{ 1, OwnershipRights::ReadAndWrite }
							,	{ 2, OwnershipRights::ReadOnly }
							,	{ 3, OwnershipRights::ReadAndWrite }
							,	{ 4, OwnershipRights::NoAccess }
						}
				}
			,	{
						"emmanuelg"
					,	{
								{ 1, OwnershipRights::ReadAndWrite }
							,	{ 2, OwnershipRights::NoAccess }
							,	{ 3, OwnershipRights::ReadOnly }
							,	{ 4, OwnershipRights::NoAccess }
						}
				}
		};

	assert( expectedResult == c.getUserPermissionsReport() );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_documents_not_having_permitted_users_query )
{
	Controller c;

	createCommonConfiguration( c );

	Controller::DocumentsInfo expectedResult =
		{
			{ 4 , "Resistance.txt" }
		};

	assert( expectedResult == c.getDocumentsNotHavingPermittedUsers() );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_users_not_having_permitted_documents_query )
{
	Controller c;

	createCommonConfiguration( c );
	c.addDocumentRightsForUser( "emmanuelg", 1, OwnershipRights::NoAccess );
	c.addDocumentRightsForUser( "emmanuelg", 3, OwnershipRights::NoAccess );

	std::unordered_set< std::string > expectedResult = { "emmanuelg" };

	assert( expectedResult == c.getUsersNotHavingPermittedDocuments() );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_documents_having_multiple_write_users_query )
{
	Controller c;

	createCommonConfiguration( c );

	Controller::DocumentsInfo expectedResult =
		{
			{ 1, "Daily Telegraph #16.txt" },
			{ 3 , "The Sun #14.txt" }
		};

	assert( expectedResult == c.getDocumentsHavingMultipleWriteUsers() );
}


/*****************************************************************************/
