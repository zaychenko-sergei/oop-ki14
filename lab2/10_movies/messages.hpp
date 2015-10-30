// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MESSAGES_HPP_
#define _MESSAGES_HPP_

/*****************************************************************************/


namespace Messages
{
	const char * const ActorNameEmpty         = "Actor name cannot be empty";
	const char * const ActorBornInFuture      = "Actor's birth year is in future";
	const char * const ActorMovieAlreadyKnown = "Actor already has a specified movie";
	const char * const MovieTitleEmpty        = "Movie title cannot be empty";
	const char * const MovieProducedInFuture  = "Movie production year is in future";
	const char * const RatingOutOfRange       = "Rating should be within [1:10]";
	const char * const MovieGenreAlreadyAdded = "Genre was already added for a movie";
	const char * const MovieActorAlreadyAdded = "Actor was already added to a movie";
	const char * const MovieUnresolved        = "Movie with the specified title was not found";
	const char * const ActorUnresolved        = "Movie actor with specified name was not found";
	const char * const ActorAlreadyRegistered = "Movie actor with identical name was already registered";
	const char * const MovieAlreadyRegistered = "Movie with identical title was already registered";
	const char * const GenreNameEmpty         = "Genre cannot be empty";
	const char * const NegativeAge            = "Age cannot be negative";
}


/*****************************************************************************/

#endif // _MESSAGES_HPP_