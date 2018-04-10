#include <iostream>
#include "RingNode.h"
#include "Ringpuffer.h"
using namespace std;

/*
==================================
2 OneRingToRuleThemAll v0.1, by Sauron Schmidt
3 ==================================
4 1) Backup einfuegen
5 2) Backup suchen
6 3) Alle Backups ausgeben
7 ?> 1 // Beispiel: neuer Datensatz
8 +Neuen Datensatz einfuegen
9 Beschreibung ?> erstes Backup
10 Daten ?> echtWichtig1
11 +Ihr Datensatz wurde hinzugefuegt.
12 [...]
13 ?> 2 // Beispiel: suche Datensatz
14 +Nach welchen Daten soll gesucht werden?
15 ?> echtWichtig1
16 + Gefunden in Backup: OldAge 0, Beschreibung: erstes Backup, Daten: echtWichtig1
17 [...]
18 ?> 3 // Beispiel: Ausgabe aller Backups nach weiteren Operationen
19 OldAge: 0, Descr: sechstes Backup, Data: 0118999
20 --------------------------
21 OldAge: 5, Descr: erstes Backup, Data: echtWichtig1
22 --------------------------
23 OldAge: 4, Descr: zweites Backup, Data: 456
24 --------------------------
25 OldAge: 3, Descr: drittes Backup, Data: 789
26 --------------------------
27 OldAge: 2, Descr: viertes Backup, Data: 007
28 --------------------------
29 OldAge: 1, Descr: fuenftes Backup, Data: 1337
30 --------------------------
*/

/*
Fragen:
1. Flugschreiber, Prozesse in denen nur die neusten Daten gespeichert werden müssen; Queues
2. Ja
3. 10 Jahre
4. Längeres Array, automatisiertes Speichern (keine manuelle Eingabe), mehrere Backups/Ringpuffer pro Jahr
*/
int main()
{
	Ringpuffer* ring = new Ringpuffer;
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
			RingNode* node = ring->search(data);
			if (node != nullptr)
			{
				cout << "+ Gefunden in Backup: ";
				node->print();
			}
			else
				cout << "+ Nicht gefunden.";

			cout << endl;
		}
		else if (input == "3")
		{
			ring->print();
		}

	} while (input != "quit");

	return 0;
}