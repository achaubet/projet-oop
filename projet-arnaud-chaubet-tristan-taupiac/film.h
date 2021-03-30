/**
 * \file film.h
 */
#ifndef FILM_H
#define FILM_H
#include "media.h" // for media_t
/**
 * A film.
 */
class film_t: public media_t
{
        public:
                /**
                 * Constructs a new film.
                 * Initializes its announcement to "The film is played!".
                 */
                film_t();
};
#endif
