// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _TESTSLIB_HPP_
#define _TESTSLIB_HPP_

/*****************************************************************************/

#include <cassert>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

/*****************************************************************************/

typedef void ( * TestProcedure )();

/*****************************************************************************/

class TestsRunner
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

    void addTest ( std::string const & _tpName, TestProcedure _tp )
    {
        m_testProcedures.push_back( std::make_pair( _tpName, _tp ) );
    }

/*-----------------------------------------------------------------*/

    void runTests ()
    {
        assert( ! m_testProcedures.empty() );

        std::cout << "Running " << m_testProcedures.size() << " test(s):\n";

        int counter = 1;
        std::for_each(
                m_testProcedures.begin()
            ,   m_testProcedures.end()
            ,   [ & ] ( std::pair< std::string, TestProcedure > const & _test ) 
                { 
                    std::cout << "Test #" << counter << " \"" << _test.first << "\" ";
                    ( * _test.second )();
                    std::cout << '\n';
                    ++ counter;
                }
        );

        std::cout << "Finished running tests.\n";
    }

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

    std::vector< std::pair< std::string, TestProcedure > > m_testProcedures;
    
/*-----------------------------------------------------------------*/

};


/*****************************************************************************/


static TestsRunner gs_TestsRunner;


/*****************************************************************************/


class TestProcedureWrapper
{
public:
    TestProcedureWrapper ( std::string const & _tpName, TestProcedure _tp )
    {
        gs_TestsRunner.addTest( _tpName, _tp );
    }
};


/*****************************************************************************/


#define DECLARE_OOP_TEST( arg_testProcedureName )                                                                        \
    void arg_testProcedureName ();                                                                                        \
    static TestProcedureWrapper gs_wrapper_##arg_testProcedureName( #arg_testProcedureName, & arg_testProcedureName );    \
    void arg_testProcedureName ()


/*****************************************************************************/

int main ()
{
    gs_TestsRunner.runTests();
}

/*****************************************************************************/

#endif //  _TESTSLIB_HPP_
