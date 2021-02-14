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
    // a.capacity()  = 316, cap = 211, ��������� �������� 1,5

    a.reserve(1200);
    std::cout << a.capacity() << std::endl; // ������ ���� 1200

    // ������ ������ 10
    a.reserve(10);
    std::cout << a.capacity() << std::endl; //�����, ������ ������� �������

    //��������� ������������ ������ ������� � int

    std::cout << a.max_size() << std::endl; // ��� ����� ���������� ��� 1073741823 ���� ���� int

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
    // � ��� ������������ ������ �������� --- (���-�� ��� �� ���������� �����)
    return 0;
}


