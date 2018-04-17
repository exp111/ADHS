#ifndef _LIST_H
#define _LIST_H
#include "Node.h"
#include <string>
#include <iostream>

template <class T>
class List
{
	/*
	Die Klasse List dient zur Verwaltung von Knoten (Node). Mit Hilfe der Klasse List
	kann ein Stapel oder Warteschlange realisiert werden.
	*/
private:
	struct form { std::string start = "<< "; std::string zwischen = ", "; std::string ende = " >>\n"; } _form;
	Node<T> * head, *tail;			// Zeiger auf Kopf- und End-Element
	int _size;						// Länge der Kette
	bool temp;						// normalerweise false; ist true, wenn es sich um eine temoräre Liste handelt
									// die innerhalb der überladenen Operatoren angelegt wird
public:
	List();
	~List();
	void InsertFront(T key);		// Einfügen eines Knotens am Anfang
	void InsertBack(T key);		// Einfügen eines Knotesn am Ende
	bool getFront(T & key);		// Entnehmen eines Knoten am Anfang
	bool getBack(T & key);		// Entnehmen eines Knoten am Ende
	Node<T>* searchFirst(T key);
	bool del(T key);				// löschen eines Knotens [key]
	bool search(T key);			// Suchen eines Knoten
	bool swap(T key1, T key2);	// Knoten in der Liste vertauschen
	int size(void);					// Größe der Lise (Anzahl der Knoten)
	bool test(void);				// Überprüfen der Zeigerstruktur der Liste

	void format(const std::string & start, const std::string & zwischen, const std::string & ende);	// Mit der format-Methode kann die Ausgabe gesteuert werden: operator <<
	List<T> & operator = (const List<T> & _List);						// Zuweisungsoperator definieren
	List<T> & operator = (const List<T> * _List);						// Zuweisungsoperator definieren
	List<T> & operator + (const List<T> & List_Append);					// Listen zusammenführen zu einer Liste
	List<T> & operator + (const List<T> * List_Append);					// Listen zusammenführen zu einer Liste
	template <typename Tf>
	friend std::ostream & operator << (std::ostream & stream, const List<Tf> & Liste);		// Ausgabeoperator überladen
	template <typename Tf>
	friend std::ostream & operator << (std::ostream & stream, const List<Tf> * Liste);		// Ausgabeoperator überladen
};

template <class T>
List<T>::List()
{
	head = new Node<T>;
	tail = new Node<T>;
	_size = 0;
	temp = false;
	head->next = tail;
	tail->prev = head;
}

template <class T>
List<T>::~List()
{
	//( ... löschen Sie alle noch vorhandenen Knoten Node dieser Instanz 
	// Denken Sie auch den die Knoten head und tail.)
	while (head != nullptr)
	{
		Node<T>* next = head->next;
		delete head;
		head = next;
	}
}

template <class T>
void List<T>::InsertFront(T key)
{
	//( ... Erweitern Sie die Methode so, dass ein neuer Knoten Node vorne
	//	(hinter dem Knoten head) in die Liste eingefügt wird. )

	Node<T>* oldNext = head->next;
	Node<T>* newNode = new Node<T>(key, oldNext, head);

	head->next = newNode;
	oldNext->prev = newNode;

	_size++;
}

template <class T>
void List<T>::InsertBack(T key)
{
	//( ... Erweitern Sie die Methode so, dass ein neuer Knoten Node hinten
	//	(vor dem Knoten tail) in die Liste eingefügt wird. )

	Node<T>* oldPrev = tail->prev;
	Node<T>* newNode = new Node<T>(key, tail, oldPrev);

	oldPrev->next = newNode;
	tail->prev = newNode;

	_size++;
}

template <class T>
bool List<T>::getFront(T & key)
{
	//( ... Erweitern Sie die Methode so, dass der erste Knoten der Liste
	//	(hinter head) zurückgegeben und dieser Knoten dann gelöscht wird.
	//	Im Erfolgsfall geben Sie true zurück, sonst false. )

	Node<T>* knoten = head->next;
	if (knoten == nullptr || knoten == tail)
		return false;
	else
	{
		key = knoten->key; //Get Key
						   //Delete
		Node<T>* oldNext = knoten->next;
		delete knoten;
		head->next = oldNext;
		oldNext->prev = head;
		_size--;

		return true;
	}
}

