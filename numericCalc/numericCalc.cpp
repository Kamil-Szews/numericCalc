#include <iostream>
#include <vector>
#include <cmath>

int convertLetter(char myLetter) {
	for (int i = 0; i < 9; i++) {
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

std::vector<int> stringToVec(std::string myNumber) {
	std::vector<int> result;
	for (int i = myNumber.size()-1; i >= 0; i--) {
		result.push_back(convertLetter(myNumber[i]));
	}
	return result;
}

int anyToDec(std::string myNumber, int mySys) {
	std::vector<int> myInts = stringToVec(myNumber);
	int result = 0;
	for (int i = 0; i < myNumber.length(); i++) {
		result += pow(mySys, i) * myInts[i];
	}
	return result;
}

int decToAny(int myInt, int myFinalSys) {
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
			std::cout << it << " " << sysPowers[it] << " " << maxPower << "\n";
			it++;
		}
	}
	int myHelper = 0;
	std::vector<int> finalValues;
	for (int i = it - 1; i >= 0; i--) {
		flag = true;
		for (int j = 0; j < myFinalSys - 1; j++) {
			if ((sysPowers[i] * j) >= myInt && flag) {
				finalValues.push_back(sysPowers[i] * j);
				flag = false;
			}
		}
		if (flag == false) {
			finalValues.push_back(0);
		}
	}
	for (int i = it - 1; i >= 0; i--) {
		std::cout << "fV: " << finalValues[i] << "\n";
	}
	return 0;
}

int main() {
	int x = anyToDec("AAAA", 18);
	std::cout << x;
	//int y =  decToAny(300, 16);
	return 0;
}


