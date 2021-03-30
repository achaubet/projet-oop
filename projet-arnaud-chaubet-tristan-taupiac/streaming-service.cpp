#include "streaming-service.h" // for streaming_service_h
#include <iostream>

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
