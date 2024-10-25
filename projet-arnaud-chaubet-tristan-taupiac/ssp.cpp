/**
 * \file ssp.cpp
 */
#include "streaming-service.h" // for streaming_service_t
#include "media.h" // for media_t
#include "anime.h" // for anime_t
#include "film.h" // for film_t
#include "series.h" // for series_t
#include "str2f-error.h" // for str2f_error
#include "str2i-error.h" // for str2i_error
#include "str2l-error.h" // for str2l_error
#include <iostream> // for cout
#include <pugixml.hpp> // for xml_document, xml_node, xml_attributes and xml_parse_result
#include <cstring> // for strcmp
#include <cstdlib> // for strtof, strtod, strlen
#include <cstdio> // for fgets and getchar
#include <climits>
#include <cerrno>
using namespace std; // for cout
using namespace pugi; // for xml_node, xml_attribute and xml_parse_result
/**
 * Browses an XML file containing data about a media of a streaming service.
 * \param media A media XML node.
 * \param service A streaming service.
 * \param media_type A media.
 * \param argv The name of this program.
 * \return -1 on error, else 0.
 */
int xml_browse_media(xml_node &media, streaming_service_t &service, media_t &media_type, const char *argv){
  xml_node media_info;
  xml_node quality;
  xml_attribute media_name;
  float rating = 0.0;
  long l_year = 0;
  int year = 0;
  char *endptr = NULL;

  for(media_name = media.first_attribute(); media_name; media_name = media_name.next_attribute()){ // Browses the attributes for a media
    if(strcmp(media_name.name(), "name") == 0){ // If the node name is "name"
      media_type.set_name(media_name.value()); // Sets the media name to media_name.value()
    }
  }
  for(media_info = media.first_child(); media_info; media_info = media_info.next_sibling()){ // Browses the informations for a media
    if(strcmp(media_info.name(), "qualities") == 0){ // If the node name is "qualities"
      for(quality = media_info.first_child(); quality; quality = quality.next_sibling()){ // Browses the qualites of a media
        if(strcmp(quality.child_value(), "low") == 0){ // If the quality is low
          media_type.qualities_push_back(low); // Add "low" quality for this media
        }
        if(strcmp(quality.child_value(), "medium") == 0){ // If the quality is medium
          media_type.qualities_push_back(medium); // Add "medium" quality for this media
        }
        if(strcmp(quality.child_value(), "high") == 0){ // If the quality is high
          media_type.qualities_push_back(high); // Add "high" quality for this media
        }
      }
    }
    if(strcmp(media_info.name(), "rating") == 0){ // If the node name is "rating"
      try{
        rating = strtof(media_info.child_value(), &endptr);
        if(errno == ERANGE){throw str2f_error(media_info.child_value());} // If the rating is out of range, throw a str2f error
        if(endptr==media_info.child_value()){throw str2f_error(media_info.child_value());} // If the rating contains invalid values, throw a str2f error
      }
      catch(str2f_error &e){ // Catch a str2f_error exception
        cerr << argv << ": an exception occurred (" << e.what() << ")" << endl;
        return -1;
      }
      media_type.set_rating(rating); // Sets the media rating to rating
    }
    if(strcmp(media_info.name(), "year") == 0){ // If the node name is "year"
      try{
        l_year = strtol(media_info.child_value(), &endptr, 10);
        if(endptr==media_info.child_value()){throw str2l_error(media_info.child_value());} // If year contains invalid values, throw a str2l error
        if(((l_year>=LONG_MAX) or (l_year<=LONG_MIN)) and (errno == ERANGE)){throw str2l_error(media_info.child_value());} // If year is out of range, throw a str2l error
      }
      catch(str2l_error &e){ // Catch a str2l_error exception
        cerr << argv << ": an exception occurred (" << e.what() << ")" << endl;
        return -1;
      }
      try{
        if((l_year>INT_MAX) or (l_year<INT_MIN)){throw str2i_error(media_info.child_value());}  // If year is outside the integer range, throw a str2i error
        year = static_cast<int>(l_year);
      }
      catch(str2i_error &e){ // Catch a str2i_error exception
        cerr << argv << ": an exception occurred (" << e.what() << ")" << endl;
        return -1;
      }
      media_type.set_year(year); // Sets the media year to year
    }
  }
  try{
    service.medias_push_back(media_type); // Add a media to a streaming service
  }
  catch(bad_alloc &e){ // Catch a bad alloc exception
    cerr << argv << ": an exception occurred (cannot add media to streaming-service, reason: " << e.what() << ")" << endl;
    return -1;
  }
  return 0;
}
/**
 * Browses an XML file containing data about a streaming service and the media it broadcasts.
 * \param doc The XML Document.
 * \param service A streaming service.
 * \param argv The name of this program.
 * \return -1 on error, else 0.
 */
