#include <iostream>
#include <cstring>
#include <cassert>
#include <functional>

class Book
{
public:
    Book(
        const char* title = "",
        const char* author = "",
        unsigned long long int id = 0
    ) : id(id)
    {
        std::size_t titleLen = std::strlen(title),
                    authorLen = std::strlen(author);
        
        assert(titleLen <= 100 && authorLen <= 50);

        std::strcpy(this->title, title);
        std::strcpy(this->author, author);
    }
    const char* getTitle() const
    {
        return this->title;
    }
    const char* getAuthor() const
    {
        return this->author;
    }
    unsigned long long int getId() const
    {
        return this->id;
    }

    friend std::ostream& operator<<(std::ostream& out, const Book& book)
    {
        out << "ISBN: " << book.id
            << ", title: " << book.title
            << ", author: " << book.author;

        return out;
    }

private:
    char title[101];
    char author[51];
    unsigned long long int id;
};

class Library
{
public:
    Library(std::size_t N)
        : capacity(N), size(0), libBooks(new LibBook[N]) {}
    Library(const Library& other)
    {
        this->copy(other);
    }
    Library& operator = (const Library& other)
    {
        if (this != &other)
        {
            this->deallocate();
            this->copy(other);
        }

        return *this;
    }
    ~Library()
    {
        this->deallocate();
    }
    Library& addBook(const Book& b, unsigned int k)
    {
        std::size_t idx = this->findBookByISBN(b.getId());

        if (idx != this->size)
        {
            this->libBooks[idx].nCopies += k;
        }
        else if (this->size < this->capacity)
        {
            this->libBooks[this->size].setData(b, k);
            ++this->size;
        }

        // if we are here we know that idx == this->size
        // and this->size == this->capacity
        // so there is no place in the library

        return *this;
    }

    unsigned int countBooks() const
    {
        unsigned int count = 0;

        for (std::size_t i = 0; i < this->size; ++i)
            count += this->libBooks[i].nCopies;
        
        return count;
    }

    void serialize(std::ostream& out, std::function<bool(const Book&)> pred = [](const Book&) { return true; }) const
    {
        out << "This library has " << this->size << " out of " << this->capacity << " possible number of books\n";
        for (std::size_t i = 0; i < this->size; ++i)
            if (pred(this->libBooks[i].book))    
                out << this->libBooks[i].book << " in " << this->libBooks[i].nCopies << " copies\n";
    }

    Library merge(const Library& other) const
    {
        Library result(this->capacity + other.capacity);

        for (std::size_t i = 0; i < this->size; ++i)
            result.addBook(this->libBooks[i].book, this->libBooks[i].nCopies);
        
        for (std::size_t i = 0; i < other.size; ++i)
            result.addBook(other.libBooks[i].book, other.libBooks[i].nCopies);
        
        return result;
    }

private:
    void deallocate()
    {
        delete[] this->libBooks;
    }
    void copy(const Library& other)
    {
        this->capacity = other.capacity;
        this->size = other.size;

        this->libBooks = new LibBook[this->capacity];
        for (std::size_t i = 0; i < this->size; ++i)
            this->libBooks[i].setData(other.libBooks[i].book, other.libBooks[i].nCopies);
    }

    std::size_t findBookByISBN(unsigned long long int isbn) const
    {
        for (std::size_t i = 0; i < this->size; ++i)
            if (this->libBooks[i].book.getId() == isbn)
                return i;

        return this->size;
    }
private:
    struct LibBook {
        Book book;
        unsigned int nCopies;

        void setData(const Book& book, unsigned int nCopies)
        {
            this->book = book;
            this->nCopies = nCopies;
        }
    };
private:
    std::size_t capacity, size;
    LibBook* libBooks;
};

int main()
{
    Library fmi(100), home(20);

    fmi.addBook({"OOP with C++","Todorova",1111111111},10)
       .addBook({"Numerical Methods","Boyanov",2222222222},15);

    home.addBook({"JavaScript for beginners","Smartman",3333333333},1)
        .addBook({"Numerical methods for DE","B. Boyanov",2222222222},1);

    fmi.merge(home).serialize(std::cout); //ще изведе 3 различни книги


    return 0;
}
