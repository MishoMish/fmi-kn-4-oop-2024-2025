#include <iostream>
#include <cstring>

class A {
public: 
    A(int x) : x(x) {
        std::cout << "A constructor\n";
    }
    ~A() {
        std::cout << "A destructor\n";
    }
    void printInfo() const
    {
        std::cout << x << std::endl;
    }
    int getX() const
    {
        return this->x;
    }
private:
    int x;
};

class B : public A {
public:
    B(int x) : A(x) {
        std::cout << "B constructor\n";
        this->A::printInfo();      
    }
    ~B() {
        std::cout << "B destructor\n";
    }
    void printInfo() const
    {
        std::cout << this->getX() * this->getX() << std::endl;
    }
private:
    
};
// Shape - area, perimeter
// Circle Rectangle Square 


class Employee {
private:
    char *name, *email;
    unsigned experience;
    double salary;

public:
    Employee(const char* name, const char* email, unsigned experience, double salary)
        : name(new char[strlen(name) + 1]),
          email(new char[strlen(email) + 1]),
          experience(experience),
          salary(salary)
    {
        strcpy(this->name, name);
        strcpy(this->email, email);

        std::cout << "employee constuctor\n";
    }
    Employee(const Employee& other)
    {
        this->copy(other);
    }
    Employee& operator = (const Employee& other)
    {
        if (this != &other)
        {
            this->deallocate();
            this->copy(other);
        }

        return *this;
    }
    ~Employee()
    {
        std::cout << "employee destuctor\n";
        this->deallocate();
    }

    void printInfo() const
    {
        std::cout << "Basic Info :\n";
        std::cout << "Employee:     " << this->name
                  << "Email:        " << this->email
                  << "Experience:   " << this->experience
                  << "Basic Salary: " << this->salary << '\n';
    }
    double getSalary() const
    {
        return this->salary;
    }
    double getExperience() const
    {
        return this->experience;
    }
private:
    void copy(const Employee& other)
    {
        this->experience = other.experience;
        this->salary = other.salary;

        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        this->email = new char[strlen(other.email) + 1];
        strcpy(this->email, other.email);
    }
    void deallocate()
    {
        delete[] this->name;
        delete[] this->email;
    }
};

class Developer : public Employee
{
    enum ProgrammingLanguage {
        C_PLUS_PLUS,
        C_SHARP,
        PYTHON,
        JAVA
    };
    enum Project {
        A,
        B,
        C
    };
    ProgrammingLanguage* langs;
    std::size_t langCount;
    Project proj;

public:
    Developer(
        const char* name,
        const char* email,
        unsigned experience,
        double salary,
        const char* projectName,
        const char* languages[], std::size_t size
    ) : Employee(name, email, experience, salary),
        langs(new ProgrammingLanguage[size]),
        langCount(size)
    {
        this->proj = this->getProject(projectName);
        for (size_t i = 0; i < size; ++i)
            langs[i] = this->getLang(languages[i]);

            std::cout << "dev constructor\n";
    }
    Developer(const Developer& other)
        : Employee(other)
    {
        this->copy(other);
    }
    Developer& operator = (const Developer& other)
    {
        if (this != &other)
        {
            // in this way we explicitly call the operator = of the base class
            Employee::operator=(other);
            delete[] this->langs;
            this->copy(other);
        }

        return *this;
    }
    ~Developer()
    {
        std::cout << "dev destuctor\n";
        delete[] this->langs; 
    }

    void printInfo() const 
    {
        this->Employee::printInfo();
        std::cout << "The developer works with:\n";
        // print ProgrammingLanguages
        // print Project
    }
    double getSalary() const
    {
        return this->Employee::getSalary() * ((this->Employee::getExperience() + 1) / (this->Employee::getExperience() + 1));
    }

// (opit + 1 / opit)
private:
    void copy(const Developer& other)
    {
        this->langCount = other.langCount;
        this->langs = new ProgrammingLanguage[this->langCount];
        for (size_t i = 0; i < this->langCount; ++i)
            this->langs[i] = other.langs[i];

        this->proj = other.proj;
    }
    Project getProject(const char* project)
    {
        if (strcmp(project, "A") == 0) return A;
        if (strcmp(project, "B") == 0) return B;
        if (strcmp(project, "C") == 0) return C;

        return A;
    }
    ProgrammingLanguage getLang(const char* lang)
    {
        if (strcmp(lang, "C++") == 0) return C_PLUS_PLUS;
        if (strcmp(lang, "C#") == 0) return C_SHARP;
        if (strcmp(lang, "Python") == 0) return PYTHON;
        //if (strcmp(lang, "Java") == 0) return JAVA;

        return JAVA;
    }
};



int main()
{
    // B a(5);
    // a.printInfo();
    const char* langs[] = {"C++", "C#"};
    Developer dev("Ton4o", "ton4o@gmail.com", 5, 1000, "A", langs, 2);
    Developer dev2("Don4o", "ton4o@gmail.com", 5, 2000, "A", langs, 2);

    dev = dev2;

    dev.printInfo();

    std::cout << dev.getSalary() << std::endl;

    return 0;
}