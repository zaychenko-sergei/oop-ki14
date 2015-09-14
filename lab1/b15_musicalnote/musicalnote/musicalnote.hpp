// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MUSICALNOTE_HPP_
#define _MUSICALNOTE_HPP_

/*****************************************************************************/


class MusicalNote
{

/*-----------------------------------------------------------------*/

public:

/*------------------------------------------------------------------*/

	enum Note
	{
		Note_A,
		Note_B,
		Note_C,
		Note_D,
		Note_E,
		Note_F,
		Note_G
	};

	enum Sign
	{
		Sign_None,
		Sign_Sharp,
		Sign_Flat
	};

	enum Interval
	{
		Interval_Prime,
		Interval_Minor_Second,
		Interval_Major_Second,
		Interval_Minor_Third,
		Interval_Major_Third,
		Interval_Fourth,
		Interval_Small_Fifth,
		Interval_Fifth,
		Interval_Minor_Sixth,
		Interval_Major_Sixth,
		Interval_Minor_Seventh,
		Interval_Major_Seventh
	};

/*------------------------------------------------------------------*/


	// TODO ...

/*------------------------------------------------------------------*/

};


/*****************************************************************************/

#endif //  _MUSICALNOTE_HPP_
