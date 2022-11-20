// Date of completion: November 24th, 2019

#pragma once
#ifndef CUSTOMERORDER_H
#define CUSTOMERORDER_H

#include <string>
#include "Item.h"

struct ItemInfo
{
	std::string m_itemName;
	unsigned int m_serialNumber = 0;
	bool m_fillState = false;

	ItemInfo(std::string src) : m_itemName(src) {};
};

class CustomerOrder {

	std::string m_name; //name of customer
	std::string m_product;  //name of product being assembled
	unsigned int m_cntItem;  //a count of the number of items for the customer order
	ItemInfo** m_lstItem; //dynamically allocated array of pointers. Each element of the array is a dynamically allocated object of type ItemInfo
	//the resource that the class must manage
	static size_t m_widthField; //maximum width of a field, for display
public:
	CustomerOrder(); //default constructor
	CustomerOrder(std::string& str); //custom constructor
	CustomerOrder(const CustomerOrder& other);//copy constructor
	CustomerOrder& operator=(const CustomerOrder& other) = delete;//copy assignment operator
	CustomerOrder(CustomerOrder&& other) noexcept;//move constructor
	CustomerOrder& operator=(CustomerOrder&& other);//move assignment operator
	~CustomerOrder(); //destructor
	bool getItemFillState(std::string str) const;
	bool getOrderFillState() const;
	void fillItem(Item& item, std::ostream& os);
	void display(std::ostream& os) const;
};

#endif 
