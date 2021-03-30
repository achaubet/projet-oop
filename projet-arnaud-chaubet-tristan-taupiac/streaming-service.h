/**
 * \file streaming-service.h
 */
#ifndef STREAMING_SERVICE_H
#define STREAMING_SERVICE_H
#include <string> // for string
#include <vector> // for vector
#include "media.h" // for media_t
using namespace std; //for string
/**
 * A streaming service.
 */
class streaming_service_t
{
        vector<media_t> medias; /**< The medias (offered by this streaming service).*/
        string name; /**< The name (example: "Netflix").*/
        string web; /**< The web address (example: "https://www.netflix.com/").*/
        public:
                /**
                 * Constructs a new streaming service.
                 * Initializes its name to "undefined" and its web address to "undefined".
                 */
                 streaming_service_t();
                 /**
                  * Gets the name for this streaming service.
                  * \return The name for this streaming service.
                  */
                 string get_name() const;
                 /**
                  * Gets the web address for this streaming service.
                  * \return The web address for this streaming service.
                  */
                 string get_web() const;
                 /**
                  * Handles the i command for this streaming service.
                  * Calls the << overloaded operator on this streaming service.
                  */
                 void handle_i() const;
                 /**
                  * Handles the m command for this streaming service.
                  * Iterates on medias to call the handle_m method on its elements.
                  */
                 void handle_m() const;
                 /**
                  * Handles the mn command for this streaming service.
                  * Iterates on medias to call the handle_mn method on its elements.
                  * \param name The mn command parameter.
                  */
                 void handle_mn(string name) const;
                 /**
                  * Handles the my command for this streaming service.
                  * Iterates on medias to call the handle_my method on its elements.
                  * \param year The my command parameter.
                  */
                 void handle_my(int year) const;
                 /**
                  * Handles the myge command for this streaming service.
                  * Iterates on medias to call the handle_myge method on its elements.
                  * \param year The myge command parameter.
                  */
                 void handle_myge(int year) const;
                 /**
                  * Handles the mygt command for this streaming service.
                  * Iterates on medias to call the handle_mygt method on its elements.
                  * \param year The mygt command parameter.
                  */
                 void handle_mygt(int year) const;
                 /**
                  * Handles the myle command for this streaming service.
                  * Iterates on medias to call the handle_myle method on its elements.
                  * \param year The myle command parameter.
                  */
                 void handle_myle(int year) const;
                 /**
                  * Handles the mylt command for this streaming service.
                  * Iterates on medias to call the handle_mylt method on its elements.
                  * \param year The mylt command parameter.
                  */
                 void handle_mylt(int year) const;
                 /**
                  * Handles the n command for this streaming service.
                  */
                 void handle_n() const;
                 /**
                  * Handles the w command for this streaming service.
                  */
                 void handle_w() const;
                 /**
                  * Accesses to the element of medias at the specified index for this streaming service.
                  * Calls the at method on medias.
                  * \param index The index.
                  * \return The element of medias at the specified index for this streaming service.
                  */
                 media_t medias_at(int index) const;
                 /**
                  * Adds an element at the end of medias for this streaming service.
                  * Calls the push_back method on medias.
                  * \param media The element.
                  */
                 void medias_push_back(media_t media);
                 /**
                  * Gets the size of medias for this streaming service.
                  * Calls the size method on medias.
                  * \return The size of medias for this streaming service.
                  */
                 int medias_size() const;
                 /**
                  * Sets the name for this streaming service.
                  * \param name The name for this streaming service.
                  */
                 void set_name(string name);
                 /**
                  * Sets the web address for this streaming service.
                  * \param web The web address for this streaming service.
                  */
                 void set_web(string web);
};
/**
 * Inserts a streaming service into an output stream.
 * The inserted string is "(name, web, (medias1, medias2, ...))".
 * Calls the << overloaded operator on the medias.
 * \param os The output stream.
 * \param streaming_service The streaming service.
 * \return The output stream.
 */
ostream &operator<<(ostream &os, const streaming_service_t &streaming_service);
#endif