int xml_browse(xml_document &doc, streaming_service_t &service, const char *argv){
  xml_node node;
  xml_node child_node;
  xml_node media;
  xml_attribute service_info;
  xml_attribute media_type_attr;
  media_t *media_type_ptr = NULL;

  node = doc.first_child(); // Sets node to the first child of the XML document
  for(; node; node = node.next_sibling()){ // Browses the nodes of the XML document
    if(strcmp(node.name(), "streaming-service") == 0){ // If the node name is "streaming-service"
      for(service_info = node.first_attribute(); service_info; service_info = service_info.next_attribute()){ // Browses the attributes for a streaming service
        if(strcmp(service_info.name(), "name") == 0){ // If the attribute name is "name"
          service.set_name(service_info.value()); // Sets the streaming service name
        }
      }
      for(child_node = node.first_child(); child_node; child_node = child_node.next_sibling()){ // Browses the child nodes of a streaming service
        if(strcmp(child_node.name(), "medias") == 0){ // If the node name is "medias"
          for(media = child_node.first_child(); media; media = media.next_sibling()){ // Browses the child nodes of medias
            for(media_type_attr = media.first_attribute(); media_type_attr; media_type_attr = media_type_attr.next_attribute()){ // Browses the attributes of a media node
              if(strcmp(media_type_attr.value(), "anime") == 0){ // If the media is an anime
                try{
                  media_type_ptr = new anime_t; // Try to create an anime
                }
                catch(bad_alloc &e){ // Catch a bad alloc exception
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
                  media_type_ptr = new film_t; // Try to create a film
                }
                catch(bad_alloc &e){ // Catch a bad alloc exception
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
                  media_type_ptr = new series_t; // Try to create a series
                }
                catch(bad_alloc &e){ // Catch a bad alloc exception
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
        if(strcmp(child_node.name(), "web") == 0){ // If the node name is "Web"
          service.set_web(child_node.child_value()); // Sets the streaming service website
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
 * \param input The input.
 * \param argv The name of this program.
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
 * \param array An array of characters.
 */
void clear_char_array(char *array){
  int size = strlen(array); // Sets size to the size of the array
  while(size >= 0){
    array[size] = '\0'; // Sets value to '\0'
    size--;
  }
}
/**
 * Processes the input command.
 * \param streaming_service A streaming service.
 * \param argv The name of this program.
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
    read_stdin(input, argv); // Retrieves the command entered by the user
    if(strlen(input)==2){ // If the command contains only one character
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
    else{ // Else, the command contains more than one character
      if((strlen(input)>2)){
        i = 0;
        cmd_at = -1;
        if(strlen(command)!=0){clear_char_array(command);} // If the array is not empty, then it must be emptied
        if(strlen(command_param)!=0){clear_char_array(command_param);} // If the array is not empty, then it must be emptied
        while(input[i] != '\n' and input[i] != ' '){  // Retrieves the first part of the command
          command[i] = input[i];
          i++;
        }
        for(j = 0; j < 6; j++){ // Then, we check if the first part of the command is correct
          if(strcmp(command, command_array[j])==0){cmd_at=j;}
        }
        if(cmd_at != -1){ // If the command is correct
          l = 0;
          k = strlen(command) + 1;
          if((static_cast<int>(strlen(input)) > k) and (strlen(input) < 25)){ // Retrieves the second part of the command
            while((input[k] != '\n')){
              command_param[l] = input[k];
              k++;
              l++;
            }
          }
          if((command_param[0] == '\0') or (command_param[0] == '\n')){ // Then, we check if the second part of the command is correct
            cerr << argv << ": Missing parameter for the " << command << " command" << endl;
          }
          else{
            if(strlen(input) > 18){ // If the command is greater than 18 characters
              cerr << argv << ": too many characters for the command" << endl;
            }
            else{
              if(((strtol(command_param, NULL, 10) == 0) or ((strtol(command_param, NULL, 10)) > INT_MAX) or (strtol(command_param, NULL, 10) < INT_MIN))and (strcmp(command, "mn") != 0)){ // If the parameter of the command exceeds the value range or if the parameter is incorrect
                cerr << argv << ": invalid parameter for the " << command <<  " command" << endl;
              }
              else{
                if((strtol(command_param, NULL, 10) != 0) and (strcmp(command, "mn") == 0)){ // If the parameter of the mn command is a number
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
        }
        else{cerr << argv << ": invalid command" << endl;}
      }
    }
  }
}
/**
 * The main function.
 * \param argc The numbers of arguments.
 * \param argv The array containing the arguments.
 * \return 1 on error, else 0.
 */
int main(int argc, char const *argv[]) {
  // Declaration and initialization
  xml_document doc;
  xml_parse_result result;
  streaming_service_t streaming_service;

  //Error handling
  if(argc != 2){ // Check if the numbers of arguments are correct
    cerr << argv[0] << ": invalid number of arguments" << endl;
    return 1;
  }

  // Read the document passed in parameters
  result = doc.load_file(argv[1]);

  // If there is an error or if the document doesn't exist
  if(!result){
    cerr << argv[0] << ": unable to parse the document" << endl;
    return 1;
  }

  // Browses the XML document, if there is an error, the program ends and returns 1
  if(xml_browse(doc, streaming_service, argv[0]) != 0){
    return 1;
  }

  // Allows to enter commands
  enter_commands(streaming_service, argv[0]);

  return 0;
}
