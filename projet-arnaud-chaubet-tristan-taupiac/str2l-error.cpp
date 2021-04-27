/**
 * \file str2l-error.cpp
 */
#include "str2l-error.h" // for str2l-error.h
#include <sstream> // for ostringstream
/**
 * Constructs a new string to long conversion exception.
 * \param str The string that cannot be converted to a long.
 */
str2l_error::str2l_error(string str){
  ostringstream oss;
  oss << "str2l_error: unable to convert the string \"" << str << "\" to a long";
  this->str = oss.str();
}
/**
 * Destroys an existing string to long conversion exception.
 */
str2l_error::~str2l_error() throw() {}
/**
 * Creates a string describing this string to long conversion exception.
 * This string is "str2l_error: unable to convert the string \"str\" to a long".
 * \returns The string describing this string to long conversion exception.
 */
const char *str2l_error::what() const throw(){
  return str.c_str();
}
