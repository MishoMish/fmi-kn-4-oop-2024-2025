#include <iostream>

class Plazza {
private:
    int visitorCounter;

public:
    Plazza(int initial=0)
    {
        this->visitorCounter = initial;
    }

    int getVisitorsCount() const
    {
        return this->visitorCounter;
    }

    void increaseVisitorsCount(int entering)
    {
        this->visitorCounter += entering;
    }
    void decreaseVisitorsCount(int leaving)
    {
        this->visitorCounter -= leaving;
    }
};

int main()
{
    Plazza p;
    int count;
    bool flag = true;
    while (flag) 
    {
        std::cin >> count;

        if (count > 0)
        {
            p.increaseVisitorsCount(count);
        }
        else if (count < 0)
        {
            p.decreaseVisitorsCount(-count);
        }
        else
        {
            int currentVisitors = p.getVisitorsCount();
            std::cout << currentVisitors << std::endl;

            if (currentVisitors > 10)
                flag = false;
        }
    }
}