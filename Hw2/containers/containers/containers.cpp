#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <list>
#include <forward_list>
#include <array>
#include <deque>


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
    const int sz = 100000;
    //sort vector

    std::vector <int> a;
    for (int i = 0; i < sz; i++) {
        a.push_back(sz - i);
    }

    Timer *timer_vector = new Timer;
    sort(a.begin(), a.end());
    timer_vector->stop();

    std::cout << "std::vector sorted by sort()" << std::endl;
    timer_vector->~Timer();
    a.clear();
    std::cout << std::endl;
    
    //sort list by list.sort()

    std::list <int> b;
    for (int i = 0; i < sz; i++) {
        b.push_front(i);
    }

    Timer* timer_list = new Timer;
    b.sort();
    timer_list->stop();

    std::cout << "std::list sorted by sort()" << std::endl;
    timer_list->~Timer();
    b.clear();
    std::cout << std::endl;
    
    //sort forwars_list by sort()

    std::forward_list <int> c = { 1 };
    for (int i = 0; i < sz; i++) {
        c.push_front(i);
    }

    Timer* timer_forward_list = new Timer;
    c.sort();
    timer_forward_list->stop();

    std::cout << "std::forward_ist sorted by sort()" << std::endl;
    timer_forward_list->~Timer();
    c.clear();
    std::cout << std::endl;

    //sort std::array by sort()

    std::array <int, sz> d;
    for (int i = 0; i < sz; i++) {
        d[i] = sz - i;
    }

    Timer* timer_array = new Timer;
    std::sort(d.begin(), d.end());
    timer_array->stop();

    std::cout << "std::array sorted by sort()" << std::endl;
    timer_array->~Timer();
    std::cout << std::endl;

    //sort std::deque by sort()

    std::deque <int> e;
    for (int i = 0; i < sz; i++) {
        e.push_front(i);
    }

    Timer* timer_deque = new Timer;
    std::sort(e.begin(), e.end());
    timer_deque->stop();

    std::cout << "std::deque sorted by sort()" << std::endl;
    timer_deque->~Timer();
    e.clear();
    std::cout << std::endl;


    return 0;
}


