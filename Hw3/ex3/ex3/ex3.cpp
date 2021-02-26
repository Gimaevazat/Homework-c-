


#include <iostream>
#include <boost/functional/hash.hpp>

int main()
{
    boost::hash<std::string> string_hash;
    std::size_t a = string_hash("Hash me");
    std::cout <<  a;
}