template <class T>
bool List<T>::getBack(T & key)
{
	//(... Erweitern Sie die Methode so, dass der letzte Knoten der Liste
	//	(vor tail) zurückgegeben und dieser Knoten dann gelöscht wird.
	//	Im Erfolgsfall geben Sie true zurück, sonst false. )
	Node<T>* knoten = tail->prev;
	if (knoten == nullptr || knoten == head)
		return false;
	else
	{
		key = knoten->key; //Get Key
						   //Delete
		Node<T>* oldPrev = knoten->prev;
		delete knoten;
		oldPrev->next = tail;
		tail->prev = oldPrev;

		_size--;

		return true;
	}
}

template <class T>
Node<T>* List<T>::searchFirst(T key)
{
	Node<T>* knoten = head->next;
	while (knoten != nullptr && knoten != tail)
	{
		if (knoten->key == key)
			return knoten;
		knoten = knoten->next;
	}
	return nullptr;
}

template <class T>
bool List<T>::del(T key)
{
	//(... Die Methode del sucht den Knoten mit dem Wert Key und löscht diesen
	//	im Erfolgsfall aus der Liste.
	//	Im Erfolgsfall geben Sie true zurück, sonst false. )
	Node<T>* knoten = searchFirst(key);
	if (knoten == nullptr) //Check for find
		return false;

	//Backup near
	Node<T>* oldPrev = knoten->prev;
	Node<T>* oldNext = knoten->next;
	//Delete
	delete knoten;
	_size--;
	//Connect near Nodes
	oldPrev->next = oldNext;
	oldNext->prev = oldPrev;

	return true;
}

template <class T>
bool List<T>::search(T key)
{
	//(... Die Methode search sucht den Knoten mit dem Wert key
	//	Im Erfolgsfall geben Sie true zurück, sonst false. )
	return searchFirst(key) != nullptr;
}

template <class T>
bool List<T>::swap(T key1, T key2)
{
	//(... Die Methode swap sucht den Knoten mit dem Wert key1,
	//	dann den Knoten mit dem Wert key2. Diese Knoten werden dann
	//	getauscht, indem die Zeiger der Knoten entsprechend geändert
	//	werden. )
	Node<T>* firstKnoten = searchFirst(key1);
	Node<T>* secondKnoten = searchFirst(key2);
	if (firstKnoten == nullptr || secondKnoten == nullptr)
		return false;

	//firstKnoten->key = key2; //Ghetto method
	//secondKnoten->key = key1;
	//return true;

	Node<T>* firstPrev = firstKnoten->prev;
	Node<T>* firstNext = firstKnoten->next;

	Node<T>* secondPrev = secondKnoten->prev;
	Node<T>* secondNext = secondKnoten->next;

	//First
	firstKnoten->prev = secondPrev;
	secondPrev->next = firstKnoten;
	firstKnoten->next = secondNext;
	secondNext->prev = firstKnoten;

	//Second
	secondKnoten->prev = firstPrev;
	firstPrev->next = secondKnoten;
	secondKnoten->next = firstNext;
	firstNext->prev = secondKnoten;
	return true;
}

template <class T>
int List<T>::size(void)
{
	// (... Die Methode gibt den Wert von size (Anzahl der Knoten in der Liste) zurück. )
	return _size;
}

template <class T>
bool List<T>::test(void)
{
	//(... Die Methode überprüft die Pointer der Liste. Gestartet wird mit head. Es werden alle 
	//	Knoten bis zum tail durchlaufen von dort aus dann die prev-Zeiger bis zum head.
	//	Bei Erfolg wird true zurück gegeben. )

	//Start at head
	Node<T>* knoten = head;
	while (knoten->next != nullptr) //Go till we have no more
	{
		knoten = knoten->next;
	}
	if (knoten != tail) //If we're not at tail frick off
		return false;
	//Start at tail
	knoten = tail;
	while (knoten->prev != nullptr) //Go till we have no more
	{
		knoten = knoten->prev;
	}
	return knoten == head; //Are we at head again? -> return true
}

template <class T>
void List<T>::format(const std::string & start, const std::string & zwischen, const std::string & ende)
{
	_form.start = start;
	_form.zwischen = zwischen;
	_form.ende = ende;
}

