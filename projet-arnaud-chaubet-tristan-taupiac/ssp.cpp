#include "streaming-service.h" // for streaming_service_t
#include "media.h" // for media_t
#include "anime.h" // for anime_t
#include "film.h" // for film_t
#include "series.h" // for series_t
#include <iostream> // for cout
#include <pugixml.hpp> // for xml_document, xml_node, xml_attributes, xml_parse_result
#include <cstring> // for strcmp
using namespace std;
using namespace pugi;

int xml_browse(xml_document &doc, streaming_service_t &service){
  xml_node node;
  xml_attribute service_info;
  node = doc.first_child();
  for(; node; node = node.next_sibling()){
    if(strcmp(node.name(), "streaming-service")==0){
      for(service_info = node.first_attribute(); service_info; service_info = service_info.next_attribute()){
        if(strcmp(service_info.name(), "name")==0){
          service.set_name(service_info.value());
        }
      }
      
    }
  }
  return 0;
}

int main(int argc, char const *argv[]) {
  xml_document doc;
  xml_parse_result result;

  streaming_service_t streaming_service;
  anime_t anime;

  if(argc != 2){
    cerr << "./ssp.out: invalid number of arguments" << endl;
    return 1;
  }

  result = doc.load_file(argv[1]);



  if(!result){
    cerr << "./ssp.out: unable to parse the document" << endl;
    return 1;
  }

  xml_browse(doc, streaming_service); // Ne pas oublier de verifier la valeur de retour de cette fonction pour traiter les exceptions ...

  streaming_service.handle_n();
  return 0;
}
