#include <fstream>
#include <random>
#include <iostream>
#include <iomanip>
#include <string>

int main()
{
    //------------------fill input with text
    std::ofstream out("D:\\Homework-c-\\Hw6\\ex2\\input.txt");
    for (int i = 0; i < 25; i++) {
        char ch = 'a' + rand() % 26;
        out << "Line" << std::setfill('0') << std::setw(2) << i+1  << " " << ch << std::endl;
    }
    out.close();
    //---------------open input
    std::ifstream in("D:\\Homework-c-\\Hw6\\ex2\\input.txt");
    std::string line;
    //-----------determine how long one line take
    std::getline(in, line);

    int len = in.tellg();
    //--------------cout line with number N;
    std::cout << "Line with which number do you want to cout?" << std::endl;

    int N;
    std::cin >> N;

    in.seekg(len*(N-1), std::ios::beg);

    std::getline(in, line);

    std::cout << line;


    return 0;
}

