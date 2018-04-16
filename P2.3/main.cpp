#include <iostream>
#include "Tree.h"
#include "TreeNode.h"
using namespace std;

int main()
{
	Tree* ring = new Tree;
	cout << "==================================" << endl
		<< "OneRingToRuleThemAll v0.1, by Sauron Schmidt" << endl
		<< "==================================" << endl
		<< "1) Backup einfuegen" << endl
		<< "2) Backup suchen" << endl
		<< "3) Alle Backups ausgeben" << endl;

	string input = "";
	do
	{
		cout << "?> ";
		getline(cin, input);
		if (input == "1")
		{
			//What data
			cout << "+Neuen Datensatz einfuegen" << endl << "Beschreibung ?> ";
			string desc;
			getline(cin, desc);
			cout << "Daten >? ";
			string data;
			getline(cin, data);
			RingNode* node = new RingNode();
			node->setDescription(desc);
			node->setData(data);
			ring->addNode(node);
			cout << "Ihr Datensatz wurde hinzugefuegt." << endl;
		}
		else if (input == "2")
		{
			//What data
			cout << "+Nach welchen Daten soll gesucht werden?" << endl << "?> ";
			string data;
			getline(cin, data);
			/*RingNode* node = ring->search(data);
			if (node != nullptr)
			{
				cout << "+ Gefunden in Backup: ";
				node->print();
			}
			else
				cout << "+ Nicht gefunden.";

			cout << endl;*/
		}
		else if (input == "3")
		{
			ring->print();
		}

	} while (input != "quit");
	return 0;
}