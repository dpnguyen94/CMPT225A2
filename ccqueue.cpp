#include "ccqueue.h"

CCQueue::CCQueue() {
	maxticketid = 0;
}

bool CCQueue::Add(string customer, string complaint) {
	if (customer == "" || complaint == "") return false;

	tickets.InsertBack(Ticket(maxticketid + 1,customer,complaint));
	maxticketid ++;
	return true;
}

Ticket CCQueue::Service() {
	if (!tickets.IsEmpty()) return tickets.RemoveAt(0);
	else throw std::logic_error("Ticket queue is empty");
}

bool CCQueue::MoveUp(int index) {
	if (index <= 0 || tickets.Size() <= index) return false;
	tickets.InsertAt(tickets.ElementAt(index),index - 1);
	tickets.RemoveAt(index + 1);

	return true;
}

bool CCQueue::MoveDown(int index) {
	if (index < 0 || tickets.Size() - 1 <= index) return false;
	tickets.InsertAt(tickets.ElementAt(index),index + 2);
	tickets.RemoveAt(index);

	return true;
}

int CCQueue::Size() const {
	return tickets.Size();
}