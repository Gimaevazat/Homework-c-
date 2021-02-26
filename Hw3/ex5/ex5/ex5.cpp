
#include <iostream>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/key.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <boost/tokenizer.hpp>
#include <typeinfo>

struct Rec {
	std::string name, surname, phone;
	
};

struct Byname {};
struct Bysurname {};
struct Byphone {};
struct Bykey {};
struct PhoneChange : public std::unary_function<Rec, void> {
	std::string p; PhoneChange(const std::string& _p) : p(_p) {}
	void operator()(Rec& r) { r.phone = p; }
};

typedef boost::multi_index_container<
	Rec,
	boost::multi_index::indexed_by<
		//boost::multi_index::random_access<>,
		boost::multi_index::ordered_unique<
			boost::multi_index::tag<Bysurname>, boost::multi_index::member<Rec, std::string, &Rec::surname>,
			std::less<std::string>
		>,
		boost::multi_index::hashed_non_unique<
			boost::multi_index::tag<Byname>, boost::multi_index::member<Rec, std::string, &Rec::name>
		>,
		boost::multi_index::hashed_non_unique<
			boost::multi_index::tag<Byphone>, boost::multi_index::member<Rec,std::string, &Rec::phone>
		>,
		boost::multi_index::hashed_non_unique<
			boost::multi_index::tag<Bykey>, boost::multi_index::composite_key<
				Rec,
				boost::multi_index::member<Rec, std::string, &Rec::name>,
				boost::multi_index::member<Rec, std::string, &Rec::surname>
			>
		>
	>
> Store;

void find_name(Store store, std::string Phone)
{
	Store::index<Byphone>::type::iterator it0, it1;
	tie(it0, it1) = store.get<Byphone>().equal_range(Phone);
	std::cout << "Owners of " << Phone << ": ";
	while (it0 != it1) { std::cout << (*it0).name << " " << (*it0).surname << ", "; ++it0; }
}

void find_phone(Store store, std::string Name)
{	
	std::string name, surname;
	bool flag = false;
	for (int i = 0; i < Name.size(); i++) {
		if (!flag && Name[i] != ' ') name += Name[i];
		if (flag && Name[i] != ' ') surname += Name[i];
		if (Name[i] == ' ') flag = true;
	}
	Store::index<Bykey>::type::iterator it0, it1;
	tie(it0, it1) = store.get<Bykey>().equal_range(std::make_tuple (name, surname));
	std::cout << Name << " owns these number : ";
	while (it0 != it1) { std::cout << (*it0).phone << ", "; ++it0; }
}

void show_all(Store store) {
	auto it = store.begin();
	auto it0 = store.end();
	while (it != it0) {
		std::cout << (*it).surname << " " << (*it).name << ": " << (*it).phone << std::endl;
		++it;
	}
}

Rec show_index(Store store, int index) {
	auto it = store.begin();
	for (int i = 0; i < index; i++) {
		++it;
	}
	return (*it);
}


int main()
{
	Store store;
	Rec r1 = { "Basilio", "Pupkinio", "022" };
	Rec r2 = { "Vasya", "Zdsds",     "0223" };
	Rec r3 = { "Basilio" , "Pupkinioo",     "0223" };

	store.insert(r1);
	store.insert(r2);
	store.insert(r3);\

	std::cout << "find_phone" << std::endl;
	find_phone(store, "Basilio Pupkinio");
	std::cout << std::endl;

	std::cout << std::endl  << "find_name" << std::endl;
	find_name(store, "0223");
	std::cout << std::endl;

	std::cout << std::endl << "show_all" << std::endl;
	show_all(store);

	std::cout << std::endl  << "show_index" << std::endl;
	std::cout << show_index(store, 1).surname << " " << show_index(store, 1).name
		<< ": " << show_index(store, 1).phone << std::endl;
	
	return 0;
}


