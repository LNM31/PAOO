#include <iostream>
#include <string>
#include "item4.h"
#include "item5.h"
#include "item6.h"

// Item 4: obiecte globale
int globalCounter;

Directory tempDir;

void demoItem4() {
    std::cout << "\n===== ITEM 4: Initializeaza obiectele inainte de folosire =====\n";

    std::cout << "\n--- 1. Tipuri built-in ---\n";
    int x = 0;          
    // int y;  
    Point p;  
    std::cout << "x = " << x << "\n";
    std::cout << "globalCounter = " << globalCounter << " (global -> 0 automat)\n";
    std::cout << "Point p = (" << p.x << ", " << p.y << ")\n";

    std::cout << "\n--- 2. Atribuire vs. lista de initializare ---\n";
    Name name("Ion Popescu");
    std::cout << "ABEntryAssign (atribuire in corp) -> 2 pasi:\n";
    ABEntryAssign e1(name, 123456);
    std::cout << "ABEntry (lista de initializare) -> 1 pas:\n";
    ABEntry e2(name, 123456);

    std::cout << "\n--- 3. Ordinea de initializare ---\n";
    Rectangle r(3, 4);
    r.print();

    std::cout << "\n--- 4. Obiecte statice din fisiere diferite ---\n";
    std::cout << "tempDir (global) a fost construit INAINTE de main() -> vezi primele linii\n";
    std::cout << "tfs().numDisks() = " << tfs().numDisks()
              << " (acelasi FileSystem, nu se mai construieste inca o data)\n";
}

void demoItem5() {
    std::cout << "\n===== ITEM 5: Ce functii scrie C++ pe ascuns =====\n";

    std::cout << "\n--- 1. Clasa goala ---\n";
    Empty e1;          // constructor implicit
    Empty e2(e1);      // constructor de copiere 
    e2 = e1;           // operator=
    std::cout << "Empty: construit, copiat si atribuit fara sa scriem nicio functie\n";


    std::cout << "\n--- 2. Copiere membru cu membru ---\n";
    Student s1("Ana", 10);
    Student s2(s1);           
    Student s3("Mihai", 7);
    s3 = s1;             
    s1.print();
    s2.print();
    s3.print();
    // Student s4;            

    std::cout << "\n--- 3. Pointer -> copie superficiala ---\n";
    int value = 5;
    Holder h1(&value);
    Holder h2(h1);           
    *h2.ptr = 99;            
    std::cout << "h1.ptr = " << h1.ptr << ", h2.ptr = " << h2.ptr << " (aceeasi adresa)\n";
    std::cout << "*h1.ptr = " << *h1.ptr << " (s-a schimbat si prin h1!)\n";

    std::cout << "\n--- 4. Cand operator= NU este generat ---\n";
    std::string newDog("Persephone");
    std::string oldDog("Satch");
    NamedObject<int> p(newDog, 2);
    NamedObject<int> s(oldDog, 36);
    NamedObject<int> c(p);    
    p.print();
    s.print();
    c.print();
    // p = s;               
}

void demoItem6() {
    std::cout << "\n===== ITEM 6: Interzice functiile generate pe care nu le vrei =====\n";

    std::cout << "\n--- C++11: = delete ---\n";
    HomeForSale h1("Str. Lalelelor 1");
    HomeForSale h2("Str. Florilor 2");
    h1.print();
    h2.print();
    // HomeForSale h3(h1);  
    // h1 = h2;             

    std::cout << "\n--- C++98: mostenire privata din Uncopyable ---\n";
    OldHomeForSale o1("Str. Teilor 3");
    OldHomeForSale o2("Str. Plopilor 4");
    o1.print();
    o2.print();
    // OldHomeForSale o3(o1); 
    // o1 = o2;              

    std::cout << "\nCopierea e interzisa: liniile marcate EROARE din main.cpp nu compileaza.\n";
}

int main() {
    demoItem4();
    demoItem5();
    demoItem6();
    return 0;
}
