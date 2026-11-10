#ifndef ITEM4_H
#define ITEM4_H

#include <iostream>
#include <string>

struct Point {
    int x = 0; 
    int y = 0;
};

// 2. Atribuire vs. lista de initializare
class Name {
public:
    Name() {
        std::cout << "    Name()            -> constructor implicit\n";
    }
    Name(const std::string& t) : text(t) {}
    Name(const Name& other) : text(other.text) {
        std::cout << "    Name(const Name&) -> constructor de copiere\n";
    }
    Name& operator=(const Name& other) {
        text = other.text;
        std::cout << "    operator=         -> atribuire\n";
        return *this;
    }
private:
    std::string text;
};

// Varianta gresita
class ABEntryAssign {
public:
    ABEntryAssign(const Name& name, int phone) {
        theName = name;          // acestea sunt atribuiri,
        thePhone = phone;        // NU initializari
        numTimesConsulted = 0;
    }
private:
    Name theName;
    int thePhone;
    int numTimesConsulted;
};

// varianta corecta
class ABEntry {
public:
    ABEntry(const Name& name, int phone)
        : theName(name),
          thePhone(phone),
          numTimesConsulted(0)
    {}
private:
    Name theName;
    int thePhone;
    int numTimesConsulted;
};

// 3. Ordinea de initializare
class Rectangle {
public:
    Rectangle(int w, int h)
        : width(w), height(h), area(width * height) {}

    void print() const {
        std::cout << "Rectangle " << width << " x " << height
                  << ", aria = " << area << "\n";
    }
private:
    int width;        // 1. initializat primul
    int height;       // 2. initializat al doilea
    const int area;   // 3. initializat ultimul
};

// Varianta gresita
// class BadRectangle {
//     const int area;  
//     int width;
//     int height;
// public:
//     BadRectangle(int w, int h) : width(w), height(h), area(width * height) {}
// };

// 4. Obiecte statice din fisiere .cpp diferite
class FileSystem {
public:
    FileSystem() {
        std::cout << "[FileSystem] construit (la prima apelare a lui tfs())\n";
    }
    int numDisks() const { return 4; }
};

FileSystem& tfs();   // definita in item4.cpp

class Directory {
public:
    Directory() {
        int disks = tfs().numDisks();
        std::cout << "[Directory] construit, foloseste " << disks << " discuri\n";
    }
};

#endif
