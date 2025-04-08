#include <iostream>
#include <cstring>
#include <cassert>
#include <functional>

class Question
{
public:
    Question(
        const char* question = "",
        const char* answer = ""
    )
    {
        std::size_t questionLen = std::strlen(question),
                    answerLen = std::strlen(answer);

        assert(questionLen <= 100 && answerLen <= 20);

        std::strcpy(this->question, question);
        std::strcpy(this->answer, answer);
    }

    const char* getQuestion() const
    {
        return this->question;
    }
    const char* getAnswer() const
    {
        return this->answer;
    }

    friend std::ostream& operator << (std::ostream& out, const Question& question)
    {
        out << question.question << " " << question.answer;

        return out;
    }

private:
    char question[101];
    char answer[21];
};

class Test 
{
public:
    Test(std::size_t N)
        : capacity(N), size(0), testQuestions(new TestQuestion[N]) {}
    Test(const Test& other)
    {
        this->copy(other);
    }
    Test& operator = (const Test& other)
    {
        if (this != &other)
        {
            this->deallocate();
            this->copy(other);
        }

        return *this;
    }
    ~Test()
    {
        this->deallocate();
    }

    Test& addQuestion(const Question& q, unsigned int k)
    {
        std::size_t idx = this->findQuestion(q.getQuestion());
        
        if (idx == this->size && this->size < this->capacity)
        {
            this->testQuestions[this->size].setData(q, k);
            ++this->size;
        }

        // if we are here we know that idx == this->size
        // and this->size == this->capacity
        // so there is no place in the test
        // and we do nothing

        return *this;
    }

    unsigned int maxResponses() const
    {
        unsigned int count = 0;

        for (std::size_t i = 0; i < this->size; ++i)
            count += this->testQuestions[i].nAskings;
        
        return count;
    }

    void serialize(std::ostream& out) const
    {
        out << "This test has " << this->size << " out of " << this->capacity << " possible number of questions\n";
        for (std::size_t i = 0; i < this->size; ++i)    
            out << "Question: " << this->testQuestions[i].question
                << ", could be asked " << this->testQuestions[i].nAskings << " times\n";
    }

    void perform(std::function<bool(const Question&)> pred = [](const Question&) { return true; }) const
    {
        std::cout << "Let's run this test ;)\n";

        unsigned int askedQuestions = 0, rightQuestions = 0;

        for (std::size_t i = 0; i < this->size; ++i)
            if (pred(this->testQuestions[i].question))
            {
                ++askedQuestions;
                if (rightAnswered(i))
                    ++rightQuestions;
            }
        
        if (askedQuestions)
            std::cout << "\nYou answered "
                      << 100.0 * rightQuestions / askedQuestions
                      << "% of the questions! \n";
        else
            std::cout << "\nNo question passes the predicate :'( \n";
    }

    Test merge(const Test& other) const
    {
        Test result(this->capacity + other.capacity);

        for (std::size_t i = 0; i < this->size; ++i)
            result.addQuestion(this->testQuestions[i].question, this->testQuestions[i].nAskings);
        
        for (std::size_t i = 0; i < other.size; ++i)
        {
            const char* question = other.testQuestions[i].question.getQuestion();
            unsigned int nAskingsOther = other.testQuestions[i].nAskings;
    
            std::size_t idx = result.findQuestion(question);
    
            if (idx == result.size)
                result.addQuestion(other.testQuestions[i].question, nAskingsOther);
            else if (nAskingsOther > result.testQuestions[idx].nAskings)
                result.testQuestions[idx].nAskings = nAskingsOther;
        }
        return result;
    }

private:
    void deallocate()
    {
        delete[] this->testQuestions;
    }
    void copy(const Test& other)
    {
        this->capacity = other.capacity;
        this->size = other.size;

        this->testQuestions = new TestQuestion[this->capacity];
        for (std::size_t i = 0; i < this->size; ++i)
            this->testQuestions[i].setData(other.testQuestions[i].question, other.testQuestions[i].nAskings);
    }

    std::size_t findQuestion(const char* question) const
    {
        for (std::size_t i = 0; i < this->size; ++i)
            if (std::strcmp(this->testQuestions[i].question.getQuestion(), question) == 0)
                return i;

        return this->size;
    }

    bool rightAnswered(std::size_t idx) const
    {
        char currentAnswer[32];

        unsigned int nAskings = this->testQuestions[idx].nAskings;
        const char *answer = this->testQuestions[idx].question.getAnswer(),
                   *question = this->testQuestions[idx].question.getQuestion();

        for (std::size_t i = 0; i < nAskings; ++i)
        {
            std::cout << question << ' ';
            std::cin.getline(currentAnswer, 32);

            if (std::strcmp(currentAnswer, answer) == 0)
                return true;
        }

        return false;
    }

private:
    struct TestQuestion {
        Question question;
        unsigned int nAskings;
        void setData(const Question& q, unsigned int n)
        {
            this->question = q;
            this->nAskings = n;
        }
    };
private:
    std::size_t size, capacity;
    TestQuestion* testQuestions;
};

int main()
{
    Test up(10), oop(15);

    up.addQuestion({"char or double","double"},1)
      .addQuestion({"For or while","no"}, 1);

    oop.addQuestion({"struct or class","neither"}, 2)
       .addQuestion({"added()?","functor"}, 3);
    
    up.merge(oop).perform();
 
    return 0;
}