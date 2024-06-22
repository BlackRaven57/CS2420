#pragma once
#include <iostream>
#include <memory>
#include <cmath>
using namespace std;

template <class Type>
struct Node
{
	Type data;
	shared_ptr<Node<Type>> next;
};

// Used for writing the test cases for the merge sort
template <typename Type>
class LinkedListIterator
{
public:
	LinkedListIterator(shared_ptr<Node<Type>> ptr) : current(ptr) {}
	LinkedListIterator<Type> &operator++()
	{
		current = current->next;
		return *this;
	}
	Type operator*() { return current->data; }
	bool operator==(const LinkedListIterator<Type> &rhs) const { return current == rhs.current; }
	bool operator!=(const LinkedListIterator<Type> &rhs) const { return current != rhs.current; }
	shared_ptr<Node<Type>> getNode() { return current; }

private:
	shared_ptr<Node<Type>> current;
};

template <class Type>
class LinkedList;

template <class Type>
ostream &operator<<(ostream &out, const LinkedList<Type> &list);

template <class Type>
class LinkedList
{
public:
	// Default constructor for the LinkedList. Creates an empty list by setting front and back of the list to nulllptr
	LinkedList() : front(nullptr), back(nullptr), count(0) {}
	void insert(Type data);
	Type peek(int ndx) const;
	void remove(int ndx);
	friend ostream &operator<< <>(ostream &out, const LinkedList<Type> &list);
	void mergeSort();
	LinkedListIterator<Type> begin() { return LinkedListIterator<Type>(front); }
	void mergeSort(shared_ptr<Node<Type>> head);
	shared_ptr<Node<Type>> getMiddle(shared_ptr<Node<Type>> head);
	shared_ptr<Node<Type>> mergeInOrder(shared_ptr<Node<Type>> a, shared_ptr<Node<Type>> b);

protected:
	shared_ptr<Node<Type>> front;
	shared_ptr<Node<Type>> back;
	int count;
};

// Adds to the back of the list
template <class Type>
void LinkedList<Type>::insert(Type data)
{
	auto temp = make_shared<Node<Type>>();
	temp->data = data;
	temp->next = nullptr;
	if (!front)
	{
		front = temp;
		back = temp;
	}
	else
	{
		back->next = temp;
		back = temp;
	}
	count++;
}

// Looks at an element at the given ndx value
template <class Type>
Type LinkedList<Type>::peek(int ndx) const
{
	if (ndx >= count || ndx < 0)
	{
		throw runtime_error("Out of range");
	}
	int currNodeNum = 0;
	auto currentNode = front;
	while (currNodeNum < ndx)
	{
		currNodeNum++;
		currentNode = currentNode->next;
	}
	return currentNode->data;
}

// Removes an element at the given ndx position
template <class Type>
void LinkedList<Type>::remove(int ndx)
{
	if (ndx >= count || ndx < 0)
	{
		throw runtime_error("Out of range");
	}
	// If removing the front
	if (ndx == 0)
	{
		auto toDelete = front;
		front = toDelete->next;
		return;
	}
	int currNodeNum = 0;
	auto currentNode = front;
	while (currNodeNum < ndx - 1)
	{
		currNodeNum++;
		currentNode = currentNode->next;
	}
	auto toDelete = currentNode->next;

	// Deleting from middle
	if (toDelete->next)
	{
		currentNode->next = toDelete->next;
	}
	// Delete last node
	else
	{
		currentNode->next = nullptr;
		back = currentNode;
	}
	count--;
}

// Returns an output stream for displaying the LinkedList
template <class Type>
ostream &operator<<(ostream &out, const LinkedList<Type> &list)
{
	auto curr = list.front;
	while (curr)
	{
		out << curr->data;
		if (curr->next)
		{
			out << " ";
		}
		curr = curr->next;
	}
	return out;
}

template <class Type>
void LinkedList<Type>::mergeSort()
{
	mergeSort(front);
}

/*************************************************************************
 *  TODO:  Complete the mergeSort(head) method. This method should return
 *           a sorted version of the list using the merge sort.
 *  ALGORITHM:
 *       If there is 0 or 1 node in the list,
 *           exit the method (return;)
 *       Find the middle Node (mid)
 *       let left = the head pointer of the first partition (the head)
 *       let right = the head pointer of the second half of the list (to the right of mid)
 *       Split the list by setting the mid->next to null
 *
 *       Sort the left side (hint, use recursion)
 *       Sort the right side (hint, more recursion)
 *       Set the head to be the list merged in order
 *************************************************************************/
template <class Type>
void LinkedList<Type>::mergeSort(shared_ptr<Node<Type>> head)
{
	if (head->next == nullptr || head == nullptr)
	{
		return;
	}
	auto mid = getMiddle(head);
	auto left = head;
	auto right = mid->next;
	mid->next = nullptr;
	mergeSort(left);
	mergeSort(right);
	head = mergeInOrder(left, right);
}

template <class Type>
shared_ptr<Node<Type>> LinkedList<Type>::getMiddle(shared_ptr<Node<Type>> head)
{
	int cnt = 0;
	auto curr = head;
	while (curr != nullptr)
	{
		curr = curr->next;
		cnt++;
	}
	int odd = cnt % 2;
	int num = ceil(cnt / 2);
	curr = head;
	if (odd == 0)
	{
		for (int i = 1; i < num; i++)
		{
			curr = curr->next;
		}
		return curr;
	}
	for (int i = 1; i < num + 1; i++)
	{
		curr = curr->next;
	}
	return curr;
}

template <class Type>
shared_ptr<Node<Type>> LinkedList<Type>::mergeInOrder(shared_ptr<Node<Type>> a, shared_ptr<Node<Type>> b)
{
	shared_ptr<Node<Type>> newHead = nullptr;
	auto currA = a;
	auto currB = b;
	auto curr = a;
	// If a is empty
	if (a == nullptr)
	{
		return b;
	}
	// If b is empty
	else if (b == nullptr)
	{
		return a;
	}
	// If a starts smaller than b
	else if (a->data < b->data)
	{
		newHead = a;
		currA = currA->next;
		curr = newHead;
	}
	// If b starts smaller than a
	else
	{
		newHead = b;
		currB = currB->next;
		curr = newHead;
	}
	while (currA != nullptr || currB != nullptr)
	{
		if (currA == nullptr)
		{
			curr->next = currB;
			currB = currB->next;
			curr = curr->next;
		}
		else if (currB == nullptr)
		{
			curr->next = currA;
			currA = currA->next;
			curr = curr->next;
		}
		else if (currA->data < currB->data)
		{
			curr->next = currA;
			curr = curr->next;
			currA = currA->next;
		}
		else if (currB->data < currA->data)
		{
			curr->next = currB;
			curr = curr->next;
			currB = currB->next;
		}
		else
		{
			curr->next = currA;
			curr = curr->next;
			curr->next = currB;
			curr = curr->next;
			currA = currA->next;
			currB = currB->next;
		}
	}
	curr = newHead;
	while (curr != nullptr) {
		cout << curr->data << ", ";
		curr = curr->next;
	}
	cout << endl;
	return newHead;
}
