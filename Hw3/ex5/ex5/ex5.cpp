
#include <iostream>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

struct Rec {
	std::string name, phone;
	
};

struct Byname {};
struct Byphone {};

typedef boost::multi_index_container<
	Rec,
	boost::multi_index::indexed_by<
		boost::multi_index::random_access<>,
		boost::multi_index::hashed_non_unique<
			boost::multi_index::tag<Byname>, boost::multi_index::member<Rec, std::string, &Rec::name>
		>,
		boost::multi_index::hashed_non_unique<
			boost::multi_index::tag<Byphone>, boost::multi_index::member<Rec,std::string, &Rec::phone>
		>
	>
> Store;

void find_name(Store store, std::string Phone)
{
	
	Store::index<Byphone>::type::iterator it0, it1;
	tie(it0, it1) = store.get<Byphone>().equal_range(Phone);
	std::cout << "Owners of " << Phone << ": ";
	while (it0 != it1) { std::cout << (*it0).name << ", "; ++it0; }
}

void find_phone(Store store, std::string Name)
{
	Store::index<Byname>::type::iterator it0, it1;
	tie(it0, it1) = store.get<Byname>().equal_range(Name);
	std::cout << Name << " owns these number : ";
	while (it0 != it1) { std::cout << (*it0).phone << ", "; ++it0; }
}

int main()
{
	Store store;
	Rec r1 = { "Basilio Pupkinio", "022" };
	Rec r2 = { "Vasya Pupkin",     "0223" };
	Rec r3 = { "Basilio Pupkinio",     "0223" };
	store.push_back(r1);
	store.push_back(r2);
	store.push_back(r3);
	find_phone(store, "Basilio Pupkinio");
	std::cout << std::endl;
	find_name(store, "0223");
	std::cout << std::endl << store[1].name << " owns these number " << store[1].phone << std::endl;
	return 0;
}


