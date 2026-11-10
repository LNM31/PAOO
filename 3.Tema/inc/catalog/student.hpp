#ifndef CATALOG_STUDENT_HPP
#define CATALOG_STUDENT_HPP

namespace catalog {

// Student detine doua zone de memorie pe heap: numele si vectorul de note.
// Toate datele sunt private (incapsulare): din exterior se lucreaza doar
// prin metodele publice, care verifica datele (ex: nota intre 1 si 10).
class Student {
public:
    Student(const char* name, int id, int capacity);
    Student(const Student& other);        // copy constructor: copie adanca
    Student(Student&& other) noexcept;    // move constructor: preia resursele
    ~Student();                           // elibereaza heap-ul

    // Atribuirea nu face parte din tema (vine la un laborator viitor).
    // O interzicem explicit, ca sa nu se genereze o copie superficiala.
    Student& operator=(const Student&) = delete;
    Student& operator=(Student&&) = delete;

    bool addGrade(int grade);
    double average() const;
    void print() const;

    int id() const;
    const char* name() const;
    int gradeCount() const;
    const int* gradesAddress() const;  // doar pentru demonstratii

    // Cate blocuri de pe heap detin in acest moment toate obiectele Student.
    static int liveAllocations();

private:
    const int id_;     // const: poate fi setat DOAR in lista de initializare
    char* name_;
    int* grades_;
    int capacity_;
    int count_;

    static int liveAllocations_;
};

}  // namespace catalog

#endif
