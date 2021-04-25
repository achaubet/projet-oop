/**
 * \file streaming-service.cpp
 */
#include "streaming-service.h" // for streaming_service_h
#include <iostream> // for cout
/**
 * Constructs a new streaming service.
 * Initializes its name to "undefined" and its web address to "undefined".
 */
streaming_service_t::streaming_service_t(){
  this->name = "undefined";
  this->web = "undefined";
}
/**
 * Gets the name for this streaming service.
 * \return The name for this streaming service.
 */
string streaming_service_t::get_name() const{
  return this->name;
}
/**
 * Gets the web address for this streaming service.
 * \return The web address for this streaming service.
 */
string streaming_service_t::get_web() const{
  return this->web;
}
/**
 * Handles the i command for this streaming service.
 * Calls the << overloaded operator on this streaming service.
 */
void streaming_service_t::handle_i() const{
  cout << *this;
}
/**
 * Handles the m command for this streaming service.
 * Iterates on medias to call the handle_m method on its elements.
 */
void streaming_service_t::handle_m() const{
  int i = 0;
  for(; i < static_cast<int>(this->medias.size()); i++){
    this->medias[i].handle_m();
  }
}
/**
 * Handles the mn command for this streaming service.
 * Iterates on medias to call the handle_mn method on its elements.
 * \param name The mn command parameter.
 */
void streaming_service_t::handle_mn(string name) const{
  int i = 0;
  for(; i < static_cast<int>(this->medias.size()); i++){
    this->medias[i].handle_mn(name);
  }
}
/**
 * Handles the my command for this streaming service.
 * Iterates on medias to call the handle_my method on its elements.
 * \param year The my command parameter.
 */
void streaming_service_t::handle_my(int year) const{
  int i = 0;
  for(; i < static_cast<int>(this->medias.size()); i++){
    this->medias[i].handle_my(year);
  }
}
/**
 * Handles the myge command for this streaming service.
 * Iterates on medias to call the handle_myge method on its elements.
 * \param year The myge command parameter.
 */
void streaming_service_t::handle_myge(int year) const{
  int i = 0;
  for(; i < static_cast<int>(this->medias.size()); i++){
    this->medias[i].handle_myge(year);
  }
}
/**
 * Handles the mygt command for this streaming service.
 * Iterates on medias to call the handle_mygt method on its elements.
 * \param year The mygt command parameter.
 */
void streaming_service_t::handle_mygt(int year) const{
  int i = 0;
  for(; i < static_cast<int>(this->medias.size()); i++){
    this->medias[i].handle_mygt(year);
  }
}
/**
 * Handles the myle command for this streaming service.
 * Iterates on medias to call the handle_myle method on its elements.
 * \param year The myle command parameter.
 */
void streaming_service_t::handle_myle(int year) const{
  int i = 0;
  for(; i < static_cast<int>(this->medias.size()); i++){
    this->medias[i].handle_myle(year);
  }
}
/**
 * Handles the mylt command for this streaming service.
 * Iterates on medias to call the handle_mylt method on its elements.
 * \param year The mylt command parameter.
 */
void streaming_service_t::handle_mylt(int year) const{
  int i = 0;
  for(; i < static_cast<int>(this->medias.size()); i++){
    this->medias[i].handle_mylt(year);
  }
}
/**
 * Handles the n command for this streaming service.
 */
void streaming_service_t::handle_n() const{
  cout << this->get_name() << endl;
}
/**
 * Handles the w command for this streaming service.
 */
void streaming_service_t::handle_w() const{
  cout << this->get_web() << endl;
}
/**
 * Accesses to the element of medias at the specified index for this streaming service.
 * Calls the at method on medias.
 * \param index The index.
 * \return The element of medias at the specified index for this streaming service.
 */
media_t streaming_service_t::medias_at(int index) const{
  return this->medias.at(index);
}
/**
 * Adds an element at the end of medias for this streaming service.
 * Calls the push_back method on medias.
 * \param media The element.
 */
void streaming_service_t::medias_push_back(media_t media){
  this->medias.push_back(media);
}
/**
 * Gets the size of medias for this streaming service.
 * Calls the size method on medias.
 * \return The size of medias for this streaming service.
 */
int streaming_service_t::medias_size() const{
  return this->medias.size();
}
/**
 * Sets the name for this streaming service.
 * \param name The name for this streaming service.
 */
void streaming_service_t::set_name(string name){
  this->name = name;
}
/**
 * Sets the web address for this streaming service.
 * \param web The web address for this streaming service.
 */
void streaming_service_t::set_web(string web){
  this->web = web;
}
/**
 * Inserts a streaming service into an output stream.
 * The inserted string is "(name, web, (medias1, medias2, ...))".
 * Calls the << overloaded operator on the medias.
 * \param os The output stream.
 * \param streaming_service The streaming service.
 * \return The output stream.
 */
ostream &operator<<(ostream &os, const streaming_service_t &streaming_service){
  int i = 0;
  os << "(" << streaming_service.get_name() << ", " << streaming_service.get_web() << ", (";
  for(; i < streaming_service.medias_size(); i++){ // Browses the medias of a streaming service
    i != (streaming_service.medias_size() - 1) ? os << streaming_service.medias_at(i) << ", " : os << streaming_service.medias_at(i) << ")";
  }
  os << ")" << endl;
  return os;
}
