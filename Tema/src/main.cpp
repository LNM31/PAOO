#include <catalog/bad_examples.hpp>
#include <catalog/student.hpp>

#include <cstring>
#include <iostream>
#include <utility>
#include <vector>

using catalog::LeakyStudent;
using catalog::ShallowStudent;
using catalog::Student;

namespace {

void title(const char* text)
{
    std::cout << "\n==================================================\n"
              << text
              << "\n==================================================\n";
}

void showHeap()
{
    std::cout << "  -> blocuri Student pe heap acum: "
              << Student::liveAllocations() << "\n";
}

// ---------------------------------------------------------------
// 1. Incapsulare
// ---------------------------------------------------------------
void demoEncapsulation()
{
    title("1. INCAPSULARE");
    Student ana("Ana", 1, 3);
    ana.addGrade(9);
    ana.addGrade(10);
    ana.addGrade(15);  // respinsa: nota invalida
    ana.addGrade(8);
    ana.addGrade(7);   // respinsa: nu mai e loc
    ana.print();
    // ana.grades_[0] = 100;  // nu compileaza: grades_ este private
    std::cout << "  Datele nu pot fi stricate din afara clasei: notele\n"
                 "  invalide sunt respinse de addGrade().\n";
}

// ---------------------------------------------------------------
// 2. Initializarea membrilor in constructor
// ---------------------------------------------------------------
void demoInitialization()
{
    title("2. INITIALIZAREA MEMBRILOR IN CONSTRUCTOR");
    std::cout << "  Constructorul foloseste lista de initializare:\n"
                 "    : id_(id), name_(new char[...]), grades_(new int[capacity]),\n"
                 "      capacity_(capacity), count_(0)\n"
                 "  - id_ este const: se poate seta DOAR acolo.\n"
                 "    (vezi: cmake .. -DDEMO_INIT_ERROR=ON -> eroare de compilare)\n"
                 "  - daca grades_ ar ramane neinitializat, ar contine o adresa\n"
                 "    aleatoare, iar delete[] din destructor ar strica programul.\n"
                 "  - daca count_ nu ar porni de la 0, media ar fi calculata\n"
                 "    din valori aleatoare.\n";
    Student bogdan("Bogdan", 2, 4);
    bogdan.print();  // count_ = 0 -> nicio nota, media 0
}

// ---------------------------------------------------------------
// 3. Destructorul elibereaza heap-ul
// ---------------------------------------------------------------
void demoDestructor()
{
    title("3. DESTRUCTOR: ELIBERAREA HEAP-ULUI");

    std::cout << "a) Clasa CU destructor (Student):\n";
    showHeap();
    for (int i = 0; i < 3; ++i) {
        Student temp("Temporar", 100 + i, 5);
    }  // destructorul ruleaza la fiecare iteratie
    showHeap();
    std::cout << "  Toata memoria a fost eliberata.\n";

    std::cout << "\nb) Clasa FARA destructor (LeakyStudent):\n";
    for (int i = 0; i < 3; ++i) {
        LeakyStudent leaky(5);
    }  // obiectul dispare, dar notele raman pe heap
    std::cout << "  -> blocuri LeakyStudent ramase pe heap: "
              << LeakyStudent::liveAllocations() << "\n"
              << "  MEMORY LEAK: obiectele nu mai exista, dar memoria lor\n"
                 "  nu mai poate fi eliberata (am pierdut adresele).\n";

    std::cout << "\nc) Obiect creat cu new: destructorul ruleaza la delete.\n";
    Student* p = new Student("Pe heap", 3, 2);
    showHeap();
    delete p;  // apeleaza ~Student(), apoi elibereaza obiectul
    showHeap();
}

// ---------------------------------------------------------------
// 4. Copy constructor
// ---------------------------------------------------------------
void demoCopy(bool runDoubleDelete)
{
    title("4. COPY CONSTRUCTOR");

    std::cout << "a) FARA copy constructor propriu (ShallowStudent):\n";
    ShallowStudent* a = new ShallowStudent(3);
    a->setGrade(0, 9);
    ShallowStudent* b = new ShallowStudent(*a);  // copy ctor generat de compilator
    std::cout << "  (b = copie a lui a; niciun mesaj: copy ctor-ul e generat de compilator)\n"
              << "  a are notele la " << a->gradesAddress() << "\n"
              << "  b are notele la " << b->gradesAddress() << "  <- ACEEASI adresa!\n";
    b->setGrade(0, 4);  // modificam doar copia...
    std::cout << "  Dupa b.setGrade(0, 4): a.grade(0) = " << a->grade(0)
              << "  <- s-a schimbat si originalul!\n";

    delete a;  // elibereaza vectorul comun
    if (runDoubleDelete) {
        std::cout << "  Stergem si b -> acelasi vector este eliberat a doua oara:\n";
        delete b;  // DOUBLE DELETE: comportament nedefinit, de obicei crash
    } else {
        std::cout << "  Dupa delete a, b pointeaza spre memorie eliberata (dangling).\n"
                     "  delete b ar elibera acelasi vector a doua oara: DOUBLE DELETE.\n"
                     "  Ruleaza ./catalog --double-delete ca sa vezi crash-ul.\n";
        // Lasam b intentionat nesters, ca programul sa poata continua.
    }

    std::cout << "\nb) CU copy constructor propriu (Student):\n";
    Student original("Carmen", 4, 3);
    original.addGrade(10);
    original.addGrade(9);
    showHeap();
    Student copy = original;  // apeleaza Student(const Student&)
    showHeap();
    std::cout << "  Modificam doar copia:\n";
    copy.addGrade(5);
    original.print();
    copy.print();
    std::cout << "  Fiecare obiect are propriul vector, deci fiecare destructor\n"
                 "  elibereaza memoria lui o singura data.\n";

    std::cout << "\nc) Copy constructor apelat la transmiterea prin valoare:\n";
    auto byValue = [](Student s) { std::cout << "  in functie: "; s.print(); };
    byValue(original);
}

// ---------------------------------------------------------------
// 5. Move constructor
// ---------------------------------------------------------------
void demoMove()
{
    title("5. MOVE CONSTRUCTOR");

    std::cout << "a) Copiere vs mutare:\n";
    Student source("Dan", 5, 1000);  // un vector mare de note
    source.addGrade(7);
    showHeap();

    std::cout << "  Copiere -> se aloca un vector NOU de 1000 de note:\n";
    Student copied = source;
    showHeap();

    std::cout << "  Mutare cu std::move -> nu se aloca nimic:\n";
    Student moved = std::move(source);
    showHeap();
    std::cout << "  source dupa mutare: ";
    source.print();
    std::cout << "  moved:  ";
    moved.print();

    std::cout << "\nb) std::vector muta elementele cand isi mareste capacitatea\n"
                 "   (doar pentru ca move constructor-ul este noexcept):\n";
    std::vector<Student> group;
    group.push_back(Student("Elena", 6, 3));  // temporar -> move
    group.push_back(Student("Florin", 7, 3)); // realocare -> Elena e mutata
    showHeap();
    for (const Student& s : group) {
        s.print();
    }
    std::cout << "  Fara move constructor, fiecare pas de mai sus ar fi facut o\n"
                 "  copie adanca (alocare + copiere), apoi ar fi distrus originalul.\n";
}

}  // namespace

int main(int argc, char* argv[])
{
    bool runDoubleDelete = argc > 1 && std::strcmp(argv[1], "--double-delete") == 0;

    demoEncapsulation();
    demoInitialization();
    demoDestructor();
    demoCopy(runDoubleDelete);
    demoMove();

    title("SFARSIT");
    showHeap();
    std::cout << "  Toate obiectele Student au fost distruse, heap-ul este curat.\n";
    return 0;
}
