#pragma once
#include <iostream>
#include "TreeNode.h"
using namespace std;

class Tree
{
private:
	TreeNode* anker = nullptr;
public:
	Tree();
	~Tree();

	void add(TreeNode* node);
	void remove(int posID);
	void print();
	TreeNode* search(string Name);
};

