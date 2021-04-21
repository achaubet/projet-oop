/**
 * \file media.cpp
 */
#include "media.h" // for media_t
#include <iostream> // for cout
#include <cstring> // for strcmp

media_t::media_t(){ // Constructs a new media
  this->announcement = "undefined"; // Initializes its announcement to undefined
  this->name = "undefined"; // Initializes its name to undefined
  this->rating = -1; // Initializes its rating to -1
  this->year = -1; // Initializes its year to -1
}

string media_t::get_announcement() const{ // Gets the announcement for this media
  return this->announcement; // Return the announcement for this media
}

string media_t::get_name() const{ // Gets the name for this media
  return this->name; // Return the name for this media
}

float media_t::get_rating() const{ // Gets the rating for this media
  return this->rating; // Return the rating for this media
}

int media_t::get_year() const{ // Gets the year for this media
  return this->year; // Return the year for this media
}

void media_t::handle_m() const{ // Handles the m command for this media
  cout << *this << endl;
}

void media_t::handle_mn(string name) const{ // Handles the mn command for this media
  const char *strstr_cmp = strstr(this->get_name().c_str(), name.c_str());
  if(strstr_cmp != NULL){ // If strstr_cmp is not NULL, then the name of this media contains NAME
    this->handle_m();
  }
}

void media_t::handle_my(int year) const{ // Handles the my command for this media
  if(this->get_year() == year){ // If year is equal to this media year
    this->handle_m(); // Then calls the handle_m method
  }
}

void media_t::handle_myge(int year) const{ // Handles the myge command for this media
  if(this->get_year() >= year){ // If year is greater or equal than this media year
    this->handle_m(); // Then calls the handle_m method
  }
}

void media_t::handle_mygt(int year) const{ // Handles the mygt command for this media
  if(this->get_year() > year){ // If year is greater than this media
    this->handle_m(); // Then calls the handle_m method
  }
}

void media_t::handle_myle(int year) const{
  if(this->get_year() <= year){
    this->handle_m();
  }
}

void media_t::handle_mylt(int year) const{
  if(this->get_year() < year){
    this->handle_m();
  }
}

quality_t media_t::qualities_at(int index) const{
  return this->qualities.at(index);
}

void media_t::qualities_push_back(quality_t quality){
  this->qualities.push_back(quality);
}

int media_t::qualities_size() const{
  return this->qualities.size();
}

void media_t::set_name(string name){
  this->name = name;
}

void media_t::set_rating(float rating){
  this->rating = rating;
}

void media_t::set_year(int year){
  this->year = year;
}

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
  return os; // Return the output stream
}
