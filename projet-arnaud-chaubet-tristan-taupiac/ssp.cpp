/**
 * \file ssp.cpp
 */
#include "streaming-service.h" // for streaming_service_t
#include "media.h" // for media_t
#include "anime.h" // for anime_t
#include "film.h" // for film_t
#include "series.h" // for series_t
#include "str2f-error.h" // for str2f-error
#include "str2i-error.h" // for str2i-error
#include "str2l-error.h" // for str2l-error
#include <iostream> // for cout
#include <pugixml.hpp> // for xml_document, xml_node, xml_attributes and xml_parse_result
#include <cstring> // for strcmp
#include <cstdlib> // for strtof
#include <cstdio> // for fgets
using namespace std; // for cout
using namespace pugi; // for xml_node, xml_attribute and xml_parse_result
/**
 * Browses an XML file containing data about a media of a streaming service.
 */
int xml_browse_media(xml_node &media, streaming_service_t &service, media_t &media_type, const char *argv){
  xml_node media_info;
  xml_node quality;
  xml_attribute media_name;
  float rating = 0.0;
  char *endptr = NULL;

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
      try{
        rating = strtof(media_info.child_value(), &endptr);
        if(endptr==media_info.child_value()){throw str2f_error(media_info.child_value());}
      }
      catch(str2f_error &e){
        cerr << argv << ": an exception occurred (" << e.what() << ")" << endl;
        return -1;
      }
      media_type.set_rating(rating);
    }
    if(strcmp(media_info.name(), "year") == 0){
      media_type.set_year(strtol(media_info.child_value(), &endptr, 10)); // try ... catch ICI
    }
  }
  try{
    service.medias_push_back(media_type);
  }
  catch(bad_alloc &e){
    cerr << argv << ": an exception occurred (cannot add media to streaming-service, reason: " << e.what() << ")" << endl;
    return -1;
  }
  return 0;
}
/**
 * Browses an XML file containing data about a streaming service and the media it broadcasts.
 */
int xml_browse(xml_document &doc, streaming_service_t &service, const char *argv){
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
                try{
                  media_type_ptr = new anime_t;
                }
                catch(bad_alloc &e){
                  cerr << argv << ": an exception occurred (cannot allocate a new anime, reason: " << e.what() << ")" << endl;
                  return -1;
                }
                if(xml_browse_media(media, service, *media_type_ptr, argv) != 0){
                  delete media_type_ptr;
                  return -1;
                }
                delete media_type_ptr;
              }
              if(strcmp(media_type_attr.value(), "film") == 0){
                try{
                  media_type_ptr = new film_t;
                }
                catch(bad_alloc &e){
                  cerr << argv << ": an exception occurred (cannot allocate a new film, reason: " << e.what() << ")" << endl;
                  return -1;
                }
                if(xml_browse_media(media, service, *media_type_ptr, argv) != 0){
                  delete media_type_ptr;
                  return -1;
                }
                delete media_type_ptr;
              }
              if(strcmp(media_type_attr.value(), "series") == 0){
                try{
                  media_type_ptr = new series_t;
                }
                catch(bad_alloc &e){
                  cerr << argv <<": an exception occurred (cannot allocate a new series, reason: " << e.what() << ")" << endl;
                  return -1;
                }
                if(xml_browse_media(media, service, *media_type_ptr, argv) != 0){
                  delete media_type_ptr;
                  return -1;
                }
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
  return 0;
}
/**
 * Handles the h command.
 */
void handle_h(){
  cout << "h: prints this help" << endl;
  cout << "i: prints information about the streaming service" << endl;
  cout << "m: prints the streaming service medias" << endl;
  cout << "mn NAME: prints the streaming service medias with the name containing NAME" << endl;
  cout << "my YEAR: prints the streaming service medias with the year equal to YEAR" << endl;
  cout << "myge YEAR: prints the streaming service with the year greater than or equal to YEAR" << endl;
  cout << "mygt YEAR: prints the streaming service with the year greater than YEAR" << endl;
  cout << "myle YEAR: prints the streaming service with the year less than or equal to YEAR" << endl;
  cout << "mylt YEAR: prints the streaming service with the year less than YEAR" << endl;
  cout << "n: prints the streaming service name" << endl;
  cout << "q: quits SSP" << endl;
  cout << "v: prints the SSP version" << endl;
  cout << "w: prints the streaming service web address" << endl;
}
/**
 * Function allowing the entry of a command and the verification of the entry
 */
void read_stdin(char *input, const char *argv){
  int i = 0;
  bool is_here = false;

  fgets(input, 30, stdin); // Allows the read of the stdin stream
  if(input[0]=='\n'){ // Check if the command is not empty
    cerr << argv << ": invalid command" << endl;
    input[0] = '\0';
  }
  else{ // Else, we check that the command is not greater than 30 characters
    for(; i <= static_cast<int>(strlen(input)); i++){
      if(input[i]=='\n'){ // If it finds the control character '\n' then the command doesn't exceed 30 character
        is_here = true; // And we set the boolean to true
      }
    }
    if(!is_here){ // If it's false then it did not find the control character '\n', so the stdin stream is not empty
      while(getchar()!='\n'); // It must be cleared with the getchar() function until reaching the control character
    }
  }
}
/**
 * Clear an array of characters.
 */
