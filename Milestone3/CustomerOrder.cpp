// Serach Boes
// Date of completion: November 24th, 2019

#include <iostream>
#include <iomanip>
#include "CustomerOrder.h"
#include "Item.h"
#include "Utilities.h"

using namespace std;

size_t CustomerOrder::m_widthField = 0; //need to define static variables outside of the class in cpp file or else linking error

CustomerOrder::CustomerOrder() {
	m_name = "";
	m_product = "";
	m_cntItem = 0;
	m_lstItem = nullptr;
}

CustomerOrder::CustomerOrder(std::string& str) { //custom constructor

	Utilities util;
	bool flag = false;
	size_t pos = 0;

	try { m_name = util.extractToken(str, pos, flag); }
	catch (const char* Msg) {};

	flag = false;
	pos += (m_name.length() + 1);

	try { m_product = util.extractToken(str, pos, flag); }
	catch (const char* Msg) {};

	flag = false;
	pos += (m_product.length() + 1);

	unsigned int count = 0; //count number of items in the customer order
	for (unsigned int i = 0; i < str.length(); i++)
	{
		if (str[i] == util.getDelimiter())
		{
			count++;
		}
	}
	m_cntItem = count - 1;
	m_lstItem = new ItemInfo * [m_cntItem]; //allocate memory needed for amount of items

	for (size_t i = 0; i < m_cntItem; ++i) {
		try { m_lstItem[i] = new ItemInfo(util.extractToken(str, pos, flag)); } //store items
		catch (const char* Msg) {};
		flag = false;
		pos += (m_lstItem[i]->m_itemName.length() + 1);
	}

	if (CustomerOrder::m_widthField < util.getFieldWidth()) {
		CustomerOrder::m_widthField = util.getFieldWidth();
	}


}

CustomerOrder::CustomerOrder(const CustomerOrder& other) {//copy constructor
	//throw an exception if called
	throw "Copy Operations Not Allowed";
}

CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept {//move constructor
	m_lstItem = nullptr;
	*this = std::move(other);
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) {//move assignment operator


	if (this != &other) {
		delete[] m_lstItem;
		m_name = other.m_name;
		m_product = other.m_product;
		m_cntItem = other.m_cntItem;
		m_lstItem = other.m_lstItem;
		other.m_lstItem = nullptr;
		other.m_name = "";
		other.m_product = "";
		other.m_cntItem = 0;
	}

	return *this;

}

bool CustomerOrder::getItemFillState(std::string str) const { //returns the ItemInfo::m_fillState of the item specified as a parameter. 
	//If the item doesn't exist in the order, return true

	bool flag = true;
	for (unsigned int i = 0; i < m_cntItem; ++i) {
		if (m_lstItem[i]->m_itemName == str)
			flag = m_lstItem[i]->m_fillState;
	}
	return flag;
}

bool CustomerOrder::getOrderFillState() const { //returns true if all the items in the order have been filled; false otherwise

	bool flag = false;
	unsigned int amountFilled = 0;
	for (unsigned int i = 0; i < m_cntItem; ++i) {
		if (m_lstItem[i]->m_fillState == true)
			++amountFilled;
	}
	if (amountFilled == m_cntItem)
		flag = true;

	return flag;
}

void CustomerOrder::fillItem(Item& item, std::ostream& os) {

	for (unsigned int i = 0; i < m_cntItem; ++i) {
		if (m_lstItem[i]->m_itemName == item.getName() && item.getQuantity() > 0) {
			item.updateQuantity();
			m_lstItem[i]->m_serialNumber = item.getSerialNumber();
			m_lstItem[i]->m_fillState = true;
			os << "Filled " << m_name << ", " << m_product << "[" << item.getName() << "]" << endl;
		}

		if (m_lstItem[i]->m_itemName == item.getName() && item.getQuantity() == 0)
			os << "Unable to fill " << m_name << ", " << m_product << "[" << item.getName() << "]" << endl;
	}
}

void CustomerOrder::display(std::ostream& os) const {
	os.setf(std::ios::left);
	os << m_name << " - " << m_product << endl;
	for (size_t i = 0; i < m_cntItem; ++i) {
		os << "[";
		os.setf(std::ios::right);
		os << std::setfill('0') << setw(6) << m_lstItem[i]->m_serialNumber;
		os.unsetf(std::ios::right);
		os << "] ";
		os << std::setfill(' ');
		os << setw(m_widthField + 4) << m_lstItem[i]->m_itemName << " - ";//
		if (m_lstItem[i]->m_fillState == true)
			os << "FILLED" << endl;
		else
			os << "MISSING" << endl;
	}
}

CustomerOrder::~CustomerOrder() {
	for (size_t i = 0; i < m_cntItem; ++i) {
		delete m_lstItem[i];
	}
	delete[] m_lstItem;
};