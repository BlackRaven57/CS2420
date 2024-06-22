#include <iostream>
#include <memory>
using namespace std;

template <class Type> 
struct Node {
	Node(Type d): data(d), next(nullptr) {}
	Type data;
	shared_ptr<Node<Type>> next;
};

template <class Type>
class Queue {
    public:
    // Constructor to create an empty queue
    Queue() {
        front = nullptr;
        cnt = 0;
    }

    // Copy constructor to create a deep copy of the queue
    Queue(const Queue<Type> &q) {
        cnt = 0;
	    auto temp = q.front;
	    front = make_shared<Node<Type>>(temp->data);
	    auto curr = front;
	    cnt++;
	    for (int i = 1; i < q.cnt; i++) {
		    temp = temp->next;
            auto newPtr = make_shared<Node<Type>>(temp->data);
		    curr->next = newPtr;
		    curr = curr->next;
		    cnt++;
	    }
    }

    // Allows the user to create a deep copy of the queue
    Queue<Type> operator = (Queue<Type>& q) {
        clear();
        cnt = 0;
	    auto temp = q.front;
	    front = make_shared<Node<Type>>(temp->data);
	    auto curr = front;
	    cnt++;
	    for (int i = 1; i < q.cnt; i++) {
		    temp = temp->next;
            auto newPtr = make_shared<Node<Type>>(temp->data);
		    curr->next = newPtr;
		    curr = curr->next;
		    cnt++;
	    }
	    return *this;
    }

    // Inserts data at the back of the queue
    void enqueue(Type data) {
        auto newPtr = make_shared<Node<Type>>(data);
        if (cnt == 0) {
            front = newPtr;
        }
        else {
            auto curr = front;
            for (int i = 0; i < cnt - 1; i++) {
                curr = curr->next;
            }
        curr->next = newPtr;
        }
        cnt++;
    }


    // Looks at the value at the front of the queue
    Type peek() {
        return front->data;
    }

    // Removes the front of the queue
    void dequeue() {
        if (cnt > 1) {
            front = front->next;
            cnt--;
        }
        else if (cnt == 1) {
            front = nullptr;
            cnt = 0;
        }
        else if (cnt == 0) {
            throw runtime_error("Empty Stack");
        }
    }

    // Returns true if the queue is empty
    bool isEmpty() {
        return cnt == 0;
    }

    // Empties everything out of the queue
    void clear() {
        front = nullptr;
        cnt = 0;
    }

    // Returns a stream containing all the items in the Queue
    friend ostream& operator << (ostream& out, const Queue<Type>& q) {
        auto temp = q.front;
	    while (temp) {
		    out << temp->data;
		    if (temp->next) {
                out << " ";
            }
		    temp = temp->next;
	    }
	    return out;
    }

    private:
	shared_ptr<Node<Type>> front;
	int cnt;
};
