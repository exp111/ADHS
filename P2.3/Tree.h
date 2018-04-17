#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "TreeNode.h"
using namespace std;

class Tree
{
private:
	TreeNode* anker = nullptr;
	int size = 0;
public:
	Tree();
	~Tree();

	void add(TreeNode* node);
	void addRecursive(TreeNode* anker, TreeNode* node);
	void deleteWithChilds(TreeNode * toDelete);
	bool removeRecursive(TreeNode * anker, int posID);
	bool remove(int posID);
	void preOrder(TreeNode * anker);
	void print();
	void searchRecursive(vector<TreeNode*>& List, string Name, TreeNode * anker);
	bool importCSV(string fileName);
	vector<TreeNode*> search(string Name);
};

