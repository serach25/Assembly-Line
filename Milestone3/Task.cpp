// Name: Serach Boes
// Date of completion: December 1st, 2019

#include <iostream>
#include <string>
#include "Task.h"

using namespace std;

Task::Task(const std::string& str) : Item(str) {
	m_pNextTask = nullptr; //set to safe state
}

void Task::runProcess(std::ostream& os) {  //runs a single cycle of the assembly line for the current task
	if (!m_orders.empty())       //if there are orders in the queue
		if (!m_orders.back().getOrderFillState())      //verify fill status of the last order - if not filled
			if (!m_orders.back().getItemFillState(getName()))   //If the item exists in the order, returns false
				m_orders.back().fillItem(*this, os);      //fill the last order
}


bool Task::moveTask() { //moves the last order in the queue to the next task on the assembly line 
	//if the orders fill state for the current item is true.
	
	bool flag = true;
	if (m_orders.empty()) { //if the queue is empty, return false
		flag = false;
	}

	if (!m_orders.empty()) {
		if (m_orders.back().getItemFillState(getName()) && m_pNextTask != nullptr) {
			*m_pNextTask += move(m_orders.back());
			m_orders.pop_back();
		}
	}
	
	return flag;
}


void Task::setNextTask(Task& task) { //stores the provided Task object's reference into the m_pNextTask pointer.
	m_pNextTask = &task;
}

bool Task::getCompleted(CustomerOrder& order) {
	bool flag = false;
	
	if(!m_orders.empty() && m_orders.back().getOrderFillState()) { //if m_orders is not empty and the last order is filled
		order = move(m_orders.back());
		m_orders.pop_back();
		flag = true;
	}
	return flag;
}

void Task::validate(std::ostream& os) { //writes the name of the Item this Task is responsable for into the parameter
	
	os << getName() << " --> " << (m_pNextTask==nullptr?"END OF LINE":m_pNextTask->getName() )<< endl;
}

Task& Task::operator+=(CustomerOrder&& order){ //r-value reference
	m_orders.push_front(std::move(order)); //moves parameter onto the front of the m_orders queue
	return *this;
}



