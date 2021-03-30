/**
 * \file media.h
 */
#ifndef MEDIA_H
#define MEDIA_H
#include <string> // for string
#include <vector> // for vector
using namespace std; // for string
/**
  * A quality.
  */
enum quality_t
{
      low,
      medium,
      high
};
/**
 * A media.
 */
class media_t
{
        private:
                string name; /**< The media name (example: "Steins;Gate").*/
                vector<quality_t> qualities; /**< The media qualities (example: "low" and "medium"). */
                float rating; /**< The media rating (example: "6.6").*/
                int year; /**< The media year (example: "2011").*/
        protected:
                string announcement;/**< The announcement to print when the media is played (example: "The anime is played!").*/
        public:
                /**
                 * Constructs a new media.
                 * Initializes its announcement to "undefined", its name to "undefined", its rating to "-1" and its year to "-1".
                 */
                media_t();
                /**
                 * Gets the announcement for this media.
                 * \return The announcement for this media.
                 */
                string get_announcement() const;
                /**
                 * Gets the name for this media.
                 * \return The name for this media.
                 */
                string get_name() const;
                /**
                 * Gets the rating for this media.
                 * \return The rating for this media.
                 */
                float get_rating() const;
                /**
                 * Gets the year for this media.
                 * \return The year for this media.
                 */
                int get_year() const;
                /**
                 * Handles the m command for this media.
                 * Calls the << overloaded operator on this media.
                 */
                void handle_m() const;
                /**
                 * Handles the mn command for this media.
                 * Calls the handle_m method on this media if the condition is satisfied.
                 * \param name The mn command parameter.
                 */
                void handle_mn(string name) const;
                /**
                 * Handles the my command for this media.
                 * Calls the handle_m method on this media if the condition is satisfied.
                 * \param year The my command parameter.
                 */
                void handle_my(int year) const;
                /**
                 * Handles the myge command for this media.
                 * Calls the handle_m method on this media if the condition is satisfied.
                 * \param year The myge command parameter.
                 */
                void handle_myge(int year) const;
                /**
                 * Handles the mygt command for this media.
                 * Calls the handle_m method on this media if the condition is satisfied.
                 * \param year The mygt command parameter.
                 */
                void handle_mygt(int year) const;
                /**
                 * Handles the myle command for this media.
                 * Calls the handle_m method on this media if the condition is satisfied.
                 * \param year The myle command parameter.
                 */
                void handle_myle(int year) const;
                /**
                 * Handles the mylt command for this media.
                 * Calls the handle_m method on this media if the condition is satisfied.
                 * \param year The mylt command parameter.
                 */
                void handle_mylt(int year) const;
                /**
                 * Accesses to the element of qualities at the specified index for this media.
                 * Calls the at method on qualities.
                 * \param index The index.
                 * \return The element of qualities at the specified index for this media.
                 */
                quality_t qualities_at(int index) const;
                /**
                 * Adds an element at the end of qualities for this media.
                 * Calls the push_back method on qualities.
                 * \param quality The element.
                 */
                void qualities_push_back(quality_t quality);
                /**
                 * Gets the size of qualities for this media.
                 * Calls the size method on qualities.
                 * \return The size of qualities for this media.
                 */
                int qualities_size() const;
                /**
                 * Sets the name for this media.
                 * \param name The name for this media.
                 */
                void set_name(string name);
                /**
                 * Sets the rating for this media.
                 * \param rating The name for this media.
                 */
                void set_rating(float rating);
                /**
                 * Sets the year for this media.
                 * \param year The name for this media.
                 */
                void set_year(int year);
};
/**
 * Inserts a media into an output stream.
 * The inserted string is "(name, year, announcement, rating, (qualities1, qualities2, ...))".
 * \param os The output stream.
 * \param media The media.
 * \return The output stream.
 */
ostream &operator<<(ostream &os, const media_t &media);
#endif