void clear_char_array(char *array){
  int size = strlen(array); // Sets size to the size of the array
  while(size >= 0){
    array[size] = '\0'; // Sets value to '\0'.
    size--;
  }
}
/**
 * Processes the input command.
 */
void enter_commands(streaming_service_t streaming_service, const char *argv){
  int i = 0, j = 0, k = 0, l = 0;
  int cmd_at = 0;
  char **endPtr = NULL;
  char input[30] = {'\0', '\0'};
  char command[10] = {'\0'};
  char command_param[30] = {'\0'};
  const char* command_array[6] =  {"mn", "my", "myge", "mygt", "myle", "mylt"};
  bool quit = false;

  while(!quit){
    cout << "SSP> ";
    read_stdin(input, argv); // Retrieves the command entered by the user.
    if(strlen(input)==2){
      switch(input[0]){
        case 'i':streaming_service.handle_i();break;
        case 'm':streaming_service.handle_m();break;
        case 'n':streaming_service.handle_n();break;
        case 'w':streaming_service.handle_w();break;
        case 'v':cout << "SSP (Streaming Service Program) 20210420\n\n" << "Copyright (C) 2021 Tristan Taupiac and Arnaud Chaubet.\n\n" << "Written by Tristan Taupiac <tristan.taupiac@etud.univ-pau.fr> and Arnaud Chaubet <a.chaubet@etud.univ-pau.fr>." <<endl;break;
        case 'h':handle_h();break;
        case 'q':quit=true;break;
        default:cerr << argv << ": invalid command" << endl;break;
      }
    }
    else{
      if((strlen(input)>2)){
        i = 0;
        cmd_at = -1;
        if(strlen(command)!=0){clear_char_array(command);}
        if(strlen(command_param)!=0){clear_char_array(command_param);}
        while(input[i] != '\n' and input[i] != ' '){
          command[i] = input[i];
          i++;
        }
        for(j = 0; j < 6; j++){
          if(strcmp(command, command_array[j])==0){cmd_at=j;}
        }
        if(cmd_at != -1){
          l = 0;
          k = strlen(command) + 1;
          if((static_cast<int>(strlen(input)) > k) and (strlen(input) < 25)){
            while((input[k] != '\n')){
              command_param[l] = input[k];
              k++;
              l++;
            }
          }
          if((command_param[0] == '\0') or (command_param[0] == '\n')){
            cerr << argv << ": Missing parameter for the " << command << " command" << endl;
          }
          else{
            if(strlen(command_param) >= 18){
              cerr << argv << ": too many characters for the command" << endl;
            }
            if((strtol(command_param, NULL, 10) == 0) and (strcmp(command, "mn") != 0)){
              cerr << argv << ": invalid parameter for the " << command <<  " command" << endl;
            }
            else{
              if((strtol(command_param, NULL, 10) != 0) and (strcmp(command, "mn") == 0)){
                cerr << argv << ": invalid parameter for the " << command <<  " command" << endl;
              }
              else{
                switch(cmd_at){
                  case 0:streaming_service.handle_mn(command_param);break;
                  case 1:streaming_service.handle_my(strtol(command_param, endPtr, 10));break;
                  case 2:streaming_service.handle_myge(strtol(command_param, endPtr, 10));break;
                  case 3:streaming_service.handle_mygt(strtol(command_param, endPtr, 10));break;
                  case 4:streaming_service.handle_myle(strtol(command_param, endPtr, 10));break;
                  case 5:streaming_service.handle_mylt(strtol(command_param, endPtr, 10));break;
                }
              }
            }
          }
        }
        else{cerr << argv << ": invalid command" << endl;}
      }
      else{cerr << argv << ": invalid command" << endl;}
    }
  }
}


int main(int argc, char const *argv[]) {
  /**
   * Declaration and initialization.
   */
  xml_document doc;
  xml_parse_result result;
  streaming_service_t streaming_service;
  /**
   * Error handling.
   */
  if(argc != 2){ // Check if the numbers of arguments are correct.
    cerr << argv[0] << ": invalid number of arguments" << endl;
    return 1;
  }
  /**
   * Read the document passed in parameters.
   */
  result = doc.load_file(argv[1]);
  /**
   * If there is an error or if the document doesn't exist.
   */
  if(!result){
    cerr << argv[0] << ": unable to parse the document" << endl;
    return 1;
  }
  /**
   * Browses the XML document, if there is an error, the program ends and returns 1.
   */
  if(xml_browse(doc, streaming_service, argv[0]) != 0){
    return 1;
  }
  /**
   * Allows to enter commands.
   */
  enter_commands(streaming_service, argv[0]);

  return 0;
}
