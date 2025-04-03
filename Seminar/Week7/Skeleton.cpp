#include <iostream>
#include <string>

class Student
{
    // TODO: Implement student details
};

class Instructor
{
    // TODO: Implement instructor details
};

class Room
{
    // TODO: Implement room details
};

class Time
{
    // TODO: Implement time details
};

class Session
{
private:
    std::string name;
    Student *attendees[30];
    int attendeeCount;
    Instructor *instructor;
    Room *location;
    Time duration;

public:
    Session();
    ~Session();
    bool operator==(const Session &other) const;
    void addAttendee(Student *student);
    void removeAttendee(Student *student);
};

class SessionIterator
{
private:
    Session *sessions[50];
    int current;
    int total;

public:
    SessionIterator();
    void next();
    bool isEnd();
    void notify();
};

template <typename T>
bool load(std::string filename);

int main()
{
    // TODO: Implement test cases and functionality
    return 0;
}
