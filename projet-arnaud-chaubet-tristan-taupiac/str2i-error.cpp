/**
 * \file str2i-error.cpp
 */
#include "str2i-error.h" // for str2i-error.h
#include <sstream> // for ostringstream
#include <exception> // for exception
#include <string> // for string
using namespace std;
/**
 * Constructs a new string to int conversion exception.
 * \param str The string that cannot be converted to a int.
 */
str2i_error::str2i_error(string str){
  ostringstream oss;
  oss << "str2i_error: unable to convert the string \"" << str << "\" to a int";
  this->str = oss.str();
}
/**
 * Destroys an existing string to int conversion exception.
 */
str2i_error::~str2i_error() throw() {}
/**
 * Creates a string describing this string to int conversion exception.
 * This string is "str2i_error: unable to convert the string \"str\" to a int".
 * \returns The string describing this string to int conversion exception.
 */
const char *str2i_error::what() const throw(){
  return str.c_str();
}
