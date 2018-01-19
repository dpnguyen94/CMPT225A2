#ifdef _DLINKEDLIST_H_

template <class T>
void DLinkedList<T>::CopyList(const DLinkedList& l1) {
	size = 0;
	front = NULL;
	back = NULL;
	for (int i = 0; i < l1.Size(); i ++)
		InsertBack(l1.ElementAt(i));
}

template <class T>
void DLinkedList<T>::DeleteList() {
	Node<T> *temp;
	while (front != NULL) {
		size --;
		temp = front;
		front = front -> next;
		delete temp;
	}
	back = NULL;
}

template <class T>
DLinkedList<T>::DLinkedList() {
	size = 0;
	front = NULL;
	back = NULL;
}

template <class T>
DLinkedList<T>::DLinkedList(const DLinkedList& l1) {
	CopyList(l1);
}

template <class T>
DLinkedList<T>::~DLinkedList() {
	DeleteList();
}


template <class T>
void DLinkedList<T>::InsertFront(T item) {
	
	Node<T> *node = new Node<T>(item);
	if (front != NULL) {
		node -> next = front;
		front -> prev = node;
	}
	front = node;

	size ++;
	if (size == 1) back = front;
}

template <class T>
void DLinkedList<T>::InsertBack(T item) {
	Node<T> *node = new Node<T>(item);
	if (back != NULL) {
		node -> prev = back;
		back -> next = node;
	}
	back = node;

	size ++;
	if (size == 1) front = back;
}

template <class T>
void DLinkedList<T>::InsertAt(T item, int p) {
	if (p == 0) InsertFront(item);
	else if (p == size) InsertBack(item);
	else if (0 < p && p < size) {
		size ++;
		Node<T> *temp = front;
		for (int i = 0; i < p; i ++)
			temp = temp -> next;
		
		Node<T>* node = new Node<T>(item);
		temp -> prev -> next = node;
		node -> prev = temp -> prev;
		node -> next = temp;
		temp -> prev = node;

	} else throw std::exception("Invalid index");
}

template <class T>
T DLinkedList<T>::RemoveAt(int p) {
	T result;
	Node<T> *temp;
	if (size > 0) {
		if (p == 0) {
			size --;
			temp = front;
			front = front -> next;
			front -> prev = NULL;
			result = temp -> data;
			delete temp;
		} else if (p == size - 1) {
			size --;
			temp = back;
			back = back -> prev;
			back -> next = NULL;
			result = temp -> data;
			delete temp;
		} else if (0 < p && p < size - 1) {
			size --;
			temp = front;
			for (int i = 0; i < p; i ++) 
				temp = temp -> next;
			
			temp -> prev -> next = temp -> next;
			temp -> next -> prev = temp -> prev;

			result = temp -> data;
			delete temp;
		} else throw std::exception("Invalid index");
	} else throw std::exception("List is empty");

	return result;
}

template <class T>
void DLinkedList<T>::RemoveDuplicates() {
	for (int i = 0; i < size - 1; i ++) {
		T item = ElementAt(i);
		for (int k = size - 1; k > i; k --) 
			if (item == ElementAt(k)) RemoveAt(k);
	}
}

template <class T>
int DLinkedList<T>::Size() const {
	return size;
}

template <class T>
bool DLinkedList<T>::IsEmpty() const {
	return (size == 0);
}

template <class T>
bool DLinkedList<T>::Contains(T item) const {
	Node<T> *temp = front;
	while (temp != NULL) {
		if (temp -> data == item) return true;
		temp = temp -> next;
	}

	return false;
}

template <class T>
T DLinkedList<T>::ElementAt(int p) const {
	if (0 <= p && p < size) {
		Node<T> *temp = front;
		for (int i = 0; i < p; i ++) 
			temp = temp -> next;
		return temp -> data;
	} else throw std::exception("Invalid index");
}

template <class T>
DLinkedList<T>& DLinkedList<T>::operator = (const DLinkedList& l1) {
	if (front != l1.front) {
		DeleteList();
		CopyList(l1);
	}

	return *this;
}

#endif 
