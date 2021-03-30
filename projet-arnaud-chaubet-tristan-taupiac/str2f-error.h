/**
 * \file str2f-error.h
 */
#ifndef STR2F_ERROR_H
#define STR2F_ERROR_H
#include <exception> // for exception
#include <string> // for string
using namespace std; //for string
/**
 * A string to float conversion exception.
 */
class str2f_error: public exception
{
        string str; /**< The string describing this string to float conversion exception.*/
        public:
                /**
                 * Constructs a new string to float conversion exception.
                 * \param str The string that cannot be converted to a float.
                 */
                str2f_error(string str);
                /**
                 * Destroys an existing string to float conversion exception.
                 */
                ~str2f_error() throw ();
                /**
                 * Creates a string describing this string to float conversion exception.
                 * This string is "str2f_error: unable to convert the string \"str\" to a float".
                 * \returns The string describing this string to float conversion exception.
                 */
                const char *what() const throw();
};
#endif

