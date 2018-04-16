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
		oldAnker->next = Anker;

		size++;

		//Increase Age by 1 of all
		RingNode* tmp = Anker->next;
		while (tmp != nullptr && tmp != Anker) //FindLast
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
		oldAnker->next = Anker;

		delete toDelete;

		//Increase Age by 1 of all
		RingNode* tmp = Anker->next;
		while (tmp != nullptr && tmp != Anker) //FindLast
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
		{
			tmp = tmp->next;
			if (tmp == Anker)
				break;
		}
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

		if (tmp == Anker)
			break;
	}
}
