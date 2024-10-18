//
// Created by tomin on 16.10.2024.
//

#ifndef S3_LABORATORY_WORK_2_COUNTER_H
#define S3_LABORATORY_WORK_2_COUNTER_H
using namespace std;
// Class representing a reference counter class
class Counter
{
private:
    unsigned int m_counter{};
public:
    // Constructor
    Counter() : m_counter(0){};

    Counter(const Counter&) = delete;
    Counter& operator=(const Counter&) = delete;

    // Destructor
    ~Counter() {}

    // count reset
    void reset()
    {
        m_counter = 0;
    }

    // getter
    unsigned int get() const {
        return m_counter;
    }


    // Overload post/pre increment
    void operator++()
    {
        m_counter++;
    }

    void operator++(int)
    {
        m_counter++;
    }

    // Overload post/pre decrement
    void operator--()
    {
        m_counter--;
    }
    void operator--(int)
    {
        m_counter--;
    }

    // Overloading << operator
    friend ostream& operator<<(ostream& os,
                               const Counter& counter)
    {
        os << "Counter Value : " << counter.m_counter
           << endl;
        return os;
    }
};

#endif //S3_LABORATORY_WORK_2_COUNTER_H
