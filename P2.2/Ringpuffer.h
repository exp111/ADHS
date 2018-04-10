#pragma once
#include <string>
#include <iostream>
#include "RingNode.h"
using namespace std;

class Ringpuffer
{
private:
	RingNode* Anker;
	int size = 0;
public:
	Ringpuffer();
	~Ringpuffer();
	//???
	//???
	//???
	RingNode* getLast();
	void addNode(RingNode* Node);
	RingNode* search(string Data);
	void print();
};