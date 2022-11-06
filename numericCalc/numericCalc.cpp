#include <iostream>
#include <vector>
#include <cmath>
#include <string> 

int charToInt(char myLetter) { // converting letter in any system to int e.g.: E to 15 or C to 13
	for (int i = 0; i <= 9; i++) {
		if (myLetter == char(i + 48)) {
			return i;
		}
	}
	for (int i = 0; i < 26; i++) {
		if (myLetter == char(i + 65)) {
			return (i + 10);
		}
		else if (myLetter == char(i + 97)) {
			return (i + 10);
		}
	}
	return 0;
}

std::string convertToString(std::vector<int> finalValuesVector) { // converting vector of int's values to string e.g.: 17, 13, 9, 0, 10 to GC90A
	std::string finalString = "";								  
	for (int i = 0; i < finalValuesVector.size(); i++) {
		if (finalValuesVector[i] < 10) {
			finalString += std::to_string(finalValuesVector[i]);
		}
		else {
			finalString += char(55 + finalValuesVector[i]);
		}
	}
	return finalString;
}

std::vector<int> stringToVec(std::string myNumber) { // converting array of characters to vector of int's
	std::vector<int> vecOfInts;
	for (int i = myNumber.size()-1; i >= 0; i--) {
		vecOfInts.push_back(charToInt(myNumber[i]));
	}
	return vecOfInts;
}

std::vector<int> powersOfSystem(int myInt, int myFinalSys) { // creating a vector of all needed powers of system to convert our number
	std::vector<int> sysPowers;
	int maxPower = 0;
	int it = 0;
	bool flag = true;
	while (flag) {
		if (maxPower >= myInt) {
			flag = false;
		}
		else {
			sysPowers.push_back(pow(myFinalSys, it));
			maxPower += (pow(myFinalSys, it) * (myFinalSys - 1));
			it++;
		}
	}
	return sysPowers;
}

int anyToDec(std::string myNumber, int mySys) { // convetring a number of any system to decimal system
	std::vector<int> myInts = stringToVec(myNumber);
	int decNumber = 0;
	for (int i = 0; i < myNumber.length(); i++) {
		decNumber += pow(mySys, i) * myInts[i];
	}
	return decNumber;
}

std::string decToAny(int myInt, int myFinalSys) { // convetring decimal number to any system 
	std::vector<int> sysPowers = powersOfSystem(myInt, myFinalSys);
	bool flag = true;
	std::vector<int> finalValues;
	for (int i = sysPowers.size() - 1; i >= 0; i--) {
		flag = true;
		for (int j = myFinalSys - 1; j >= 0; j--) {
			if (myInt - (sysPowers[i] * j) >= 0 && flag) {
				finalValues.push_back(j);
				myInt -= sysPowers[i] * j;
				flag = false;
			}
		}
	}
	return convertToString(finalValues);
}

bool dataIsGood(std::string myValue, std::string previousSystem, int finalSystem) { // checking if the data is good
	if (finalSystem < 0 || finalSystem > 36) {
		return false;
	}
	for (int i = 0; i < previousSystem.size(); i++) {
		if (int(previousSystem[i]) <= 48 || int(previousSystem[i]) >= 57) {
			return false;
		}
	}
	int previousSystemInt = std::stoi(previousSystem);
	for (int i = 0; i < myValue.size(); i++) {
		if (charToInt(myValue[i]) >= previousSystemInt) {
			return false;
		}
	}
	return true;
}

std::string anyToAny(std::string myValue, std::string previousSystemString, int finalSystem) { // convetring a number of any system to a number of any system
	if (dataIsGood(myValue, previousSystemString, finalSystem)) {
		int previousSystemInt = std::stoi(previousSystemString);
		return decToAny(anyToDec(myValue, previousSystemInt), finalSystem);
	}
	return "Wrong input data.";
}

int main() {
	std::string x = anyToAny("a82823", "11", 16); // number, system of this number, our new system -> our number in new system
	std::cout << x;
	return 0;
}


