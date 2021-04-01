#include "streaming-service.h" // for streaming_service_t
#include "media.h" // for media_t
#include "anime.h" // for anime_t
#include "film.h" // for film_t
#include "series.h" // for series_t
#include <iostream> // for cout
#include <pugixml.hpp> // for xml_document, xml_node, xml_attributes, xml_parse_result
using namespace std;
using namespace pugi;

int main(int argc, char const *argv[]) {
  streaming_service_t netflix;
  anime_t anime;
  anime.qualities_push_back(medium);
  anime.qualities_push_back(high);
  netflix.set_name("Netflix");
  netflix.set_web("https://www.netflix.com/");
  netflix.medias_push_back(anime);
  netflix.medias_push_back(anime);
  netflix.handle_i();
  return 0;
}
