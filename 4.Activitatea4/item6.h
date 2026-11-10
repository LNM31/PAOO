#ifndef ITEM6_H
#define ITEM6_H

#include <iostream>
#include <string>

// Varianta moderna (C++11 +)
class HomeForSale {
public:
    explicit HomeForSale(const std::string& addr) : address(addr) {}

    HomeForSale(const HomeForSale&) = delete;             // fara copiere
    HomeForSale& operator=(const HomeForSale&) = delete;  // fara atribuire

    void print() const { std::cout << "HomeForSale: " << address << "\n"; }
private:
    std::string address;
};

// Varianta din carte (C++98): private + nedefinit
class Uncopyable {
protected:
    Uncopyable() {}      
    ~Uncopyable() {}    
private:
    Uncopyable(const Uncopyable&);             
    Uncopyable& operator=(const Uncopyable&);   
};

class OldHomeForSale : private Uncopyable {
public:
    explicit OldHomeForSale(const std::string& addr) : address(addr) {}
    void print() const { std::cout << "OldHomeForSale: " << address << "\n"; }
private:
    std::string address;
};

#endif
