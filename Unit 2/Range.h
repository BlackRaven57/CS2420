#pragma once
#include <iostream>
using namespace std;

template <class Type>
class Range;

template <class Type>
ostream& operator << (ostream&, const Range<Type>&); 

template <class Type>
class Range {
    private:
    Type start;
    Type end;
    Type step;

    public:
    Range(Type s, Type e): start(s), end(e), step(1) {}
    Range(Type s, Type e, Type t): start(s), end(e), step(t) {}

    int length() {
        Type x;
        int size = 0;
        if (step > 0) {
            for (Type i = start; i <= end; i += step) {
                size++;
            }
        }
        else {
            for (Type i = start; i >= end; i += step) {
                size++;
            }
        }
        return size;
    }

    Type sum() {
        Type total = 0;
        if (step > 0) {
            for (Type i = start; i <= end; i += step) {
                total += i;
            }
        }
        else {
            for (Type i = start; i >= end; i += step) {
                total += i;
            }
        }
        return total;
    }

    Type average() {
        Type avg = (Type)sum() / (Type)length();
        return avg;
    }

    Type min() {
        Type small = start;
        if (step > 0) {
            for (Type i = start; i <= end; i += step) {
                if (i < small) {
                    small = i;
                }
            }
        }
        else {
            for (Type i = start; i >= end; i += step) {
                if (i < small) {
                    small = i;
                }
            }
        }
        return small;
    }

    Type max() {
        Type big = start;
        if (step > 0) {
            for (Type i = start; i <= end; i += step) {
                if (i > big) {
                    big = i;
                }
            }
        }
        else {
            for (Type i = start; i >= end; i += step) {
                if (i > big) {
                    big = i;
                }
            }
        }
        return big;
    }

    friend ostream& operator << (ostream& out, const Range<Type>& r) {
        out << r.start;
        for (Type i = (r.start + r.step); i <= r.end; i += r.step) {
            out << ", " << i;
        }
        return out;
    }

};