template <class T>
List<T> & List<T>::operator = (const List<T> & _List)
{
	// in dem Objekt _List sind die Knoten enthalten, die Kopiert werden sollen.
	// Kopiert wird in das Objekt "this"
	if (this == &_List) return *this;	//  !! keine Aktion notwendig
	Node<T> * tmp_node;
	if (_size)
	{
		Node<T> * tmp_del;
		tmp_node = head->next;
		while (tmp_node != tail)		// Alle eventuell vorhandenen Knoten in this l�schen
		{
			tmp_del = tmp_node;
			tmp_node = tmp_node->next;
			delete tmp_del;
		}
		_size = 0;
		head->next = tail;
		tail->prev = head;
	}
	tmp_node = _List.head->next;
	while (tmp_node != _List.tail)
	{
		InsertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	if (_List.temp) delete & _List;		// ist die �bergebene Liste eine tempor�re Liste? -> aus Operator +
	return *this;
}

template <class T>
List<T> & List<T>::operator = (const List<T> * _List)
{
	// in dem Objekt _List sind die Knoten enthalten, die Kopiert werden sollen.
	// Kopiert wird in das Objekt "this"
	if (this == _List) return *this;	//  !! keine Aktion notwendig
	Node<T> * tmp_node;
	if (_size)
	{
		Node<T> * tmp_del;
		tmp_node = head->next;
		while (tmp_node != tail)		// Alle eventuell vorhandenen Knoten in this l�schen
		{
			tmp_del = tmp_node;
			tmp_node = tmp_node->next;
			delete tmp_del;
		}
		_size = 0;
		head->next = tail;
		tail->prev = head;
	}
	tmp_node = _List->head->next;
	while (tmp_node != _List->tail)
	{
		InsertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	if (_List->temp) delete _List;		// ist die �bergebene Liste eine tempor�re Liste? -> aus Operator +
	return *this;
}

template <class T>
List<T> & List<T>::operator + (List<T> const & List_Append)
{
	Node<T> * tmp_node;
	List * tmp;
	if (temp) {								// this ist eine tempor�re Liste und kann ver�ndert werden
		tmp = this;
	}
	else {
		tmp = new List<T>;					// this ist keine tempor�re Liste -> Kopie erzeugen
		tmp->temp = true;					// Merker setzten, dass es sich um eine tempor�re Liste handelt
		tmp_node = head->next;
		while (tmp_node != tail) {
			tmp->InsertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append._size) {				// anh�ngen der �bergebenen Liste an tmp
		tmp_node = List_Append.head->next;
		while (tmp_node != List_Append.tail) {
			tmp->InsertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append.temp) delete & List_Append;		// wurde eine tempor�re Liste �bergeben, dann wird diese gel�scht							// 
	return *tmp;
}

template <class T>
List<T> & List<T>::operator + (List<T> const * List_Append)
{
	Node<T> * tmp_node;
	List * tmp;
	if (temp) {								// this ist eine temporäre Liste und kann verändert werden
		tmp = this;
	}
	else {
		tmp = new List<T>;					// this ist keine temporäre Liste -> Kopie erzeugen
		tmp->temp = true;					// Merker setzten, dass es sich um eine temporäre Liste handelt
		tmp_node = head->next;
		while (tmp_node != tail) {
			tmp->InsertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append->_size) {				// anhängen der übergebenen Liste an tmp
		tmp_node = List_Append->head->next;
		while (tmp_node != List_Append->tail) {
			tmp->InsertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append->temp) delete List_Append;		// wurde eine temporäre Liste übergeben, dann wird diese gelöscht							// 
	return *tmp;
}


template <class Tf>
std::ostream & operator << (std::ostream  & stream, const List<Tf> & Liste)
{
	stream << Liste._form.start;
	for (Node<Tf> * tmp = Liste.head->next; tmp != Liste.tail; tmp = tmp->next)
		stream << tmp->key << (tmp->next == Liste.tail ? Liste._form.ende : Liste._form.zwischen);
	if (Liste.temp) delete & Liste;			// wurde eine temporäre Liste übergeben, dann wird diese gelöscht
	return stream;
}

template <class Tf>
std::ostream & operator << (std::ostream  & stream, const List<Tf> * Liste)
{
	stream << Liste->_form.start;
	for (Node<Tf> * tmp = Liste->head->next; tmp != Liste->tail; tmp = tmp->next)
		stream << tmp->key << (tmp->next == Liste->tail ? Liste->_form.ende : Liste->_form.zwischen);
	if (Liste->temp) delete Liste;			// wurde eine temporäre Liste übergeben, dann wird diese gelöscht
	return stream;
}

#endif