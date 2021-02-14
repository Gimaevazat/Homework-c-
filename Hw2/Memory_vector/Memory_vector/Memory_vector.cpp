#include <iostream>
#include <vector>

int main()
{
    std::vector <int> a;
    const int sz = 200;

    for (int i = 0; i < sz ; i++) {

        a.push_back(1);
    }

    int cap = a.capacity();

    for (int i = 0; cap == a.capacity() ; i++) {

        a.push_back(1);
    }
    std::cout << cap << " " << a.capacity() << " " << float (a.capacity()) / float(cap) << std::endl; 
    // a.capacity()  = 316, cap = 211, отношение примерно 1,5

    a.reserve(1200);
    std::cout << a.capacity() << std::endl; // размер стал 1200

    // сделаю размер 10
    a.reserve(10);
    std::cout << a.capacity() << std::endl; //ВАУУУ, размер остался прежним

    //определим максимальный размер массива с int

    std::cout << a.max_size() << std::endl; // для моего компьютера это 1073741823 штук типа int

    a.clear();
    a.shrink_to_fit();
    
    for (int i = 107374182; 1 == 1; i + 1073741823) {

        try
        {
            a.clear();
            a.shrink_to_fit();
            a.reserve(i);
        }
        catch (std::bad_alloc& ba)
        {
            std::cout << std::endl << "bad_alloc" << std::endl << "max size = " << i << std::endl;
            break;
        }
    }
    // а тут максимальный размер оказался --- (что-то тут не получается выйти)
    return 0;
}


