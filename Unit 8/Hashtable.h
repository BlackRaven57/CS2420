#pragma once
#include <iostream>
#include <memory>
#include <cmath>

using namespace std;

template<class Type>
struct Bucket {
	Type data;
	bool empty = true;
};

template<class Type>
class Hashtable;

template<class Type>
ostream& operator<< (ostream &, Hashtable<Type>&);

template<class Type>
class Hashtable {
	public:
	Hashtable();
	Hashtable(int);
	Hashtable(int, double);
	Hashtable(const Hashtable<Type>& other);
	Hashtable& operator=(const Hashtable<Type>& other);
	int getSize() const;
	int getCapacity() const;
	double getLoadFactorThreshold() const;
	bool empty() const;
	void insert(const Type);
	void rehash();
	static bool isPrime(int num) {
		for (int i = 2; i < num; i++) {
			if (num % i == 0) {
				return false;
			}
		}
		return true;
	}
	static int nextPrime(int num) {
		while (!isPrime(num)) {
			num++;
		}
		return num;
	}
	void remove(int);
	bool contains(int) const;
	int indexOf(int) const;
	void clear();
	friend ostream& operator<< <>(ostream &, Hashtable<Type>&);

	private:
	int hash(Type v) const;
	double loadFactorThreshold;
	int capacity;
	int size;
	unique_ptr<Bucket<Type>[]> htable;
};



template<class Type>
Hashtable<Type>::Hashtable() {
	size = 0;
	capacity = 17;
	loadFactorThreshold = 0.65;
	htable = make_unique<Bucket<Type>[]>(capacity);
}

template<class Type>
Hashtable<Type>::Hashtable(int capacity): capacity(capacity) {
	size = 0;
	loadFactorThreshold = 0.65;
	htable = make_unique<Bucket<Type>[]>(capacity);
}

template<class Type>
Hashtable<Type>::Hashtable(int cap, double fct): capacity(cap), loadFactorThreshold(fct) {
	size = 0;
	htable = make_unique<Bucket<Type>[]>(capacity);
}

template<class Type>
Hashtable<Type>::Hashtable(const Hashtable<Type>& other) {
	size = other.size;
	capacity = other.capacity;
	htable = make_unique<Bucket<Type>[]>(capacity);
	for (int i = 0; i < capacity; i++) {
		htable[i] = other.htable[i];
	}
}

template<class Type>
Hashtable<Type>& Hashtable<Type>::operator=(const Hashtable<Type>& other) {
	size = other.size;
	capacity = other.capacity;
	htable = make_unique<Bucket<Type>[]>(capacity);
	for (int i = 0; i < capacity; i++) {
		htable[i] = other.htable[i];
	}
	return *this;
}

template<class Type>
int Hashtable<Type>::hash(Type v) const {
	return fmod(v, capacity);
}

template<class Type>
int Hashtable<Type>::getSize() const {
	return size;
}

template<class Type>
int Hashtable<Type>::getCapacity() const {
	return capacity;
}

template<class Type>
double Hashtable<Type>::getLoadFactorThreshold() const {
	return loadFactorThreshold;
}

template<class Type>
bool Hashtable<Type>::empty() const {
	if (size == 0) {
		return true;
	}
	return false;
}

template<class Type>
void Hashtable<Type>::insert(Type value) {
	size++;
	if (size >= capacity * loadFactorThreshold) {
		rehash();
	}
	int i = 0;
	int index;
	while (true) {
		index = fmod((value + (i * i)), capacity);
		if (htable[index].empty == true) {
			htable[index] = {value, false};
			return;
		}
		i++;
	}
}

template<class Type>
void Hashtable<Type>::rehash() {
	int index;
	size = 0;
	int i;
	int cap = nextPrime(capacity * 2);
	Hashtable<Type> temp(cap);
	for (int x = 0; x < capacity; x++) {
		if (!htable[x].empty) {
			i = 0;
			while (true) {
				index = fmod((htable[x].data + (i * i)), cap);
				if (temp.htable[index].empty) {
					temp.htable[index] = move(htable[x]);
					size++;
					break;
				}
				i++;
			}
		}
	}
	capacity = cap;
	htable = make_unique<Bucket<Type>[]>(cap);
	for (int i = 0; i < capacity; i++) {
		htable[i] = move(temp.htable[i]);
	}
}

template<class Type>
void Hashtable<Type>::remove(int value) {
	if (capacity == 0) {
		throw runtime_error("Hashtable Empty");
	}
	int i = 0;
	while (htable[hash(value + i)].data != value && i < capacity) {
		i++;
	}
	if (i == capacity) {
		return;
	}
	htable[hash(value + i)] = {0, true};
	size--;
}

template<class Type>
bool Hashtable<Type>::contains(int value) const {
	int i = 0;
	while (htable[hash(value + i)].data != value && i < capacity) {
		i++;
	}
	if (htable[hash(value + i)].data == value) {
		return true;
	}
}

template<class Type>
int Hashtable<Type>::indexOf(int num) const {
	for (int i = 0; i < capacity; i++) {
		if (htable[i].data == num) {
			return i;
		}
	}
	return -1;
}

template<class Type>
void Hashtable<Type>::clear() {
	size = 0;
	htable = make_unique<Bucket<Type>[]>(capacity);
}

template<class Type>
ostream& operator<< (ostream& out, Hashtable<Type>& h) {
	out << "\nCapacity: " << h.capacity << "\n";
	for (int i = 0; i < h.capacity; i++) {
		if (h.htable[i].empty == false) {
			out << i << ": " << h.htable[i].data << endl;
		}
	}
	return out;
}