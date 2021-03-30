/**
 * \file series.h
 */
#ifndef SERIES_H
#define SERIES_H
#include "media.h" // for media_t
/**
 * A series.
 */
class series_t: public media_t
{
        public:
                /**
                 * Constructs a new series.
                 * Initializes its announcement to "The series is played!".
                 */
                series_t();
};
#endif

