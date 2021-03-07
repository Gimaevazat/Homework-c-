
#include <stdio.h>
#include <curl/curl.h>
#include <iostream>
#include <D:\Homework-c-\Hw5\currency rate(ex 1)\nlohmann\json.hpp>
#include <boost/algorithm/string.hpp>
#include <string>
#include <locale>
#include <iomanip>
#include <sstream>
#include <numeric>
#include <string_view>
#include <map>
//------------------------------JSON
using json = nlohmann::json;

const std::string url = "https://www.cbr-xml-daily.ru/daily_json.js"; //site with the price of currency
//const std::string url = "https://www.cbr-xml-daily.ru/daily_jsonp.js";
//const std::string url = "https://www.cbr-xml-daily.ru/daily_utf8.xml";


static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)//idk what is this
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

std::string Downloadjson(std::string URL) { //return string with price
	CURL* curl;
	CURLcode res;
	std::string readBuffer;

	curl = curl_easy_init();
	if (curl) {

		curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	return readBuffer;
}

long double price_in_RUB(std::string currency) {//return price of currency
	std::string a = Downloadjson(url);

	json j = json::parse(a);
	json h;
	json::iterator it = j.begin();

	// I don't need garbage, so i shift the iterator from begin to the block with price
	for (int i = 0; i != 4; i++) {
		++it;
	}

	h = *it;
	//find name of the currency and return its price
	if (h.find(currency) != h.end()) {
		long double a = *(*(h.find(currency))).find("Previous");
		long double b = *(*(h.find(currency))).find("Nominal");
		long double c = a / b;
		return c;
	}
	//if name of the currency wasn't found
	else {
		return -1;
	}
}

//-------------------------------------

const std::map <std::string, std::string> list_locale = { 
	{"USD", "en_US.UTF-8"},
	{"JPY","ja_JP.UTF-8" },
	{"EUR", "de_DE.UTF - 8"},
	{"AUD","en_AU.UTF - 8"},
	{"AZN" , "az_AZ.UTF-8"},
	{"GBP", "en_GB.UTF - 8"},
	{"AMD", "hy_AM.UTF-8"},
	{"BYN", "be_BY.UTF-8"},
	{"BGN", "bg_BG.UTF-8"},
	{"BRL","pt_BR.UTF-8"},
	{"HUF", "hu_HU.UTF-8"},
	{"HKD", "zh_HK.UTF-8"},
	{"DKK", "da_DK.UTF-8"},
	{"EUR","de_DE.UTF-8"},
	{"INR", "hi_IN.UTF-8"},
	{"KZT","kk_KZ.UTF-8"},
	{"CAD","en_CA.UTF-8"},
	{"KGS","ky_KG.UTF-8"},
	{"CHY","zh_CN.UTF-8"},
	{"NOK", "nb_NO.UTF-8"},
	{"PLN","pl_PL.UTF-8"},
	{"SGD", "en_SG.UTF-8"},
	{"TRY", "ku_TR.UTF-8"},
	{"UAH","uk_UA.UTF-8"},
	{"CZK","cs_CZ.UTF-8"},
	{"SEK","sv_SE.UTF-8"},
	{"CHF", "de_CH.UTF-8"},
	{"KRW","ko_KR.UTF-8"}
};

std::pair<std::string, std::string> give_locale(std::string input_string)
{
	input_string.erase(remove_if(input_string.begin(), input_string.end(), [](char c)
		{ return !isalpha(c); }), input_string.end());

	for (auto& c : input_string) c = toupper(c);

	auto search = list_locale.find(input_string);

	if (search != list_locale.end()) {
		return std::pair<std::string, std::string>(search->second, input_string);
	}
	else {
		std::cout << "Bad name of currency\n";
	}
}

void show(std::string input_string)
{
	std::istringstream s(input_string);
	std::string input_string_copy = input_string;

	std::pair<std::string, std::string> pair = give_locale(input_string_copy);

	s.imbue(std::locale(pair.first));
	std::cout.imbue(std::locale(pair.first));

	long double price;

	s >> std::get_money(price, false);

	std::cout << std::showbase << std::put_money(price, false) << " = ";

	price *= price_in_RUB(pair.second);

	std::cout.imbue(std::locale("ru_RU.utf8"));
	std::cout << std::showbase << std::put_money(price, false);
}



int main()
{

	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	std::string input_string;
	std::getline(std::cin, input_string);

	show(input_string);
	
	return 0;
}
