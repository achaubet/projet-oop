/**
 * \file str2f-error.cpp
 */
#include "str2f-error.h" // for str2f_error
#include <sstream> // for ostringstream
/**
 * Constructs a new string to float conversion exception.
 * \param str The string that cannot be converted to a float.
 */
str2f_error::str2f_error(string str){
  ostringstream oss;
  oss << "str2f_error: unable to convert the string \"" << str << "\" to a float";
  this->str = oss.str();
}
/**
 * Destroys an existing string to float conversion exception.
 */
str2f_error::~str2f_error() throw (){}
/**
 * Creates a string describing this string to float conversion exception.
 * This string is "str2f_error: unable to convert the string \"str\" to a float".
 * \returns The string describing this string to float conversion exception.
 */
const char *str2f_error::what() const throw(){
  return this->str.c_str();
}
