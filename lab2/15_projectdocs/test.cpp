// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

/*****************************************************************************/

#include "controller.hpp"
#include "messages.hpp"

#include "testslib.hpp"

/*****************************************************************************/


void createCommonConfiguration ( Controller & c )
{
	c.addProject( "Low-Risk Project" );

	c.addDocumentForProject( "Low-Risk Project", "Initiation", "" );
	c.addDocumentForProject( "Low-Risk Project", "Planning", "ISO/IEC 27001:2005" );
	c.addDocumentForProject( "Low-Risk Project", "Executing", "" );
	c.addDocumentForProject( "Low-Risk Project", "Monitoring & Controlling", "" );
	c.addDocumentForProject( "Low-Risk Project", "Closing", "" );

	c.addProject( "Medium-Risk Project" );

	c.addDocumentForProject( "Medium-Risk Project", "Initiation", "" );
	c.addDocumentForProject( "Medium-Risk Project", "Planning", "ISO/IEC 27001:2005" );
	c.addDocumentForProject( "Medium-Risk Project", "Executing", "ISO/IEC 27001:2005" );
	c.addDocumentForProject( "Medium-Risk Project", "Monitoring & Controlling", "" );
	c.addDocumentForProject( "Medium-Risk Project", "Closing", "" );

	c.addStandardForProject( "Medium-Risk Project", "ISO/IEC 27001:2005" );
	c.addStandardForProject( "Medium-Risk Project", "TOGAF v9.1" );

	c.addProject( "High-Risk Project" );

	c.addDocumentForProject( "High-Risk Project", "Initiation", "TOGAF v9.1" );
	c.addDocumentForProject( "High-Risk Project", "Planning", "ISO/IEC 27001:2005" );
	c.addDocumentForProject( "High-Risk Project", "Executing", "ISO/IEC 27001:2005" );
	c.addDocumentForProject( "High-Risk Project", "Monitoring & Controlling", "TOGAF v9.1" );
	c.addDocumentForProject( "High-Risk Project", "Closing", "TOGAF v9.1" );


	c.addStandardForProject( "High-Risk Project", "ISO/IEC 27001:2005" );
	c.addStandardForProject( "High-Risk Project", "TOGAF v9.1" );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_project )
{
	Controller c;

	c.addProject( "test" );

	assert( c.getProjectsCount() == 1 );
	assert( c.hasProject( "test" ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_multiple_projects )
{
	Controller c;

	c.addProject( "easy" );
	c.addProject( "medium" );
	c.addProject( "hard" );

	assert( c.getProjectsCount() == 3 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_duplicating_project )
{
	Controller c;

	c.addProject( "render" );

	ASSERT_THROWS(
			c.addProject( "render" )
		,	Messages::ProjectAlreadyExists
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_project_with_empty_name )
{
	Controller c;

	ASSERT_THROWS(
			c.addProject( "" )
		,	Messages::ProjectNameIsEmpty
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_document_trace_properties )
{
	Controller c;

	c.addProject( "render" );

	c.addDocumentForProject( "render", "shadows.cc", "CPP11" );

	assert( c.hasProjectDocument( "render", "shadows.cc" ) );
	assert( c.getProjectDocumentStandard( "render", "shadows.cc" ) == "CPP11" );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_document_with_empty_standard )
{
	Controller c;

	c.addProject( "render" );

	c.addDocumentForProject( "render", "shadows.cc", "" );

	assert( c.hasProjectDocument( "render", "shadows.cc" ) );
	assert( c.getProjectDocumentStandard( "render", "shadows.cc" ) == "" );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_document_with_empty_name )
{
	Controller c;

	c.addProject( "render" );

	ASSERT_THROWS(
			c.addDocumentForProject( "render", "", "CPP11" )
		,	Messages::DocumentNameIsEmpty
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_document_with_empty_project )
{
	Controller c;

	c.addProject( "render" );

	ASSERT_THROWS(
			c.addDocumentForProject( "", "shadows.cc", "CPP11" )
		,	Messages::ProjectDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_document_for_unexisting_project )
{
	Controller c;

	c.addProject( "render" );

	ASSERT_THROWS(
			c.addDocumentForProject( "parser", "yacc.y", "Bison" )
		,	Messages::ProjectDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_document_with_duplicating_name )
{
	Controller c;

	c.addProject( "render" );

	c.addDocumentForProject( "render", "shadows.cc", "CPP11" );

	ASSERT_THROWS(
			c.addDocumentForProject( "render", "shadows.cc", "C99" )
		,	Messages::DocumentAlreadyExistsInProject
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_standard_for_project )
{
	Controller c;

	c.addProject( "render" );

	c.addStandardForProject( "render", "CPP11" );

	assert( c.hasProjectStandard( "render", "CPP11" ) );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_standard_for_empty_project_name )
{
	Controller c;

	c.addProject( "render" );

	ASSERT_THROWS(
			c.addStandardForProject( "", "CPP11" )
		,	Messages::ProjectDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_standard_for_unexisting_project_name )
{
	Controller c;

	c.addProject( "render" );

	ASSERT_THROWS(
			c.addStandardForProject( "parser", "CPP11" )
		,	Messages::ProjectDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_standard_for_empty_standard_name )
{
	Controller c;

	c.addProject( "render" );

	ASSERT_THROWS(
			c.addStandardForProject( "render", "" )
		,	Messages::StandardNameIsEmpty
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_duplicating_standard )
{
	Controller c;

	c.addProject( "render" );

	c.addStandardForProject( "render", "CPP11" );

	ASSERT_THROWS(
			c.addStandardForProject( "render", "CPP11" )
		,	Messages::StandardAlreadyExistsInProject
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_multiple_documents )
{
	Controller c;

	c.addProject( "Project Docs" );

	c.addDocumentForProject( "Project Docs", "Development", "ISO/IEC 27001:2005" );
	c.addDocumentForProject( "Project Docs", "Maintenance", "TOGAF v9.1" );
	c.addDocumentForProject( "Project Docs", "Review", "ISO/IEC 27001:2005" );
	c.addDocumentForProject( "Project Docs", "Implementation", "ISO/IEC 27001:2005" );

	assert( c.getProjectDocumentsCount( "Project Docs" ) == 4 );
	assert( c.getProjectStandardsCount( "Project Docs" ) == 0 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_multiple_standards )
{
	Controller c;

	c.addProject( "Project Docs" );

	c.addStandardForProject( "Project Docs", "ISO/IEC 27001:2005" );
	c.addStandardForProject( "Project Docs", "TOGAF v9.1" );

	assert( c.getProjectDocumentsCount( "Project Docs" ) == 0 );
	assert( c.getProjectStandardsCount( "Project Docs" ) == 2 );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_documents_count_with_empty_project_name )
{
	Controller c;

	c.addProject( "Project Docs" );

	ASSERT_THROWS(
			c.getProjectDocumentsCount( "" )
		,	Messages::ProjectDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_create_documents_count_with_unexisting_project_name )
{
	Controller c;

	c.addProject( "Project Docs" );

	ASSERT_THROWS(
			c.getProjectDocumentsCount( "project docs" )
		,	Messages::ProjectDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_has_project_document_with_empty_project_name )
{
	Controller c;

	c.addProject( "render" );

	c.addDocumentForProject( "render", "shadows.cc", "" );

	ASSERT_THROWS(
			assert( c.hasProjectDocument( "", "shadows.cc" ) )
		,	Messages::ProjectDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_has_project_document_with_unexisting_project_name )
{
	Controller c;

	c.addProject( "render" );

	c.addDocumentForProject( "render", "shadows.cc", "" );

	ASSERT_THROWS(
			assert( c.hasProjectDocument( "Render", "shadows.cc" ) )
		,	Messages::ProjectDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_project_document_standard_with_empty_project_name )
{
	Controller c;

	c.addProject( "render" );

	c.addDocumentForProject( "render", "shadows.cc", "CPP11" );

	ASSERT_THROWS(
			c.getProjectDocumentStandard( "", "shadows.cc" )
		,	Messages::ProjectDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_get_project_document_standard_with_unexisting_project_name )
{
	Controller c;

	c.addProject( "render" );

	c.addDocumentForProject( "render", "shadows.cc", "CPP11" );

	ASSERT_THROWS(
			c.getProjectDocumentStandard( "Render", "shadows.cc" )
		,	Messages::ProjectDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_has_project_standard_with_empty_project_name )
{
	Controller c;

	c.addProject( "Docs" );

	c.addStandardForProject( "Docs", "ISO/IEC 27001:2005" );

	ASSERT_THROWS(
			assert( c.hasProjectStandard( "", "ISO/IEC 27001:2005" ) )
		,	Messages::ProjectDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_has_project_standard_with_unexisting_project_name )
{
	Controller c;

	c.addProject( "Docs" );

	c.addStandardForProject( "Docs", "ISO/IEC 27001:2005" );

	ASSERT_THROWS(
			assert( c.hasProjectStandard( "docs", "ISO/IEC 27001:2005" ) )
		,	Messages::ProjectDoesNotExist
	);
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_has_project_standard_with_empty_standard_name )
{
	Controller c;

	c.addProject( "Docs" );

	c.addStandardForProject( "Docs", "ISO/IEC 27001:2005" );

	assert( c.hasProjectStandard( "Docs", "" ) == false );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_project_standards_used_query )
{
	Controller c;

	createCommonConfiguration( c );

	c.addStandardForProject( "Low-Risk Project", "ISO/IEC 27001:2005" );

	Controller::StandardNames expectedResult = { "ISO/IEC 27001:2005" };

	assert( c.getProjectStandardsUsed() == expectedResult );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_project_with_all_needed_standard_documents_query )
{
	Controller c;

	createCommonConfiguration( c );

	Controller::ProjectNames expectedResult = { "Low-Risk Project", "High-Risk Project" };

	assert( c.getProjectsWithAllNeededStandardDocuments() == expectedResult );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_projects_not_having_standard_document_query )
{
	Controller c;

	createCommonConfiguration( c );

	Controller::ProjectNames expectedResult = { "Low-Risk Project", "Medium-Risk Project" };

	assert( c.getProjectsNotHavingStandardDocument( "TOGAF v9.1" ) == expectedResult );
}


/*****************************************************************************/


DECLARE_OOP_TEST ( test_projects_get_most_popular_standard_query )
{
	Controller c;

	createCommonConfiguration( c );

	std::string expectedResult = "ISO/IEC 27001:2005";

	assert( c.getMostPopularStandard() == expectedResult );
}


/*****************************************************************************/
