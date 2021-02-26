

#include <stdio.h>    
#include <math.h>       
#include <iostream>
#include <bitset>
#include <cmath>
#include <cstddef>
#include <string>
#include <functional>

std::string dictionary(int a) {
	if (a < 10) return std::to_string(a);
	if (a == 10) return "A";
	if (a == 11) return "B";
	if (a == 12) return "C";
	if (a == 13) return "D";
	if (a == 14) return "E";
	if (a == 15) return "F";
}
std::string bit_int(float number) //integral part to binary system
{
	bool flag = true;
	float number_abs = abs(number);
	float fractpart, intpart;
	fractpart = modf(number_abs, &intpart);

	std::bitset<sizeof(intpart)*8> bit (intpart);
	std::string string_bit_int;
	
	for (int i = bit.size() - 1; i >= 0 ; i--) {
		if (flag && bit[i] == 1) {
			flag = false;
		}
		if (!flag) {
			if (bit[i] == 1) {
				string_bit_int +="1";
			}
			if (bit[i] == 0) {
				string_bit_int += "0";
			}
		}
	}
	return string_bit_int;
}

std::string bit_fract(float number) //fractional part to binary system
{ 
	std::string bits;
	float number_abs = abs(number);
	float fractpart, intpart;
	fractpart = modf(number_abs, &intpart);
	bool flag = true;						
	bool empty = bit_int(number).empty();
	int N = 24;
	int bit_int_lenght = bit_int(number).length();

	for (int i = 0; i <= N - bit_int_lenght; i++) {
		if (empty && flag) { //if integral part = 0 i need more bits cuz mantissa = 23
			i--;
		}
		fractpart *= 2;
		if (fractpart - 1 < 0) {
			bits += "0";
		}
		if (fractpart - 1 > 0) {
			bits += "1";
			fractpart -= 1;
			flag = false; 
		}
	}

	return bits;
}

std::string number_bits(float number)  //number to binary system
{ 
	std::string exponent;
	std::string mantissa;
	std::string number_string = bit_int(number) + bit_fract(number);
	std::pair<std::string, std::string> pair;

	int i = 0;
	while (number_string[i] == 0) {
		i++;
	}

	int exp = bit_int(number).length() - i - 1; // int exponent 
	exponent = bit_int(exp + 127);  // string exponent

	for (int j = i + 1; j < number_string.length(); j++) {
		mantissa += number_string[j];
	}

	number_string.clear();

	if (number > 0) number_string += "0";
	if (number < 0) number_string += "1";
	number_string += exponent;
	number_string += mantissa;

	return number_string;
}

std::string number_16(float number) //number to 16 system
{
	std::string number_string = number_bits(number);
	std::string number_string_16;
	for (int i = 0; i < 8; i++) {
		int b = 0;
		
		b = (number_string[4 * i] - '0') * 8 + (number_string[4 * i + 1] - '0') * 4 +
			(number_string[4 * i + 2] - '0') * 2 + (number_string[4 * i + 3] - '0');
		
		number_string_16 += dictionary(b);
	}

	return number_string_16;
}

int main()
{
	float param = 13.374;
	
	std::cout << "Number in 16 system: " << number_16(param) << std::endl;
	std::cout << "Hash number: " <<  std::hash <std::string> {}(number_16(param)) << std::endl;
	
	return 0;
}


