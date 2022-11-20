// Name: Serach Boes
// Date of completion: November 16th, 2019

#include <iostream>
#include <iomanip>
#include <string>
#include "Item.h"
#include "Utilities.h"

size_t Item::m_widthField = 0; //need to define static variables outside of the class in cpp file or else linking error

Item::Item(const std::string& str) { //custom constructor

	Utilities util;
	bool flag = false;
	size_t pos = 0;

	try { m_name = util.extractToken(str, pos, flag); }
	catch (const char* Msg) {};

	flag = false;
	pos += (m_name.length() + 1);
	std::string stringNum;

	try { stringNum = util.extractToken(str, pos, flag); }
	catch (const char* Msg) {};

	flag = false;
	pos += (stringNum.length() + 1);
	m_serialNumber = std::stoi(stringNum);
	std::string stringQuantity;

	try { stringQuantity = util.extractToken(str, pos, flag); }
	catch (const char* Msg) {};

	flag = false;
	pos += (stringQuantity.length() + 1);
	m_quantity = std::stoi(stringQuantity);

	try { m_description = util.extractToken(str, pos, flag); }
	catch (const char* Msg) {};

	if (Item::m_widthField < util.getFieldWidth()) {
		Item::m_widthField = util.getFieldWidth();
	}
}

void Item::updateQuantity() {
	if (m_quantity > 0)
		m_quantity--;
}

void Item::display(std::ostream& os, bool full) const {

	os.setf(std::ios::left);
	os << std::setw(m_widthField) << m_name << " [";
	os.unsetf(std::ios::left);
	os.setf(std::ios::right);
	os << std::setfill('0') << std::setw(6) << m_serialNumber << "]";
	os.unsetf(std::ios::right);
	os << std::setfill(' ');

	if (full == true) {
		os.setf(std::ios::left);
		os << " Quantity: " << std::setw(m_widthField) << m_quantity << " Description: " << m_description;
	}

	os.unsetf(std::ios::left);
	os << std::endl;
}