#pragma once
#include <iostream>
#include <string>

class TreeNode
{
private:
	int NodePosID;
	int NodeID;
	string Name;
	int Alter;
	double Einkommen;
	int PLZ;
	//TODO: make public or tree buddy
	TreeNode* links = nullptr;
	TreeNode* rechts = nullptr;
public:
	TreeNode();
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
};

