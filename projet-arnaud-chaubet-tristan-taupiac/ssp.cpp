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
#include <cstdio> //  for fgets
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
      media_type.set_rating(strtof(media_info.child_value(),endptr));  // Try ... Catch ICI (Si echec, retouner -1)
    }
    if(strcmp(media_info.name(), "year") == 0){
      media_type.set_year(strtol(media_info.child_value(), endptr, 10)); // try ... catch ICI
    }
  }

  try{
    service.medias_push_back(media_type);
  }
  catch(bad_alloc &e){
    cerr << "An exception occurred, cannot add media to streaming-service, reason: " << e.what() << endl;
    return -1;
  }
  return 0;
}

int xml_browse(xml_document &doc, streaming_service_t &service){
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
                  cerr << "An exception occurred, cannot allocate a new anime, reason: " << e.what() << endl;
                  return -1;
                }
                if(xml_browse_media(media, service, *media_type_ptr) != 0){
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
                  cerr << "An exception occurred, cannot allocate a new film, reason: " << e.what() << endl;
                  return -1;
                }
                if(xml_browse_media(media, service, *media_type_ptr) != 0){
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
                  cerr << "An exception occurred, cannot allocate a new series, reason: " << e.what() << endl;
                  return -1;
                }
                if(xml_browse_media(media, service, *media_type_ptr) != 0){
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

void read_stdin(char *input){ //Fonction permettant la saisie et la verification de la saisie
  int i = 0;
  bool is_here = false;
  fgets(input, 30, stdin); //On rentre une commande
  if(input[0]=='\n'){ // On verifie si celle-ci n'est pas vide
    cout << "./ssp.out: invalid command" << endl;
    input[0] = '\0';
  }
  else{ // Sinon on verifie que la commande n'excède pas 30 caractères
    for(; i <= static_cast<int>(strlen(input)); i++){
      if(input[i]=='\n'){ // Si il trouve le caractère de contrôle '\n' alors la commande n'excède pas les 30 caractères
        is_here = true; // Et on passe le booléen à vrai
      }
    }
    if(!is_here){ // Si c'est faux alors il n'as pas trouvé de caractère de contrôle '\n', le flux n'est donc pas vide
      while(getchar()!='\n'); // Il faut alors le vider avec la fonction getchar() jusqu'a atteindre le caractère de contrôle
    }
  }
}

void clear_char_array(char *array){
  int size = strlen(array);
  while(size > 0){
    array[size] = '\0';
    size--;
  }
}


void enter_commands(streaming_service_t streaming_service){
  int i = 0;
  int j = 0;
  int cmd_at = 0;
  char **endPtr = NULL;
  char input[30] = {'\0', '\0'};
  char command[10] = {'\0'};
  char command_param[30] = {'\0'};
  const char* command_array[6] =  {"mn", "my", "myge", "mygt", "myle", "mylt"};
  bool quit = false;
  while(!quit){
    cout << "SSP> ";
    read_stdin(input);
    if(strlen(input)==2){
      switch(input[0]){
        case 'i':streaming_service.handle_i();break;
        case 'm':streaming_service.handle_m();break;
        case 'n':streaming_service.handle_n();break;
        case 'w':streaming_service.handle_w();break;
        case 'v':cout << "SSP (Streaming Service Program) 20210408\n\n" << "Copyright (C) 2021 Tristan Taupiac and Arnaud Chaubet.\n\n" << "Written by Tristan Taupiac <tristan.taupiac@etud.univ-pau.fr> and Arnaud Chaubet <a.chaubet@etud.univ-pau.fr>." <<endl;break;
        case 'h':handle_h();break;
        case 'q':quit=true;break;
        default:cout<<"./ssp.out: invalid command"<<endl;break;
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
        cout << "cmd at: " << cmd_at << endl;
        switch(cmd_at){
          case 0:streaming_service.handle_mn(command_param);break;
          case 1:streaming_service.handle_my(strtol(command_param, endPtr, 10));break;
          case 2:streaming_service.handle_myge(strtol(command_param, endPtr, 10));break;
          case 3:streaming_service.handle_mygt(strtol(command_param, endPtr, 10));break;
          case 4:streaming_service.handle_myle(strtol(command_param, endPtr, 10));break;
          case 5:streaming_service.handle_mylt(strtol(command_param, endPtr, 10));break;
          default:cout<<"./ssp.out: invalid command"<<endl;break;
        }
      }
      else{cout << "./ssp.out: invalid command" << endl;}
    }
  }
}



int main(int argc, char const *argv[]) {
  // Déclaration et initialisation des variables
  xml_document doc;
  xml_parse_result result;
  streaming_service_t streaming_service;

  // Début du programme et traitement des erreurs

  if(argc != 2){ // On vérifie le nombres de paramètres passés en arguments
    cerr << argv[0] << ": invalid number of arguments" << endl;
    return 1;
  }

  result = doc.load_file(argv[1]); // Récuperation du document passé en paramètres

  if(!result){ // Si il y a une erreur avec le document ou si celui-ci n'existe pas
    cerr << argv[0] << ": unable to parse the document" << endl;
    return 1;
  }

  if(xml_browse(doc, streaming_service) != 0){ // Si il y a une erreur durant le parcours du document XML
    return 1;
  }

  enter_commands(streaming_service);

  return 0;
}
