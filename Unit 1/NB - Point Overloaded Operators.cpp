#include <iostream>
using namespace std;

template <class Type>
class Point;

template <class Type>
ostream& operator << (ostream&, const Point<Type>&);

template <class Type>
istream& operator >> (istream&, Point<Type>&);


template <class Type>
class Point {
    private:
        Type x;
        Type y;

    public:
        Point(){x=0; y=0;}
        Point(Type x, Type y): x(x), y(y){}

        Point<Type> operator+ (const Point<Type>& p) {
            Point p3(x + p.x, y + p.y);
            return p3;
        }

        Point<Type> operator- (const Point<Type>& p) {
            Point p3(x - p.x, y - p.y);
            return p3;
        }

        Point<Type> operator+= (const Point<Type>& p) {
            x += p.x;
            y += p.y;
            return *this;
        }

        Point<Type> operator-= (const Point<Type>& p) {
            x -= p.x;
            y -= p.y;
            return *this;
        }

        friend ostream& operator<< (ostream& out, const Point<Type>& p) {
            out << "(" << p.x << ", " << p.y << ")";
            return out;
        }

        friend istream& operator>> (istream& in, Point<Type>& p) {
            in >> p.x >> p.y;
            return in;
        }
};



int main() {
    Point<int> p1;
    cout << "Point 1:" << endl;
    cin >> p1;

    Point<int> p2;
    cout << "Point 2:" << endl;
    cin >> p2;

    Point<int> p3 = p1 + p2;
    cout << p1 << " + " << p2 << " = " << p3 << endl;
    
    Point<int> p4 = p1 - p2;
    cout << p1 << " - " << p2 << " = " << p4 << endl;

    p1 += p2;
    cout << "Increment p1 by p2 to get " << p1 << endl;

    p3 -= p4;
    cout << "Remove p4 from p3 to get " << p3 << endl;
    return 0;
}
