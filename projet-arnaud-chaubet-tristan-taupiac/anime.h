/**
 * \file anime.h
 */
#ifndef ANIME_H
#define ANIME_H
#include "media.h" // for media_t
/**
 * An anime.
 */
class anime_t: public media_t
{
          public:
                  /**
                   * Constructs a new anime.
                   * Initializes its announcement to "The anime is played!".
                   */
                 anime_t();
};
#endif
