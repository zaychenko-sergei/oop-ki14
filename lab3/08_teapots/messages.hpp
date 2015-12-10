// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MESSAGES_HPP_
#define _MESSAGES_HPP_

/*****************************************************************************/

namespace Messages
{

/*-----------------------------------------------------------------*/

	const char * const NonPositiveVolume = "Teapot volume must be positive";
	const char * const NonPositiveSpeed  = "Teapot heating speed must be positive";
	const char * const WrongTeapotIndex  = "Teapot index is wrong";

	const char * const TeapotVolumeOverflow  = "Too much water is added to teapot";
	const char * const TeapotVolumeUnderflow = "Too much water is taken from teapot";

	const char * const TeapotAlmostBurned    = "Teapot is almost burned";

	const char * const TeapotIsNotModifiable = "Teapot is not modifiable at the moment";

/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

#endif // _MESSAGES_HPP_
