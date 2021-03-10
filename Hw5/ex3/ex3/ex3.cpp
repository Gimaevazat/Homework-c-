
#include <string>
#include <iostream>
#include <regex>
#include <fstream>
#include <cstring>
#include <cassert>
#include <string_view>


bool is_valid_email_id(std::string str) {
    static const std::regex r(R"(\w+\.?\w*@\w+\.([[:alpha:]]+))");
    return regex_match(str.data(), r);
}

std::string trim(std::string text) {
    static const auto r = std::regex(R"(^(\w+\.?\w*))");
    return regex_replace(text.data(), r, "");
}

int main()
{
    std::ofstream out("D:\\Homework-c-\\Hw5\\ex3\\output.txt");
    std::ifstream in("D:\\Homework-c-\\Hw5\\ex3\\input.txt");

    while (in) 
    {
        std::string line;

        std::getline(in, line);

        std::cout << line << std::endl;

        if (is_valid_email_id(line)) {
            out << line << std::endl;
            out << "Valid name | " << trim (line) << std::endl << "------------------------" << std::endl;
        }
        else{
            out << line << std::endl << "Don't valid name" << std::endl 
                << "------------------------" << std::endl;
        }
    }

    in.close();
    out.close();
    return 0;
}

