#pragma once
#include <string>
#include <iostream>
using namespace std;

class RingNode
{
private:
	int OldAge = 0;
	string Description;
	string SymbolicData;
public:
	RingNode* next;

public:
	RingNode();
	~RingNode();
	int getAge();
	void setAge(int age);
	string getDescription();
	void setDescription(string description);
	string getData();
	void setData(string data);
	void print();
};

