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
  cout << this;
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
