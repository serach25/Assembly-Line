// Name: Serach Boes
// Date of completion: November 16th, 2019

#include <iostream>
#include <string>
#include "Utilities.h"

char Utilities::m_delimiter;

void Utilities::setFieldWidth(size_t width) { //sets the field width of the current object to the value of the parameter

	m_widthField = width;
}

size_t Utilities::getFieldWidth() const { //returns the field width of the current object

	return m_widthField;
}

const std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) { //extracts tokens from the first parameter

	std::string notConst = str;
	notConst = notConst.erase(0, next_pos);
	std::string widthName = notConst;
	notConst = notConst.substr(0, notConst.find(m_delimiter));

	if (notConst.empty())  // NOT successful
	{
		throw "No token between delimiters";
	}

	if (m_widthField < notConst.length() && widthName.length() == str.length()) {
		m_widthField = notConst.length();
	}

	if ((str.length() == notConst.length()))
		more = false;
	else {
		more = true;
	}
	return notConst;
}

const char Utilities::getDelimiter() const { //returns the delimiter character of the current object.
	return m_delimiter;
}
