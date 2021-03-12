#include <fstream>
#include <iostream>
#include <D:\Homework-c-\Hw6\ex4\nlohmann\json.hpp>
#include <string>
#include <iomanip>
#include <locale>
#include <ostream>
#include <istream>
#include <filesystem>
#include <string>

using json = nlohmann::json;


class Person
{
private:
    std::string name, surname, country, city;
    int age;

public:
    Person(std::string s = "", int a = 0)  
    {
        name = s;
        surname = s;
        country = s;
        city = s;
        age = a;
    }
    std::string name_() {
        return name;
    }
    std::string surname_() {
        return surname;
    }
    std::string country_() {
        return country;
    }
    std::string city_() {
        return city;
    }
    int age_() {
        return age;
    }
    friend std::istream& operator>> (std::istream& in, Person& person);
};

std::istream& operator>> (std::istream& in, Person& person)
{
    in >> person.name;
    in >> person.surname;
    in >> person.age;
    in >> person.country;
    in >> person.city;

    return in;
}

json make_json() {
    Person person;
    std::cin >> person;
    json j;
    
    j["address"]["city"] = person.city_();
    j["address"]["country"] = person.country_();
    j["person"]["age"] = person.age_();
    j["person"]["surname"] = person.surname_();
    j["person"]["name"] = person.name_();

    return j;
}

void create_file(std::filesystem::path path) {
    json j = make_json();
    std::string s;
    //------------create json file like name_surname.json
    s += j.find("person").value().find("name").value();
    s += "_";
    s += j.find("person").value().find("surname").value();
    s += ".json";

    std::ofstream out(path / s);
    out << std::setw(4) << j;
    out.close();
}

int main(int argc, char **argv)
{
    system("chcp 1251");
    std::filesystem::path path = "./";
    std::filesystem::create_directory(path/ "JSON");

    path = path / "JSON";

    bool flag = true;

    while (flag) {
        create_file(path);
        std::cout << "IF you want to add more people, then enter 1, otherwise 0" << std::endl;
        std::cin >> flag;
    }

}

