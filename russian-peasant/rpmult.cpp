//moenika chowdhury
//lab 7: russianpeasant.cpp
//I pledge my honor that I've abided by the Stevens Honor System

#include <iostream>
#include <sstream>
#include <string>

using namespace std;
//get the product of two non-negative integers using the Russian Peasant Multiplication Method
unsigned long russian_peasant_multiplication(unsigned int m, unsigned int n){
	unsigned long firstNum = m;
	unsigned long secondNum = n;
	unsigned long result = 0;

	while(secondNum > 0) { //when n doesn't become equal to 1
		if(secondNum & 1) {
			result += firstNum; //if n is odd then you add m to the result
		}
		//using bitwise to multiply and divide
		firstNum = firstNum << 1; //shifting to the left is multiplying by doubling
		secondNum = secondNum >> 1; //shifting to the right is dividing in half
	}
	return result; //returning the answer provided by bitwise shifting
}

int main(int argc, char * const argv[]) {
	int m;
	int n;

	stringstream iss;

//ERROR CHECKING

	if(argc != 3) { //checks the user puts in 2 arguments, length of 3.
		cout << "Usage: ./rpmult <integer m> <integer n>" << endl;
		return 0;
	}

	iss.str(argv[1]);

	if(!(iss >> m)) {
		cerr << "Error: The first argument is not a valid nonnegative integer." << endl;
		return 0;
	}

	iss.clear();
	iss.str(argv[2]);
	if(!(iss>>n)) {
		cerr << "Error: The second argument is not a valid nonnegative integer." << endl;
		return 0;
	}

	if (m < 0) { //if m is a negative number
		cerr << "Error: The first argument is not a valid nonnegative integer." << endl;
		return 0;
	}

	if (n<0) { //if n is a negative number
		cerr << "Error: The first argument is not a valid nonnegative integer." << endl;
		return 0;
	}

	cout << m << " x " << n << " = " << russian_peasant_multiplication(m, n) << endl;
}
