#include <string>
#include <iostream>
#include <regex>
#include <fstream>
#include <cstring>
#include <cassert>
#include <vector>
#include <iterator>

const std::regex r(R"((([0][1-9])|([1-2][0-9])|([3][0-1]))\.(([0][1-9])|([1][0-2])|([1-9]))\.\d{4})");

int main()
{
    std::locale("ru-ru.UTF-8");

    std::ofstream out("D:\\Homework-c-\\Hw5\\ex4\\output.txt");
    std::ifstream in("D:\\Homework-c-\\Hw5\\ex4\\input.txt");

    while (in)
    {
        std::string line;

        std::getline(in, line);

        const std::vector<std::string> f{std::sregex_token_iterator{line.begin(), line.end(), r, 0},
        std::sregex_token_iterator{} };

        for (auto it = f.begin(); it != f.end(); ++it) {
            out << *it << std::endl;
        }
    }

    in.close();
    out.close();
    return 0;
}
