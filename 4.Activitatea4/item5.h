#ifndef ITEM5_H
#define ITEM5_H

#include <iostream>
#include <string>

// 1. Clasa goala

// class Empty {
// public:
//     Empty() { ... }                             // constructor implicit
//     Empty(const Empty& rhs) { ... }             // copy constructor 
//     ~Empty() { ... }                            // destructor
//     Empty& operator=(const Empty& rhs) { ... }  // operator=
// };

class Empty {};

// 2. Copierea generata e membru cu membru
class Student {
public:

    Student(const std::string& n, int g) : name(n), grade(g) {}

    void print() const {
        std::cout << "Student " << name << ", nota " << grade << "\n";
    }
private:
    std::string name;
    int grade;
};

// 3. Pointer -> copie superficiala (shallow copy)
class Holder {
public:
    explicit Holder(int* p) : ptr(p) {}
    int* ptr;
};

// 4. Cand operator= NU este generat
template<typename T>
class NamedObject {
public:
    
    NamedObject(std::string& name, const T& value)
        : nameValue(name), objectValue(value) {}

    void print() const {
        std::cout << "NamedObject " << nameValue << " = " << objectValue << "\n";
    }
private:
    std::string& nameValue;   // referinta
    const T objectValue;      // const
};

#endif
