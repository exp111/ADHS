#include "TreeNode.h"
using namespace std;


TreeNode::TreeNode()
{
}


TreeNode::~TreeNode()
{
}

string TreeNode::getName()
{
	return Name;
}

int TreeNode::getAlter()
{
	return Alter;
}

double TreeNode::getEinkommen()
{
	return Einkommen;
}

int TreeNode::getPLZ()
{
	return PLZ;
}

void TreeNode::setName(string name)
{
	this->Name = name;
}

void TreeNode::setAlter(int alter)
{
	this->Alter = alter;
}

void TreeNode::setEinkommen(double einkommen)
{
	this->Einkommen = einkommen;
}

void TreeNode::setPLZ(int plz)
{
	this->PLZ = plz;
}

void TreeNode::printData()
{
	cout << "NodeID: " << to_string(this->NodeID)
		<< ", Name: " << this->Name
		<< ", Alter: " << to_string(this->Alter)
		<< ", Einkommen: " << to_string(this->Einkommen)
		<< ", PLZ: " << to_string(this->PLZ)
		<< ", PosID: " << to_string(this->NodePosID) << endl;
}
