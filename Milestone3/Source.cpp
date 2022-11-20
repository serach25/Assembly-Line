LineManager::LineManager(std::string& fileName, std::vector<Task*>& tasks, std::vector<CustomerOrder>& orders) {
bool more;
size_t pos;
size_t count;
size_t formerNo;
Utilities util;
std::ifstream file(fileName);
std::string record;
if (!file)
{
	std::cout << "*** Unable to open " + fileName + " file" << std::endl;
}
while (!file.eof())
{
	more = true; pos = 0u; count = 0u;
	std::getline(file, record);
	std::string former = util.extractToken(record, pos, more);
	std::string next = "";
	if (more) next = util.extractToken(record, pos, more);
	for (size_t i = 0; i < tasks.size(); i++) {
		if (tasks[i]->getName() == former) {
			formerNo = i;
			break;
		}
	}
	if (next.size() != 0) {
		for (size_t i = 0; i < tasks.size(); i++) {
			if (tasks[i]->getName() == next) {
				tasks[formerNo]->setNextTask(*tasks[i]);
				break;
			}
		}
	}
	else
		tasks[formerNo]->setNextTask(*AssemblyLine[0]);
	AssemblyLine.push_back(tasks[formerNo]);
}
for (size_t i = 0; i < orders.size(); i++) {
	ToBeFilled.push_back(std::move(orders[i]));
}
}