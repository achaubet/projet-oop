/**
 * \file media.cpp
 */
#include "media.h" // for media_t
#include <iostream> // for cout
#include <cstring> // for strcmp
/**
 * Constructs a new media.
 * Initializes its announcement to "undefined", its name to "undefined", its rating to "-1" and its year to "-1".
 */
media_t::media_t(){
  this->announcement = "undefined"; // Initializes its announcement to undefined
  this->name = "undefined"; // Initializes its name to undefined
  this->rating = -1; // Initializes its rating to -1
  this->year = -1; // Initializes its year to -1
}
/**
 * Gets the announcement for this media.
 * \return The announcement for this media.
 */
string media_t::get_announcement() const{
  return this->announcement;
}
/**
 * Gets the name for this media.
 * \return The name for this media.
 */
string media_t::get_name() const{
  return this->name;
}
/**
 * Gets the rating for this media.
 * \return The rating for this media.
 */
float media_t::get_rating() const{
  return this->rating;
}
/**
 * Gets the year for this media.
 * \return The year for this media.
 */
int media_t::get_year() const{
  return this->year;
}
/**
 * Handles the m command for this media.
 * Calls the << overloaded operator on this media.
 */
void media_t::handle_m() const{
  cout << *this << endl;
}
/**
 * Handles the mn command for this media.
 * Calls the handle_m method on this media if the condition is satisfied.
 * \param name The mn command parameter.
 */
void media_t::handle_mn(string name) const{
  const char *strstr_cmp = strstr(this->get_name().c_str(), name.c_str());
  if(strstr_cmp != NULL){ // If strstr_cmp is not NULL, then the name of this media contains NAME
    this->handle_m();
  }
}
/**
 * Handles the my command for this media.
 * Calls the handle_m method on this media if the condition is satisfied.
 * \param year The my command parameter.
 */
void media_t::handle_my(int year) const{
  if(this->get_year() == year){ // If year is equal to this media year
    this->handle_m(); // Then calls the handle_m method
  }
}
/**
 * Handles the myge command for this media.
 * Calls the handle_m method on this media if the condition is satisfied.
 * \param year The myge command parameter.
 */
void media_t::handle_myge(int year) const{
  if(this->get_year() >= year){ // If this media year is greater than or equal to YEAR
    this->handle_m(); // Then calls the handle_m method
  }
}
/**
 * Handles the mygt command for this media.
 * Calls the handle_m method on this media if the condition is satisfied.
 * \param year The mygt command parameter.
 */
void media_t::handle_mygt(int year) const{
  if(this->get_year() > year){ // If this media year is greater than YEAR
    this->handle_m(); // Then calls the handle_m method
  }
}
/**
 * Handles the myle command for this media.
 * Calls the handle_m method on this media if the condition is satisfied.
 * \param year The myle command parameter.
 */
void media_t::handle_myle(int year) const{
  if(this->get_year() <= year){
    this->handle_m();
  }
}
/**
 * Handles the mylt command for this media.
 * Calls the handle_m method on this media if the condition is satisfied.
 * \param year The mylt command parameter.
 */
void media_t::handle_mylt(int year) const{
  if(this->get_year() < year){
    this->handle_m();
  }
}
/**
 * Accesses to the element of qualities at the specified index for this media.
 * Calls the at method on qualities.
 * \param index The index.
 * \return The element of qualities at the specified index for this media.
 */
quality_t media_t::qualities_at(int index) const{
  return this->qualities.at(index);
}
/**
 * Adds an element at the end of qualities for this media.
 * Calls the push_back method on qualities.
 * \param quality The element.
 */
void media_t::qualities_push_back(quality_t quality){
  this->qualities.push_back(quality);
}
/**
 * Gets the size of qualities for this media.
 * Calls the size method on qualities.
 * \return The size of qualities for this media.
 */
int media_t::qualities_size() const{
  return this->qualities.size();
}
/**
 * Sets the name for this media.
 * \param name The name for this media.
 */
void media_t::set_name(string name){
  this->name = name;
}
/**
 * Sets the rating for this media.
 * \param rating The name for this media.
 */
void media_t::set_rating(float rating){
  this->rating = rating;
}
/**
 * Sets the year for this media.
 * \param year The name for this media.
 */
void media_t::set_year(int year){
  this->year = year;
}
/**
 * Inserts a media into an output stream.
 * The inserted string is "(name, year, announcement, rating, (qualities1, qualities2, ...))".
 * \param os The output stream.
 * \param media The media.
 * \return The output stream.
 */
ostream &operator<<(ostream &os, const media_t &media){
  int i = 0;
  os << "("<< media.get_name() << ", " << media.get_year() << ", " << media.get_announcement() << ", " << media.get_rating() << ", ("; // Inserts the name, the year, the announcement and the rating of this media
  for(i = media.qualities_at(0); i < (media.qualities_size()+media.qualities_at(0)); i++){ // Browses the qualities of this media
    switch(i){ // And add them to the output stream
      case low:os << "low";break;
      case medium:os << "medium";break;
      case high:os << "high";break;
    }
    i != (((media.qualities_at(0)+media.qualities_size())-1)) ? os << ", " : os << ")";
  }
  os << ")";
  return os;
}
