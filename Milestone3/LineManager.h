// Name: Serach Boes
// Date of completion: December 1st, 2019

#pragma once
#ifndef LINEMANAGER_H
#define LINEMANAGER_H

#include <vector>
#include <deque>
#include <string>
#include "Task.h"

class LineManager {
	std::vector<Task*> AssemblyLine; //A vector containing all the references of the task objects on the assembly line
	std::deque<CustomerOrder> ToBeFilled; //a deque of customer orders to be filled
	std::deque<CustomerOrder> Completed; //a deque of customer orders that are completed
	unsigned int m_cntCustomerOrder; //number of CustomerOrder objects the assembly line started with 

public:
	LineManager(const std::string& str, std::vector<Task*>& tasks, std::vector<CustomerOrder>& toBeFilled );  
	bool run(std::ostream& os); //performs 1 cycle of operations on the assembly line
	void displayCompleted(std::ostream& os) const;  //displays all orders that were completed
	void validateTasks() const; //validates each task on the assembly line
};

#endif

