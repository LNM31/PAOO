#include <catalog/student.hpp>

#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>

namespace catalog {

int Student::liveAllocations_ = 0;

// Toti membrii sunt initializati in lista de initializare, in ordinea
// in care sunt declarati in clasa. id_ este const, deci nici nu s-ar
// putea seta altfel.
Student::Student(const char* name, int id, int capacity)
    : id_(id),
      name_(new char[std::strlen(name) + 1]),
      grades_(new int[capacity]),
      capacity_(capacity),
      count_(0)
{
    std::strcpy(name_, name);
    liveAllocations_ += 2;
    std::cout << "  [Constructor]      " << name_ << " (id " << id_
              << "), note la adresa " << grades_ << "\n";
}

// Copie adanca: copia primeste propriile zone de memorie, cu aceleasi valori.
// Daca sursa a fost mutata (pointeri nullptr), copia ramane si ea goala.
Student::Student(const Student& other)
    : id_(other.id_),
      name_(nullptr),
      grades_(nullptr),
      capacity_(other.capacity_),
      count_(other.count_)
{
    if (other.name_) {
        name_ = new char[std::strlen(other.name_) + 1];
        std::strcpy(name_, other.name_);
        ++liveAllocations_;
    }
    if (other.grades_) {
        grades_ = new int[capacity_];
        std::copy(other.grades_, other.grades_ + count_, grades_);
        ++liveAllocations_;
    }
    std::cout << "  [Copy constructor] " << (name_ ? name_ : "(gol)")
              << ": note NOI la " << grades_
              << " (originalul ramane la " << other.grades_ << ")\n";
}

// Mutare: nu se aloca nimic. Destinatia preia pointerii, iar sursa
// ramane cu nullptr, ca destructorul ei sa nu mai elibereze nimic.
Student::Student(Student&& other) noexcept
    : id_(other.id_),
      name_(other.name_),
      grades_(other.grades_),
      capacity_(other.capacity_),
      count_(other.count_)
{
    other.name_ = nullptr;
    other.grades_ = nullptr;
    other.capacity_ = 0;
    other.count_ = 0;
    std::cout << "  [Move constructor] " << (name_ ? name_ : "(gol)")
              << ": preia notele de la " << grades_ << ", fara alocare noua\n";
}

Student::~Student()
{
    std::cout << "  [Destructor]       "
              << (name_ ? name_ : "(obiect mutat, nu are ce elibera)") << "\n";
    if (name_) {
        delete[] name_;
        --liveAllocations_;
    }
    if (grades_) {
        delete[] grades_;
        --liveAllocations_;
    }
}

bool Student::addGrade(int grade)
{
    if (!grades_ || grade < 1 || grade > 10 || count_ == capacity_) {
        std::cout << "  Nota " << grade << " respinsa pentru "
                  << (name_ ? name_ : "(gol)") << "\n";
        return false;
    }
    grades_[count_++] = grade;
    return true;
}

double Student::average() const
{
    if (count_ == 0) {
        return 0.0;
    }
    int sum = 0;
    for (int i = 0; i < count_; ++i) {
        sum += grades_[i];
    }
    return static_cast<double>(sum) / count_;
}

void Student::print() const
{
    if (!name_) {
        std::cout << "  Student gol (resursele au fost mutate)\n";
        return;
    }
    std::cout << "  " << name_ << " (id " << id_ << "): note [";
    for (int i = 0; i < count_; ++i) {
        std::cout << grades_[i] << (i + 1 < count_ ? " " : "");
    }
    std::cout << "], media " << std::fixed << std::setprecision(2) << average()
              << ", note la " << grades_ << "\n";
}

int Student::id() const { return id_; }
const char* Student::name() const { return name_; }
int Student::gradeCount() const { return count_; }
const int* Student::gradesAddress() const { return grades_; }
int Student::liveAllocations() { return liveAllocations_; }

}  // namespace catalog
