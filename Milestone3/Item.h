// Name: Serach Boes
// Date of completion: November 16th, 2019

#pragma once
#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {

	std::string m_name;
	std::string m_description;
	int	m_serialNumber;
	unsigned int m_quantity;
	static size_t m_widthField;

public:
	Item(const std::string& str); //custom constructor
	const std::string& getName() const { return m_name; };
	const unsigned int getSerialNumber() { return m_serialNumber++; };
	const unsigned int getQuantity() { return m_quantity; };
	void updateQuantity();
	void display(std::ostream& os, bool full) const;

};

#endif
