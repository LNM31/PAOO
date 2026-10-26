#ifndef CATALOG_BAD_EXAMPLES_HPP
#define CATALOG_BAD_EXAMPLES_HPP

// Clase scrise GRESIT intentionat, ca sa se vada ce se intampla
// cand lipseste destructorul sau copy constructor-ul.

namespace catalog {

// Aloca note pe heap, dar NU are destructor -> memory leak.
class LeakyStudent {
    public:
        explicit LeakyStudent(int capacity);
        static int liveAllocations();

    private:
        int* grades_;
        static int liveAllocations_;
};

// Are destructor, dar NU are copy constructor propriu. Compilatorul
// genereaza unul care copiaza doar adresa (copie superficiala).
class ShallowStudent {
    public:
        explicit ShallowStudent(int capacity);
        ~ShallowStudent();

        void setGrade(int index, int grade);
        int grade(int index) const;
        const int* gradesAddress() const;

    private:
        int* grades_;
        int capacity_;
};

}  // namespace catalog

#endif
