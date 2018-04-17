#include "List.h"

List::List()
{
	head = new Node;
	tail = new Node;
	_size = 0;
	temp = false;
	head->next = tail;
	tail->prev = head;
}
List::~List()
{
	//( ... löschen Sie alle noch vorhandenen Knoten Node dieser Instanz 
	// Denken Sie auch den die Knoten head und tail.)
	while (head != nullptr)
	{
		Node* next = head->next;
		delete head;
		head = next;
	}
}
void List::InsertFront(int key)
{
	//( ... Erweitern Sie die Methode so, dass ein neuer Knoten Node vorne
	//	(hinter dem Knoten head) in die Liste eingefügt wird. )
	
	Node* oldNext = head->next;
	Node* newNode = new Node(key, oldNext, head);

	head->next = newNode;
	oldNext->prev = newNode;

	_size++;
}
void List::InsertBack(int key)
{
	//( ... Erweitern Sie die Methode so, dass ein neuer Knoten Node hinten
	//	(vor dem Knoten tail) in die Liste eingefügt wird. )
	
	Node* oldPrev = tail->prev;
	Node* newNode = new Node(key, tail, oldPrev);

	oldPrev->next = newNode;
	tail->prev = newNode;

	_size++;
}
bool List::getFront(int & key)
{
	//( ... Erweitern Sie die Methode so, dass der erste Knoten der Liste
	//	(hinter head) zurückgegeben und dieser Knoten dann gelöscht wird.
	//	Im Erfolgsfall geben Sie true zurück, sonst false. )

	Node* knoten = head->next;
	if (knoten == nullptr || knoten == tail)
		return false;
	else
	{
		key = knoten->key; //Get Key
		//Delete
		Node* oldNext = knoten->next;
		delete knoten;
		head->next = oldNext;
		oldNext->prev = head;

		_size--;

		return true;
	}
}
bool List::getBack(int & key)
{
	//(... Erweitern Sie die Methode so, dass der letzte Knoten der Liste
	//	(vor tail) zurückgegeben und dieser Knoten dann gelöscht wird.
	//	Im Erfolgsfall geben Sie true zurück, sonst false. )
	Node* knoten = tail->prev;
	if (knoten == nullptr || knoten == head)
		return false;
	else
	{
		key = knoten->key; //Get Key
		//Delete
		Node* oldPrev = knoten->prev;
		delete knoten;
		oldPrev->next = tail;
		tail->prev = oldPrev;

		_size--;

		return true;
	}
}
Node* List::searchFirst(int key)
{
	Node* knoten = head->next;
	while (knoten != nullptr && knoten != tail)
	{
		if (knoten->key == key)
			return knoten;
		knoten = knoten->next;
	}
	return nullptr;
}
bool List::del(int key)
{
	//(... Die Methode del sucht den Knoten mit dem Wert Key und löscht diesen
	//	im Erfolgsfall aus der Liste.
	//	Im Erfolgsfall geben Sie true zurück, sonst false. )
	Node* knoten = searchFirst(key);
	if (knoten == nullptr) //Check for find
		return false;

	//Backup near
	Node* oldPrev = knoten->prev;
	Node* oldNext = knoten->next;
	delete knoten; //Delete
	_size--;
	//Connect near Nodes
	oldPrev->next = oldNext;
	oldNext->prev = oldPrev;

	return true;
}
bool List::search(int key)
{
	//(... Die Methode search sucht den Knoten mit dem Wert key
	//	Im Erfolgsfall geben Sie true zurück, sonst false. )
	return searchFirst(key) != nullptr;
}
bool List::swap(int key1, int key2)
{
	//(... Die Methode swap sucht den Knoten mit dem Wert key1,
	//	dann den Knoten mit dem Wert key2. Diese Knoten werden dann
	//	getauscht, indem die Zeiger der Knoten entsprechend geändert
	//	werden. )
	Node* firstKnoten = searchFirst(key1);
	Node* secondKnoten = searchFirst(key2);
	if (firstKnoten == nullptr || secondKnoten == nullptr)
		return false;

	//firstKnoten->key = key2; //Ghetto method
	//secondKnoten->key = key1;
	//return true;

	Node* firstPrev = firstKnoten->prev;
	Node* firstNext = firstKnoten->next;

	Node* secondPrev = secondKnoten->prev;
	Node* secondNext = secondKnoten->next;

	if (firstPrev == secondKnoten || secondNext == firstKnoten)
	{
		firstKnoten->prev = secondPrev;
		firstKnoten->next = secondKnoten;
		secondKnoten->prev = firstKnoten;
		secondKnoten->next = firstNext;

		firstNext->prev = secondKnoten;
		secondPrev->next = firstKnoten;
	}
	else if (secondPrev == firstKnoten || firstNext == secondKnoten)
	{
		secondKnoten->prev = firstPrev;
		secondKnoten->next = firstKnoten;
		firstKnoten->prev = secondKnoten;
		firstKnoten->next = secondNext;

		secondNext->prev = firstKnoten;
		firstPrev->next = secondKnoten;
	}
	else
	{
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
	}
	return true;
}
int List::size(void)
{
	// (... Die Methode gibt den Wert von size (Anzahl der Knoten in der Liste) zurück. )
	return _size;
}
bool List::test(void)
{
	//(... Die Methode überprüft die Pointer der Liste. Gestartet wird mit head. Es werden alle 
	//	Knoten bis zum tail durchlaufen von dort aus dann die prev-Zeiger bis zum head.
	//	Bei Erfolg wird true zurück gegeben. )

	//Start at head
	Node* knoten = head;
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

void List::format(const std::string & start, const std::string & zwischen, const std::string & ende)
{
	_form.start = start;
	_form.zwischen = zwischen;
	_form.ende = ende;
}

List & List::operator = (const List & _List)
{
	// in dem Objekt _List sind die Knoten enthalten, die Kopiert werden sollen.
	// Kopiert wird in das Objekt "this"
	if (this == &_List) return *this;	//  !! keine Aktion notwendig
	Node * tmp_node;
	if (_size)
	{
		Node * tmp_del;
		tmp_node = head->next;
		while (tmp_node != tail)		// Alle eventuell vorhandenen Knoten in this löschen
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
	if (_List.temp) delete & _List;		// ist die Übergebene Liste eine temporäre Liste? -> aus Operator +
	return *this;
}

List & List::operator = (const List * _List)
{
	// in dem Objekt _List sind die Knoten enthalten, die Kopiert werden sollen.
	// Kopiert wird in das Objekt "this"
	if (this == _List) return *this;	//  !! keine Aktion notwendig
	Node * tmp_node;
	if (_size)
	{
		Node * tmp_del;
		tmp_node = head->next;
		while (tmp_node != tail)		// Alle eventuell vorhandenen Knoten in this löschen
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
	if (_List->temp) delete _List;		// ist die Übergebene Liste eine temporäre Liste? -> aus Operator +
	return *this;
}

List & List::operator + (const List & List_Append)
{
	Node * tmp_node;
	List * tmp;
	if (temp){								// this ist eine temporäre Liste und kann verändert werden
		tmp = this;
	}
	else {
		tmp = new List;						// this ist keine temporäre Liste -> Kopie erzeugen
		tmp->temp = true;					// Merker setzten, dass es sich um eine temporäre Liste handelt
		tmp_node = head->next;
		while (tmp_node != tail){
			tmp->InsertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append._size) {				// anhängen der übergebenen Liste an tmp
		tmp_node = List_Append.head->next;
		while (tmp_node != List_Append.tail){
			tmp->InsertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append.temp) delete & List_Append;		// wurde eine temporäre Liste übergeben, dann wird diese gelöscht							// 
	return *tmp;
}

List & List::operator + (const List * List_Append)
{
	Node * tmp_node;
	List * tmp;
	if (temp){								// this ist eine temporäre Liste und kann verändert werden
		tmp = this;
	}
	else {
		tmp = new List;						// this ist keine temporäre Liste -> Kopie erzeugen
		tmp->temp = true;					// Merker setzten, dass es sich um eine temporäre Liste handelt
		tmp_node = head->next;
		while (tmp_node != tail){
			tmp->InsertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append->_size) {				// anhängen der übergebenen Liste an tmp
		tmp_node = List_Append->head->next;
		while (tmp_node != List_Append->tail){
			tmp->InsertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append->temp) delete List_Append;		// wurde eine temporäre Liste übergeben, dann wird diese gelöscht							// 
	return *tmp;
}

std::ostream & operator<<(std::ostream  & stream, List const & Liste)
{
	stream << Liste._form.start;
	for (Node * tmp = Liste.head->next; tmp != Liste.tail; tmp = tmp->next)
		stream << tmp->key << (tmp->next == Liste.tail ? Liste._form.ende : Liste._form.zwischen);
	if (Liste.temp) delete & Liste;			// wurde eine temporäre Liste übergeben, dann wird diese gelöscht
	return stream;
}

std::ostream & operator << (std::ostream & stream, List const * Liste)
{
	stream << Liste->_form.start;
	for (Node * tmp = Liste->head->next; tmp != Liste->tail; tmp = tmp->next)
		stream << tmp->key << (tmp->next == Liste->tail ? Liste->_form.ende : Liste->_form.zwischen);
	if (Liste->temp) delete Liste;			// wurde eine temporäre Liste übergeben, dann wird diese gelöscht
	return stream;
}