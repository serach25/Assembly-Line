// Name: Serach Boes
// Date of completion: December 1st, 2019

#include <iostream>
#include <fstream>
#include <deque>
#include "LineManager.h"
#include "Utilities.h"
#include "CustomerOrder.h"


using namespace std;

LineManager::LineManager(const std::string& str, std::vector<Task*>& tasks, std::vector<CustomerOrder>& Filled) {
	//custom constructor(filename to be used for linking the assembly line objects, 
	//a reference to a vector of type Task* that contains the addresses of all the Task objects created for the assembly line,
	//a reference to a vector of type CustomerOrder that contains all the CustomerOrder objects to be filled)

	Utilities util;
	util.setDelimiter('|');
	string temp;
	bool flag = true;
	
	std::deque<std::string> formLine; //store the order of the tasks to form the Assembly line
	formLine.push_front("");
	fstream file;
	file.open(str);

	if (!file)
		throw "Cannot Open File";

	//read records from the file and set up all the m_pNextTask references in the Task objects

	while (file.eof() == 0) // returns not zero when there is no more data to be read from the file
	{
		size_t pos = 0;
		getline(file, temp);  
		std::string str2 = ""; 
		std::string str1 = util.extractToken(temp, pos, flag);
		pos = str1.length() + 1;

		if (flag == true) {
			str2 = util.extractToken(temp, pos, flag);
		}

		if (str1 != formLine.back()) {
			formLine.push_back(str1);
		}

		if (str2 != "") {
			formLine.push_back(str2);
		}

	}

	formLine.pop_front();
	size_t previous = 0;

	for (size_t i = 0; i < tasks.size(); ++i) { //find starting point
		if (formLine[0] == tasks[i]->getName()) {
			previous = i;
			formLine.pop_front();
		}
	}
	
	for (size_t i = 0; i < formLine.size(); ++i) {  
		for (size_t j = 0; j < tasks.size(); ++j) {  //link together from starting point
			if (formLine[i] == tasks[j]->getName()) {
				tasks[previous]->setNextTask(*tasks[j]);  // Linking each Task object together to form the assembly line
				previous = j;
			}
		}
	}
	
	for (size_t i = 0; i < tasks.size(); ++i){
		AssemblyLine.push_back(tasks[i]);  //copy all the Task objects into the AssemblyLine container
	}

	for (size_t i = 0; i < Filled.size(); i++) { //Move all customer order objects onto the front of the ToBeFilled queue
		ToBeFilled.push_front(std::move(Filled[i]));
	}
	file.close();
}

bool LineManager::run(std::ostream& os) { //performs 1 cycle of operations on the assembly line
	
	bool flag = false;

	if (!ToBeFilled.empty()) { //if there are any customer order objects in the to be filled queue 
		*AssemblyLine[4] += std::move(ToBeFilled.back()); //move the last order onto the starting point of the assembly line
		ToBeFilled.pop_back();
	}
		for (size_t i = 0; i < AssemblyLine.size(); i++) {
			AssemblyLine[i]->runProcess(os); //loop through all tasks on the assembly line and run one cycle of the task's process
		}

		for (size_t j = 0; j < AssemblyLine.size(); j++) {
			AssemblyLine[j]->moveTask();  //loop through all tasks on the assembly line and move the order down the line
		}
	
		CustomerOrder filled_order;
		if (AssemblyLine[3]->getCompleted(filled_order)) {
			//cout << "Test" << endl;
				Completed.push_back(std::move(filled_order)); //completed orders should be put into the completed queue
		}
		
		if (Completed.size() == 4) { //return true if all the orders have been filled, otherwise return false
			flag = true;
			};

	return flag;
}

void LineManager::displayCompleted(std::ostream& os) const {  //displays all orders that were completed
	for (size_t i = 0; i < Completed.size(); ++i) {
		Completed[i].display(os);
	}
}

void LineManager::validateTasks() const { //validates each task on the assembly line
	for (size_t i = 0; i < AssemblyLine.size(); ++i) {
		AssemblyLine[i]->validate(cout);
	}
}