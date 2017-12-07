/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Moenika Chowdhury
 * Date        : September 23rd, 2017
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I've abided by the Stevens Honor System. Moenika Chowdhury
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) { //read only reference &s
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.

	for(size_t x = 0; x< s.length(); x++) { //read only
		char character = s[x];
				if(! islower(character)) { //confirms they are letters in the english alphabet
					return false;
				}
	}

	return true;
}

/*
 * logic for all unique letters:
 * 1. find the index of string.at(x) - 'a'
 * 2. compute 2^ index which should give me 0's with a 1 at the index we found
 * 3. need to do a bitwise and function with the counter, which is the store and the calculated index
 * 4. if this is > 0, this letter exists and we return false since its not unique
 * 5. if it is = 0 keep going through the iterations
 * 6. need to use a bitwise OR which is '|' of our counter and the 2^index calculated first
 * 7. need binary to check if there are duplicates
 */
bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.

	unsigned int counter = 0; //unsigned makes sure the counter is never 0
	for (size_t x = 0; x <s.length(); x++) {
		unsigned int value = s.at(x) - 'a'; //assesses the index

		if((counter & (1 << value)) > 0) { //using bitwise operations to compare storage with 2^index
			return false;
		} //if the counter and shifted value and >0 then they are the same, hense not unique
		counter = counter | (1 << value);

	}
	return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.

	if(argc !=2) {
		cout << "Usage: ./unique <string>" << endl;
		return 0;
	}
	if (is_all_lowercase(argv[1])) {
		if(all_unique_letters(argv[1])) {
			cout << "All letters are unique."; //output formatting
			return 0;
		} else {
			cout << "Duplicate letters found.";
			return 0;
		}
	}

	cerr << "Error: String must contain only lowercase letters." << endl;
	return 0;
}
