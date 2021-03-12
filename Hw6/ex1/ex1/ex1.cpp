#include <string>
#include <iostream>
#include <fstream>

int main()
{
    std::ifstream in("D:\\Homework-c-\\Hw6\\ex1\\input.txt");
    std::ifstream test("D:\\Homework-c-\\Hw6\\ex1\\test.txt");
    std::ofstream out("D:\\Homework-c-\\Hw6\\ex1\\test_without_comments.txt");

    bool no_comment = false;
    bool one_line_comment = false;
    bool multiline_comment = false;
    bool open_close_string = false;

    while (in) {
        std::string line;
        std::string input_line;

        std::getline(test, line);

        for (int i = 0; i < line.length(); i++) {
            if (line[i] == '/' && line[i + 1] == '/' && open_close_string == false) {
                break;
            }
            if (line[i] == '/' && line[i + 1] == '*') {
                multiline_comment = true;
                continue;
            }
            if (line[i] == '*' && line[i + 1] == '/') {
                multiline_comment = false;
                i++;
                continue;
            }
            if (!multiline_comment) {
                input_line += line[i];
            }
            if (line[i] == '"' && line[i - 1] != '\\') {
                open_close_string = !open_close_string;
            }
        }

        if (input_line.length() != 0) out << input_line << std::endl;
    }
    std::cout << "I delete comment";
    return 0;
}


