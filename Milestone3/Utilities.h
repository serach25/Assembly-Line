// Name: Serach Boes
// Date of completion: November 16th, 2019

#pragma once
#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

class Utilities {

	size_t m_widthField = 1; //length of token extracted
	static char m_delimiter; //seperates the tokens from a given std::string ,static because all utilities objects share the same delimiter

public:

	void setFieldWidth(size_t width);  //sets the field width of the current object to the value of the parameter
	size_t getFieldWidth() const; //returns the field width of the current object
	const std::string extractToken(const std::string& str, size_t& next_pos, bool& more); //extracts tokens from the first parameter
	static void setDelimiter(const char delimiter) { m_delimiter = delimiter; }//sets the delimiter for this class to the character received
	const char getDelimiter() const; //returns the delimiter character of the current object.
};

#endif 

