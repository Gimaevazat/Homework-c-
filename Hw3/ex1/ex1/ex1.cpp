#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <set>


class Timer {

public:
    using clock_t = std::chrono::steady_clock;
    using time_point_t = clock_t::time_point;
    Timer() : m_begin(clock_t::now()) {}
    ~Timer()
    {
        /*auto end = clock_t::now();
        start();
        std::cout << "milliseconds: " << std::chrono::duration_cast <
            std::chrono::milliseconds> (end - m_begin).count() << std::endl;*/
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
    std::set<int> Set;
    std::vector <int> Vector;
    Timer t_set, t_vector;

    for (int i = 0; i < 1000000; i++) 
    {
        int a;
        if (i == 0) t_set.reset();
        t_set.start();
        a = rand();
        Set.insert(a);
        t_set.stop();

        if (i == 0) t_vector.reset();
        t_vector.start();
        Vector.push_back(a);
        t_vector.stop();
    }

    t_vector.start();
    std::sort(Vector.begin(), Vector.end());
    t_vector.stop();

    std::cout << "time set: ";
    t_set.show();
    std::cout << "time vector: ";
    t_vector.show();
    //t_vector < t_set
   
}

