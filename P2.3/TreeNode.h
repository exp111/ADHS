#pragma once
#include <iostream>
#include <string>
using namespace std;

class TreeNode
{
	friend class Tree;
private:
	int NodePosID;
	int NodeID;
	string Name;
	int Alter;
	double Einkommen;
	int PLZ;
	TreeNode* links = nullptr;
	TreeNode* rechts = nullptr;
public:
	TreeNode();
	TreeNode(string Name, int Alter, double Einkommen, int PLZ);
	~TreeNode();

	string getName();
	int getAlter();
	double getEinkommen();
	int getPLZ();
	void setName(string name);
	void setAlter(int alter);
	void setEinkommen(double einkommen);
	void setPLZ(int plz);
	void printData();

	void setID(int ID);
};

