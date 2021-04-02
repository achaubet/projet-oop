#include "streaming-service.h" // for streaming_service_t
#include "media.h" // for media_t
#include "anime.h" // for anime_t
#include "film.h" // for film_t
#include "series.h" // for series_t
#include "str2f-error.h" // for str2f-error
#include "str2i-error.h" // for str2i-error
#include "str2l-error.h" // for str2l-error
#include <iostream> // for cout
#include <pugixml.hpp> // for xml_document, xml_node, xml_attributes, xml_parse_result
#include <cstring> // for strcmp
#include <cstdlib> // for strtof
using namespace std;
using namespace pugi;

int xml_browse_media(xml_node &media, streaming_service_t &service, media_t &media_type){
  xml_node media_info;
  xml_node quality;
  xml_attribute media_name;
  char **endptr = NULL;
  for(media_name = media.first_attribute(); media_name; media_name = media_name.next_attribute()){
    if(strcmp(media_name.name(), "name") == 0){
      media_type.set_name(media_name.value());
    }
  }
  for(media_info = media.first_child(); media_info; media_info = media_info.next_sibling()){
    if(strcmp(media_info.name(), "qualities") == 0){
      for(quality = media_info.first_child(); quality; quality = quality.next_sibling()){
        if(strcmp(quality.child_value(), "low") == 0){
          media_type.qualities_push_back(low);
        }
        if(strcmp(quality.child_value(), "medium") == 0){
          media_type.qualities_push_back(medium);
        }
        if(strcmp(quality.child_value(), "high") == 0){
          media_type.qualities_push_back(high);
        }
      }
    }
    if(strcmp(media_info.name(), "rating") == 0){
      media_type.set_rating(strtof(media_info.child_value(),endptr));  // Try ... Catch ICI (Si echec, retouner 1)
    }
    if(strcmp(media_info.name(), "year") == 0){
      media_type.set_year(strtol(media_info.child_value(), endptr, 10)); // try ... catch ICI
    }
  }
  try{
    service.medias_push_back(media_type);
  }
  catch(bad_alloc &e){
    cerr << "An exception occured, cannot add media to streaming-service, reason: " << e.what() << endl;
    return 1;
  }
  return 0;
}

int xml_browse(xml_document &doc, streaming_service_t &service){
  int err = 0;
  xml_node node;
  xml_node child_node;
  xml_node media;
  xml_attribute service_info;
  xml_attribute media_type_attr;
  media_t *media_type_ptr = NULL;

  node = doc.first_child();
  for(; node; node = node.next_sibling()){
    if(strcmp(node.name(), "streaming-service") == 0){
      for(service_info = node.first_attribute(); service_info; service_info = service_info.next_attribute()){
        if(strcmp(service_info.name(), "name") == 0){
          service.set_name(service_info.value());
        }
      }
      for(child_node = node.first_child(); child_node; child_node = child_node.next_sibling()){
        if(strcmp(child_node.name(), "medias") == 0){
          for(media = child_node.first_child(); media; media = media.next_sibling()){
            for(media_type_attr = media.first_attribute(); media_type_attr; media_type_attr = media_type_attr.next_attribute()){ // Parcours de tous les medias
              if(strcmp(media_type_attr.value(), "anime") == 0){
                media_type_ptr = new anime_t;
                 err = xml_browse_media(media, service, *media_type_ptr);
                delete media_type_ptr;
              }
              if(strcmp(media_type_attr.value(), "film") == 0){
                media_type_ptr = new film_t;
                err = xml_browse_media(media, service, *media_type_ptr);
                delete media_type_ptr;
              }
              if(strcmp(media_type_attr.value(), "series") == 0){
                media_type_ptr = new series_t;
                err = xml_browse_media(media, service, *media_type_ptr);
                delete media_type_ptr;
              }
            }
          }
        }
        if(strcmp(child_node.name(), "web") == 0){
          service.set_web(child_node.child_value());
        }
      }
    }
  }
  return err;
}

int main(int argc, char const *argv[]) {

  xml_document doc;
  xml_parse_result result;
  streaming_service_t streaming_service;

  if(argc != 2){
    cerr << "./ssp.out: invalid number of arguments" << endl;
    return 1;
  }

  result = doc.load_file(argv[1]);

  if(!result){
    cerr << "./ssp.out: unable to parse the document" << endl;
    return 1;
  }

  if(xml_browse(doc, streaming_service) != 0){
    return 1;
  }

  streaming_service.handle_m();
  return 0;
}
