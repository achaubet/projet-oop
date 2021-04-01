#include "streaming-service.h" // for streaming_service_h
#include <iostream> // for cout

streaming_service_t::streaming_service_t(){
  this->name = "undefined";
  this->web = "undefined";
}

string streaming_service_t::get_name() const{
  return this->name;
}

string streaming_service_t::get_web() const{
  return this->web;
}

void streaming_service_t::handle_i() const{
  cout << *this;
}

void streaming_service_t::handle_m() const{
  int i = 0;
  for(; i < static_cast<int>(this->medias.size()); i++){
    this->medias[i].handle_m();
  }
}

void streaming_service_t::handle_mn(string name) const{
  int i = 0;
  for(; i < static_cast<int>(this->medias.size()); i++){
    this->medias[i].handle_mn(name);
  }
}

void streaming_service_t::handle_my(int year) const{
  int i = 0;
  for(; i < static_cast<int>(this->medias.size()); i++){
    this->medias[i].handle_my(year);
  }
}

void streaming_service_t::handle_myge(int year) const{
  int i = 0;
  for(; i < static_cast<int>(this->medias.size()); i++){
    this->medias[i].handle_myge(year);
  }
}

void streaming_service_t::handle_mygt(int year) const{
  int i = 0;
  for(; i < static_cast<int>(this->medias.size()); i++){
    this->medias[i].handle_mygt(year);
  }
}

void streaming_service_t::handle_myle(int year) const{
  int i = 0;
  for(; i < static_cast<int>(this->medias.size()); i++){
    this->medias[i].handle_myle(year);
  }
}

void streaming_service_t::handle_mylt(int year) const{
  int i = 0;
  for(; i < static_cast<int>(this->medias.size()); i++){
    this->medias[i].handle_mylt(year);
  }
}

void streaming_service_t::handle_n() const{
  cout << this->get_name() << endl;
}

void streaming_service_t::handle_w() const{
  cout << this->get_web() << endl;
}

media_t streaming_service_t::medias_at(int index) const{
  return this->medias.at(index);
}

void streaming_service_t::medias_push_back(media_t media){
  this->medias.push_back(media);
}

int streaming_service_t::medias_size() const{
  return this->medias.size();
}

void streaming_service_t::set_name(string name){
  this->name = name;
}

void streaming_service_t::set_web(string web){
  this->web = web;
}

ostream &operator<<(ostream &os, const streaming_service_t &streaming_service){
  int i = 0;
  os << "(" << streaming_service.get_name() << ", " << streaming_service.get_web() << ", (";
  for(; i < streaming_service.medias_size(); i++){
    i != (streaming_service.medias_size() - 1) ? os << streaming_service.medias_at(i) << ", " : os << streaming_service.medias_at(i) << ")";
  }
  os << ")" << endl;
  return os;
}
