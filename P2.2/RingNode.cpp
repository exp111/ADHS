#include "RingNode.h"

RingNode::RingNode()
{
	OldAge = 0;
}


RingNode::~RingNode()
{
}

int RingNode::getAge()
{
	return OldAge;
}

void RingNode::setAge(int age)
{
	OldAge = age;
}

string RingNode::getDescription()
{
	return Description;
}

void RingNode::setDescription(string description)
{
	Description = description;
}

string RingNode::getData()
{
	return SymbolicData;
}

void RingNode::setData(string data)
{
	SymbolicData = data;
}

void RingNode::print()
{
	cout << "OldAge: " << std::to_string(getAge()) << ", Descr: " << getDescription() << ", Data: " << getData();
}