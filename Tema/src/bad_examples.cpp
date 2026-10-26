#include <catalog/bad_examples.hpp>

#include <iostream>

namespace catalog {

// ---------- LeakyStudent: fara destructor ----------

int LeakyStudent::liveAllocations_ = 0;

LeakyStudent::LeakyStudent(int capacity)
    : grades_(new int[capacity]())
{
    ++liveAllocations_;
    std::cout << "  [LeakyStudent constructor] note la " << grades_ << "\n";
}

int LeakyStudent::liveAllocations() { return liveAllocations_; }

// ---------- ShallowStudent: fara copy constructor ----------

ShallowStudent::ShallowStudent(int capacity)
    : grades_(new int[capacity]()),
      capacity_(capacity)
{
    std::cout << "  [ShallowStudent constructor] note la " << grades_ << "\n";
}

ShallowStudent::~ShallowStudent()
{
    std::cout << "  [ShallowStudent destructor] delete[] " << grades_ << "\n";
    delete[] grades_;
}

void ShallowStudent::setGrade(int index, int grade)
{
    if (index >= 0 && index < capacity_) {
        grades_[index] = grade;
    }
}

int ShallowStudent::grade(int index) const
{
    return (index >= 0 && index < capacity_) ? grades_[index] : 0;
}

const int* ShallowStudent::gradesAddress() const { return grades_; }

// ---------- Initializare fara lista de initializare ----------
// Se compileaza doar cu:  cmake .. -DDEMO_INIT_ERROR=ON
// Un membru const (sau o referinta) nu poate fi "atribuit" in corpul
// constructorului; la intrarea in corp el exista deja. Compilatorul da eroare.
#ifdef DEMO_INIT_ERROR
class BadInitStudent {
public:
    explicit BadInitStudent(int id)
    {
        id_ = id;  // eroare: assignment of read-only member 'id_'
    }

private:
    const int id_;
};
#endif

}  // namespace catalog
