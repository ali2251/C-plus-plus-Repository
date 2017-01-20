// TODO: implement romanToInteger in here
#include "Roman.h"
#include <string>
#include <vector>
using std::vector;
using std::string;


int romanToInteger(const string & s) {
	//local variable so dont have to change original s
	string localS = s;

	string one = "I";
	string four = "IV";
	string five = "V";
	string nine = "IX";
	string ten = "X";
	string forty = "XL";
	string fifty = "L";
	string ninety = "XC";
	string hundred = "C";
	string forHundred = "CD";
	string fiveHundred = "D";
	string nineHundred = "CM";
	string thousand = "M";

	int sums = 0;

	
	vector<string> toDelete;

	for(int i = 0; i < localS.length(); ++i) {

		//last index to be considered
		
		string temp = localS.substr(i, 2);

		if(temp == four) {
			sums += 4;
			toDelete.push_back(temp);
	
		} else if(temp == nine) {
			sums += 9;
			toDelete.push_back(temp);
		
		} else if(temp == forty) {
			sums += 40;
			toDelete.push_back(temp);
	
		} else if(temp == ninety) {
			sums +=90;
			toDelete.push_back(temp);
		
		} else if(temp == forHundred) {
			sums +=400;
			toDelete.push_back(temp);

		} else if(temp == nineHundred) {
			sums += 900;
			toDelete.push_back(temp);
		}

		

	}

	for(string a: toDelete) {

		auto toDelete = localS.find(a);
		localS.erase(toDelete,2);

	}


	for(int i = 0; i < localS.length(); i++) {

		string temp = localS.substr(i,1);

		if(temp == one) {
			sums += 1;
		} else if(temp == five) {
			sums += 5;
		} else if(temp == ten) {
			sums += 10;
		} else if(temp == fifty) {
			sums += 50;
		} else if(temp == hundred) {
			sums +=100;
		} else if(temp == fiveHundred) {
			sums += 500;
		} else if(temp == thousand) {
			sums +=1000;
		}

	}

	return sums;

}