#include <iostream>
#include <string>
using namespace std;

class Person {
public:
    Person(string name, int amount) : name(name), amount(amount) {}
    int getAmount() const;
    // Person with Person
    bool operator >(const Person &g);
    bool operator <(const Person &g);
    bool operator >=(const Person &g);
    bool operator <=(const Person &g);
    bool operator ==(const Person &g);
    bool operator !=(const Person &g);
    // Person with Int
    bool operator >(int i);
    bool operator <(int i);
    bool operator >=(int i);
    bool operator <=(int i);
    bool operator ==(int i);
    bool operator !=(int i);
    // Int with Person
    friend bool operator >(int i, const Person &g);
    friend bool operator <(int i, const Person &g);
    friend bool operator >=(int i, const Person &g);
    friend bool operator <=(int i, const Person &g);
    friend bool operator ==(int i, const Person &g);
    friend bool operator !=(int i, const Person &g);
    friend ostream& operator <<(ostream &out, const Person &g);
private:
    string name;
    int amount;
};

int Person::getAmount() const {
  return amount;
}

// Person with Person 
bool Person::operator > (const Person &g) {
  return amount > g.amount;
}

bool Person::operator < (const Person &g) {
  return amount < g.amount;
}

bool Person::operator >= (const Person &g) {
  return amount >= g.amount;
}

bool Person::operator <= (const Person &g) {
  return amount <= g.amount;
}

bool Person::operator == (const Person &g) {
    return amount == g.amount;
}

bool Person::operator != (const Person &g) {
    return amount != g.amount;
}

// Person with Int
bool Person::operator > (int i) {
  return amount > i;
}

bool Person::operator < (int i) {
  return amount < i;
}

bool Person::operator >= (int i) {
  return amount >= i;
}

bool Person::operator <= (int i) {
  return amount <= i;
}

bool Person::operator == (int i) {
    return amount == i;
}

bool Person::operator != (int i) {
    return amount != i;
}

// Int with Person
bool operator > (int i, const Person &g) {
  return i > g.amount;
}

bool operator < (int i, const Person &g) {
  return i < g.amount;
}

bool operator >= (int i, const Person &g) {
  return i >= g.amount;
}

bool operator <= (int i, const Person &g) {
  return i <= g.amount;
}

bool operator == (int i, const Person &g) {
    return i == g.amount;
}

bool operator != (int i, const Person &g) {
    return i != g.amount;
}

ostream& operator <<(ostream &out, const Person &g) {
  out << g.name << ": " << g.amount;
  return out;
}
