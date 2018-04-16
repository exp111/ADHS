#include <iostream>
#include "Tree.h"
#include "TreeNode.h"
using namespace std;

/*
==================================== // Beispiel: Menu der Anwendung
2 Person Analyzer v19.84, by George Orwell
3 ====================================
4 1) Datensatz einfuegen, manuell
5 2) Datensatz einfuegen, CSV Datei
6 3) Datensatz loschen
7 4) Suchen
8 5) Datenstruktur anzeigen
9 ?>
10 ------------------------------------------------------------------------------------
11 ?> 1 // Beispiel: manuelles Hinzufugen eines Datensatzes
12 + Bitte geben Sie die den Datensatz ein
13 Name ?> Mustermann
14 Alter ?> 1
15 Einkommen ?> 1000.00
16 PLZ ?> 1
17 + Ihr Datensatz wurde eingefugt
18 ------------------------------------------------------------------------------------
19 ?> 5 // Beispiel: Anzeigen eines Trees mit mehreren Eintragen
20 ID | Name | Alter | Einkommen | PLZ | Pos
21 ---+------------+-------+-----------+-------+-------
22 0 | Mustermann| 1| 1000| 1|1002
23 3 | Hans| 1| 500| 1|502
24 5 | Schmitz| 1| 400| 2|403
25 4 | Schmitt| 1| 500| 2|503
26 1 | Ritter| 1| 2000| 1|2002
27 2 | Kaiser| 1| 3000| 1|3002
28 ------------------------------------------------------------------------------------
29 ?> 4 // Beispiel: Datensatz suchen
30 + Bitte geben Sie den zu suchenden Datensatz an
Name ?> Schmitt
32 + Fundstellen:
33 NodeID: 4, Name: Schmitt, Alter: 1, Einkommen: 500, PLZ: 2, PosID: 503
34 ------------------------------------------------------------------------------------
35 ?> 3 // Beispiel: Datensatz loschen
36 + Bitte geben Sie den zu loschenden Datensatz an
37 PosID ?> 502
38 + Datensatz wurde geloscht.
39 ------------------------------------------------------------------------------------
40 ?> 5 // zum Vergleich nochmal Struktur angezeigt
41 ID | Name | Alter | Einkommen | PLZ | Pos
42 ---+------------+-------+-----------+-------+-------
43 0 | Mustermann| 1| 1000| 1|1002
44 4 | Schmitt| 1| 500| 2|503
45 5 | Schmitz| 1| 400| 2|403
46 1 | Ritter| 1| 2000| 1|2002
47 2 | Kaiser| 1| 3000| 1|3002
48 ------------------------------------------------------------------------------------
49 ?> 2 // Beispiel: CSV Import
50 + Mochten Sie die Daten aus der Datei "ExportZielanalyse.csv" importieren (j/n) ?> j
51 + Daten wurden dem Baum hinzugefugt.
*/
int main()
{
	Tree* ring = new Tree;
	cout << "==================================" << endl
		<< "Person Analyzer v19.84, by George Orwell" << endl
		<< "==================================" << endl
		<< "1) Datensatz einfuegen, manuell" << endl
		<< "2) Datensatz einfuegen, CSV Datei" << endl
		<< "3) Datensatz loschen" << endl
		<< "4) Suchen" << endl
		<< "5) Datenstruktur anzeigen" << endl;

	string input = "";
	do
	{
		cout << "?> ";
		getline(cin, input);
		if (input == "1") //Add manual
		{
			//TODO: add manual
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
		else if (input == "2") //Add .csv
		{
			//TODO: Add csv
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
		else if (input == "3") //Delete Data
		{
			//TODO: Delete
			ring->print();
		}
		else if (input == "4") //Search
		{
			//TODO: Search
		}
		else if (input == "5") //Print
		{
			//TODO: Print
		}

	} while (input != "quit");
	return 0;
}