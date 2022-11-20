// Name: Serach Boes
// Date of completion: December 1st, 2019

#pragma once
#ifndef TASK_H
#define TASK_H

#include <deque>
#include "Item.h"
#include "CustomerOrder.h"

class Task : public Item {
	
	std::deque<CustomerOrder> m_orders; //new orders coming in one side and exiting out the other once filled
	Task* m_pNextTask; //a pointer to the next Task on the assembly line

public:
	
	Task(const std::string& str); //custom constructor
	Task(const Task& other) = delete;//copy constructor
	Task& operator=(const Task& other) = delete;//copy assignment operator
	Task(Task&& other) noexcept = delete;//move constructor
	Task& operator=(Task&& other) = delete;//move assignment operator
	void runProcess(std::ostream& os); //runs a single cycle of the assembly line for the current task
	bool moveTask(); 
	void setNextTask(Task& task); 
	bool getCompleted(CustomerOrder& order); 
	void validate(std::ostream& os); 
	Task& operator+=(CustomerOrder&& order); 
};

#endif

