#include "Tree.h"
Tree::Tree()
{
}

Tree::~Tree()
{
	deleteWithChilds(anker);
}

void Tree::add(TreeNode * node, bool increaseSize)
{
	if (increaseSize)
	{
		node->NodeID = size;
		size++;
	}
	node->links = nullptr;
	node->rechts = nullptr;
	if (anker == nullptr)
	{
		anker = node;
		return;
	}

	addRecursive(anker, node);
}

void Tree::addRecursive(TreeNode* anker, TreeNode* node)
{
	if (node->NodePosID > anker->NodePosID)
	{
		if (anker->rechts != nullptr)
			addRecursive(anker->rechts, node);
		else
			anker->rechts = node;
	}
	else if (node->NodePosID == anker->NodePosID)
	{
		size--;
		delete node;
		return;
	}
	else
	{
		if (anker->links != nullptr)
			addRecursive(anker->links, node);
		else
			anker->links = node;
	}
}

void Tree::deleteWithChilds(TreeNode* toDelete)
{
	if (toDelete->rechts != nullptr)
		deleteWithChilds(toDelete->rechts);
	if (toDelete->links != nullptr)
		deleteWithChilds(toDelete->links);
	delete toDelete;
}

void Tree::getChilds(vector<TreeNode*> &list, TreeNode* anker)
{
	if (anker == nullptr)
		return;

	list.push_back(anker);

	getChilds(list, anker->links);
	getChilds(list, anker->rechts);
}

vector<TreeNode*> Tree::getChilds(TreeNode* anker)
{
	vector<TreeNode*> list;

	if (anker == nullptr)
		return list;

	getChilds(list, anker->links);
	getChilds(list, anker->rechts);

	return list;
}

bool Tree::removeRecursive(TreeNode* anker, int posID)
{
	if (anker == nullptr)
		return false;

	/*if (posID > anker->NodePosID)
	{
		return removeRecursive(anker->rechts, posID);
	}
	else if (anker->NodePosID == posID)
	{
		//delete 
		//TODO: should we delete the childs?
		deleteWithChilds(anker);
		return true;
	}
	else //if (posID < anker->NodePosID)
	{
		return removeRecursive(anker->rechts, posID);
	}*/
	
	if (posID > anker->NodePosID)
	{
		if (anker->rechts != nullptr && anker->rechts->NodePosID == posID)
		{
			vector<TreeNode*> childs = getChilds(anker->rechts);
			delete anker->rechts;
			anker->rechts = nullptr;
			for (unsigned i = 0; i < childs.size(); i++)
			{
				this->add(childs[i], false);
			}
			return true;
		}
		return removeRecursive(anker->rechts, posID);
	}
	else if (posID == anker->NodePosID) //This should only happen if we want to delete the anker
	{
		//TODO: FIXME removeRecursive()
		//return false;
		vector<TreeNode*> childs = getChilds(anker);
		TreeNode* newAnker = anker->rechts != nullptr ? anker->rechts : anker->links;
		delete anker;
		this->anker = nullptr;
		if (newAnker != nullptr)
		{
			newAnker->links = nullptr;
			newAnker->rechts = nullptr;
		}
		for (unsigned i = 0; i < childs.size(); i++)
		{
			this->add(childs[i], false);
		}
		return true;
	}
	else //if (posID < anker->NodePosID)
	{
		if (anker->links != nullptr && anker->links->NodePosID == posID)
		{
			vector<TreeNode*> childs = getChilds(anker->links);
			delete anker->links;
			anker->links = nullptr;
			for (unsigned i = 0; i < childs.size(); i++)
			{
				this->add(childs[i], false);
			}
			return true;
		}
		return removeRecursive(anker->links, posID);
	}
}

bool Tree::remove(int posID)
{
	//1.) Check for anker->rechts->PosID == posID || anker->links->PosID == posID
	//2.) if no continue if yes save all childs in a vector<TreeNode*>
	//3.) delete anker->rechts || anker->links
	//4.) anker->rechts = nullptr || anker->links = nullptr
	//5.) go through vector and tree->add(childs[i]) them
	//TODO: crashes cause we don't change the pointer to the deleted
	if (removeRecursive(anker, posID))
	{
		//size--;
		return true;
	}
	else
		return false;
}

void Tree::preOrder(TreeNode* anker)
{
	//1. Check if null
	if (anker == nullptr)
		return;

	//2. Output its data
	cout << setw(3) << left << anker->NodeID << "|" 
		<< setw(12) << right << anker->Name << "|" 
		<< setw(7) << right << anker->Alter << "|" 
		<< setw(11) << right << anker->Einkommen << "|"
		<< setw(7) << right << anker->PLZ << "|" 
		<< setw(7) << left << anker->NodePosID 
	<< endl;

	//3. Pre-Order the left node
	preOrder(anker->links);
	//4. Pre-Order the right node
	preOrder(anker->rechts);
}

void Tree::print()
{
	cout << "ID | Name       | Alter | Einkommen | PLZ   | Pos" << endl
		 << "---+------------+-------+-----------+-------+-------" << endl;
	preOrder(anker);
}

void Tree::searchRecursive(vector<TreeNode*> &List, string Name, TreeNode* anker)
{
	if (anker == nullptr)
		return;

	//TODO: This or Pre-Order?
	if (anker->rechts != nullptr)
		searchRecursive(List, Name, anker->rechts);
	
	if (anker->Name == Name)
		List.push_back(anker);
	
	if (anker->links != nullptr)
		searchRecursive(List, Name, anker->links);
}

string getCSVNext(string &line)
{
	string tmp = "";
	while (line.size() > 0 && line.at(0) != ';')
	{
		tmp += line[0];
		line.erase(0,1);
	}
	if (line.size() > 0)
		line.erase(0, 1);

	return tmp;
}

bool Tree::importCSV(string fileName)
{
	fstream file(fileName, fstream::in);

	if (file.bad())
		return false;

	string line;
	while (getline(file, line))
	{
		string name = getCSVNext(line);
		string alter = getCSVNext(line);
		string einkommen = getCSVNext(line);
		string plz = getCSVNext(line);
		TreeNode* node = new TreeNode(name, stoi(alter), stod(einkommen), stoi(plz));
		this->add(node);
	}
	return true;
}

vector<TreeNode*> Tree::search(string Name)
{
	vector<TreeNode*> results;
	searchRecursive(results, Name, anker);
	return results;
}
