
#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>


class Timer {

public:
    using clock_t = std::chrono::steady_clock;
    using time_point_t = clock_t::time_point;
    Timer(): m_begin(clock_t::now()) {}
    ~Timer()
    {
        auto end = clock_t::now();
        start();
        std::cout << "milliseconds" << std::chrono::duration_cast <
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
    private:
    time_point_t m_begin;
    time_point_t start_time;
    time_point_t stop_time;
    bool flag = false;
};



int main()
{
    std::vector <int> a;
    for (int i = 0; i < 1000000; i++) {
        a.push_back(1000000 - i);
    }
    Timer r, t;
    std::sort(a.begin(), a.end());
    r.stop();
    t.stop();
    for (int i = 0; i < 1000000; i++) {
        a[i] = 1000000 - i;
    }
    r.start();
    Timer s;
    std::sort(a.begin(), a.end());
}


