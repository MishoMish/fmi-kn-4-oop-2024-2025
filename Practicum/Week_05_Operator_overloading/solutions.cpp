#include <iostream>
#include <cstring>

class Note
{
    public:
    Note(
        const char description[] = "",
        unsigned short int date = 1,
        unsigned short int month = 1,
        unsigned short int year = 2000
    ) : deadline{date, month, year} {
        std::strncpy(this->description, description, sizeof(this->description) - 1);
        this->description[sizeof(this->description) - 1] = '\0';
        
        // bonus: Adding data validation
    }
    
    friend std::ostream& operator << (std::ostream& out, const Note& note)
    {
        out << note.description << '\n' << note.deadline; 
        
        return out;
    } 

    private:
    struct Date {
        unsigned short int date, month, year;

        friend std::ostream& operator << (std::ostream& out, const Date& date)
        {
            out << date.date << '-' << date.month << '-' << date.year;

            return out;
        } 
    };

private:
public:
    char description[101];
    Date deadline;

};

class ToDoList
{
public:
// big 4
    ToDoList()
        : capacity(16), size(0) {
        this->notes = new Note[this->capacity];
    }
    ToDoList(const ToDoList& other)
    {
        this->copy(other);
    }
    ToDoList& operator = (const ToDoList& other)
    {
        if (this != &other)
        {
            this->deallocate();
            this->copy(other);
        }

        return *this;
    }
    ~ToDoList()
    {
        this->deallocate();
    }

// add Note
    void addNote(const Note& note)
    {
        if (this->size == this->capacity)
            this->resize();
        
        this->notes[this->size] = note;
        ++this->size;
    }
// addition operators
    ToDoList& operator += (const ToDoList& other)
    {
        for (std::size_t i = 0; i < other.size; ++i)
            this->addNote(other.notes[i]);
        
        return *this;
    }

    ToDoList operator + (const ToDoList& other) const
    {
        ToDoList result = *this;
        result += other;

        return result;
    }
// comparison operators
    bool operator < (const ToDoList& other) const
    {
        return this->size < other.size;
    }
    bool operator == (const ToDoList& other) const
    {
        return !(*this < other) && !(other < *this);
    }

// remove by id
    bool removeById(const std::size_t idx)
    {
        if (idx >= this->size)
            return false;
        
        for (std::size_t i = idx + 1; i < this->size; ++i)
            this->notes[i - 1] = this->notes[i];
        --this->size;

        return true;
    }
// printing
    friend std::ostream& operator << (std::ostream& out, const ToDoList& toDoList)
    {
        out << "This To-Do List contains " << toDoList.size << " notes and here there are:\n";
        for (std::size_t i = 0; i < toDoList.size; ++i)
        {
            out << i << ' ' << toDoList.notes[i] << '\n';
        }

        return out;
    }

private:
    void copy(const ToDoList& other)
    {
        this->capacity = other.capacity;
        this->size = other.size;

        this->notes = new Note[this->capacity];
        for (std::size_t i = 0; i < this->size; ++i)
            this->notes[i] = other.notes[i];
    }
    void deallocate()
    {
        delete[] this->notes;
        this->size = this->capacity = 0;
    }
    void resize()
    {
        this->capacity *= 2;
        
        Note* resizedNotes = new Note[this->capacity];
        for (std::size_t i = 0; i < this->size; ++i)
            resizedNotes[i] = this->notes[i];
        
        delete[] this->notes;
        this->notes = resizedNotes;
    }

private:
    Note* notes;
    std::size_t size, capacity;
};



int main()
{
    ToDoList tdl;

    Note n1("Hello", 2, 4, 2001);

    for (int i = 0; i < 32; ++i)
        tdl.addNote(n1);

    std::cout << tdl << "\n\n\n";

    tdl.removeById(30);

    std::cout << tdl;
    return 0;
}