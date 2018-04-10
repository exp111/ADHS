#include "Ringpuffer.h"

Ringpuffer::Ringpuffer()
{
	size = 0;
}


Ringpuffer::~Ringpuffer()
{
	while (Anker != nullptr)
	{
		RingNode* tmp = Anker->next;
		delete Anker;
		Anker = tmp;
	}
}

RingNode* Ringpuffer::getLast()
{
	RingNode* tmp = Anker;
	if (tmp == nullptr) //IsEmpty?
		return nullptr;
	while (tmp->next != nullptr) //FindLast
	{
		tmp = tmp->next;
	}
	return tmp;
}

void Ringpuffer::addNode(RingNode * Node)
{
	if (Anker == nullptr)
	{
		Anker = Node;
		size++;
		return;
	}

	if (size < 6)
	{
		//Put Node after old Anker
		RingNode* oldAnker = Anker;
		Anker = Node;
		Anker->next = oldAnker->next != nullptr ? oldAnker->next : oldAnker;
		getLast()->next = oldAnker->next != nullptr ? oldAnker : nullptr;
		oldAnker->next = nullptr;

		size++;

		//Increase Age by 1 of all
		RingNode* tmp = Anker->next;
		while (tmp != nullptr) //FindLast
		{
			tmp->setAge(tmp->getAge() + 1);
			tmp = tmp->next;
		}
	}
	else
	{
		//Put Node after old Anker
		RingNode* oldAnker = Anker;
		Anker = Node;
		RingNode* toDelete = oldAnker->next;
		Anker->next = toDelete->next;
		getLast()->next = oldAnker;
		oldAnker->next = nullptr;

		delete toDelete;

		//Increase Age by 1 of all
		RingNode* tmp = Anker->next;
		while (tmp != nullptr) //FindLast
		{
			tmp->setAge(tmp->getAge() + 1);
			tmp = tmp->next;
		}
	}
}

RingNode* Ringpuffer::search(string Data)
{
	RingNode* tmp = Anker;
	while (tmp != nullptr)
	{
		if (tmp->getData() == Data)
			return tmp;
		else
			tmp = tmp->next;
	}
	return nullptr;
}

void Ringpuffer::print()
{
	RingNode* tmp = Anker;
	while (tmp != nullptr)
	{
		tmp->print();
		cout << endl;
		cout << "--------------------------" << endl;
		tmp = tmp->next;
	}
}
