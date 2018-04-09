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
	//( ... l�schen Sie alle noch vorhandenen Knoten Node dieser Instanz 
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
	//	(hinter dem Knoten head) in die Liste eingef�gt wird. )
	
	Node* oldNext = head->next;
	Node* newNode = new Node(key, oldNext, head);

	head->next = newNode;
	oldNext->prev = newNode;
}
void List::InsertBack(int key)
{
	//( ... Erweitern Sie die Methode so, dass ein neuer Knoten Node hinten
	//	(vor dem Knoten tail) in die Liste eingef�gt wird. )
	
	Node* oldPrev = tail->prev;
	Node* newNode = new Node(key, tail, oldPrev);

	oldPrev->next = newNode;
	tail->prev = newNode;
}
bool List::getFront(int & key)
{
	//( ... Erweitern Sie die Methode so, dass der erste Knoten der Liste
	//	(hinter head) zur�ckgegeben und dieser Knoten dann gel�scht wird.
	//	Im Erfolgsfall geben Sie true zur�ck, sonst false. )

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

		return true;
	}
}
bool List::getBack(int & key)
{
	//(... Erweitern Sie die Methode so, dass der letzte Knoten der Liste
	//	(vor tail) zur�ckgegeben und dieser Knoten dann gel�scht wird.
	//	Im Erfolgsfall geben Sie true zur�ck, sonst false. )
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

		return true;
	}
}
bool List::del(int key)
{
	//TODO: (... Die Methode del sucht den Knoten mit dem Wert Key und l�scht diesen
	//	im Erfolgsfall aus der Liste.
	//	Im Erfolgsfall geben Sie true zur�ck, sonst false. )
}
bool List::search(int key)
{
	//TODO: (... Die Methode search sucht den Knoten mit dem Wert key
	//	Im Erfolgsfall geben Sie true zur�ck, sonst false. )
}
bool List::swap(int key1, int key2)
{
	//TODO: (... Die Methode swap sucht den Knoten mit dem Wert key1,
	//	dann den Knoten mit dem Wert key2. Diese Knoten werden dann
	//	getauscht, indem die Zeiger der Knoten entsprechend ge�ndert
	//	werden. )
}
int List::size(void)
{
	//TODO: (... Die Methode git den Wert von size (Anzahl der Knoten in der Liste) zur�ck. )
}
bool List::test(void)
{
	//TODO: (... Die Methode �berpr�ft die Pointer der Liste. Gestartet wird mit head. Es werden alle 
	//	Knoten bis zum tail durchlaufen von dort aus dann die prev-Zeiger bis zum head.
	//	Bei Erfolg wird true zur�ck gegeben. )
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

List & List::operator + (const List & List_Append)
{
	Node * tmp_node;
	List * tmp;
	if (temp){								// this ist eine tempor�re Liste und kann ver�ndert werden
		tmp = this;
	}
	else {
		tmp = new List;						// this ist keine tempor�re Liste -> Kopie erzeugen
		tmp->temp = true;					// Merker setzten, dass es sich um eine tempor�re Liste handelt
		tmp_node = head->next;
		while (tmp_node != tail){
			tmp->InsertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append._size) {				// anh�ngen der �bergebenen Liste an tmp
		tmp_node = List_Append.head->next;
		while (tmp_node != List_Append.tail){
			tmp->InsertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append.temp) delete & List_Append;		// wurde eine tempor�re Liste �bergeben, dann wird diese gel�scht							// 
	return *tmp;
}

List & List::operator + (const List * List_Append)
{
	Node * tmp_node;
	List * tmp;
	if (temp){								// this ist eine tempor�re Liste und kann ver�ndert werden
		tmp = this;
	}
	else {
		tmp = new List;						// this ist keine tempor�re Liste -> Kopie erzeugen
		tmp->temp = true;					// Merker setzten, dass es sich um eine tempor�re Liste handelt
		tmp_node = head->next;
		while (tmp_node != tail){
			tmp->InsertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append->_size) {				// anh�ngen der �bergebenen Liste an tmp
		tmp_node = List_Append->head->next;
		while (tmp_node != List_Append->tail){
			tmp->InsertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append->temp) delete List_Append;		// wurde eine tempor�re Liste �bergeben, dann wird diese gel�scht							// 
	return *tmp;
}

std::ostream & operator<<(std::ostream  & stream, List const & Liste)
{
	stream << Liste._form.start;
	for (Node * tmp = Liste.head->next; tmp != Liste.tail; tmp = tmp->next)
		stream << tmp->key << (tmp->next == Liste.tail ? Liste._form.ende : Liste._form.zwischen);
	if (Liste.temp) delete & Liste;			// wurde eine tempor�re Liste �bergeben, dann wird diese gel�scht
	return stream;
}

std::ostream & operator << (std::ostream & stream, List const * Liste)
{
	stream << Liste->_form.start;
	for (Node * tmp = Liste->head->next; tmp != Liste->tail; tmp = tmp->next)
		stream << tmp->key << (tmp->next == Liste->tail ? Liste->_form.ende : Liste->_form.zwischen);
	if (Liste->temp) delete Liste;			// wurde eine tempor�re Liste �bergeben, dann wird diese gel�scht
	return stream;
}