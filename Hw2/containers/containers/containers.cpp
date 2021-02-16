#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <list>
#include <forward_list>
#include <array>


class Timer {

public:
    using clock_t = std::chrono::steady_clock;
    using time_point_t = clock_t::time_point;
    Timer() : m_begin(clock_t::now()) {}
    ~Timer()
    {
        auto end = clock_t::now();
        start();
        std::cout << "milliseconds: " << std::chrono::duration_cast <
            std::chrono::milliseconds> (end - m_begin).count() << std::endl;
    }
    void stop()
    {
        stop_time = clock_t::now();
        flag = true;
    }
    void start()
    {
        if (flag) {
            start_time = clock_t::now();
            m_begin += start_time - stop_time;
            flag = false;
        }
    }
    void show()
    {
        auto end = clock_t::now();
        start();
        std::cout << "milliseconds: " << std::chrono::duration_cast <
            std::chrono::milliseconds> (end - m_begin).count() << std::endl;
    }
    void reset() 
    {
        m_begin = clock_t::now();
    }
private:
    time_point_t m_begin;
    time_point_t start_time;
    time_point_t stop_time;
    bool flag = false;
};

int main()
{
    const int sz = 10000;
    //sort vector

    std::vector <int> a;
    for (int i = 0; i < sz; i++) {
        a.push_back(sz - i);
    }

    Timer *timer = new Timer;
    sort(a.begin(), a.end());
    timer->stop();

    std::cout << "Vector sorted by sort()" << std::endl;
    timer->~Timer();
    a.clear();
    std::cout << std::endl;
    
    //sort list by list.sort()

    std::list <int> b;
    for (int i = 0; i < sz; i++) {
        b.push_front(i);
    }

    timer->reset();
    b.sort();
    timer->stop();

    std::cout << "List sorted by sort()" << std::endl;
    timer->~Timer();
    b.clear();
    std::cout << std::endl;
    
    //sort forwars_list by sort()

    std::forward_list <int> c = { 1 };
    for (int i = 0; i < sz; i++) {
        c.push_front(i);
    }

    timer->reset();
    c.sort();
    timer->stop();

    std::cout << "Forward_ist sorted by sort()" << std::endl;
    timer->~Timer();
    c.clear();
    std::cout << std::endl;

    //sort std::array by sort()
    /*
    std::array <int, 1000> d;
    for (int i = 0; i < 1000; i++) {
        d.at(i) = 1000 - i;
    }

    timer->reset();
    std::sort(d.begin(), d.end());
    timer->stop();

    std::cout << "std::array sorted by sort()" << std::endl;
    timer->~Timer();
    std::cout << std::endl;*/

    return 0;
}


