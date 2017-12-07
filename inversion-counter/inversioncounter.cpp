/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Moenika Chowdhury
 * Version     : 1.0
 * Date        : November 3rd, 2017
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I've abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    // TODO
	long counter = 0;
	for(int i = 0; i<length-1; ++i) { //gets the first element in the list
		for(int j = i+1; j<length; ++j) { //2nd element in the list
			if(array[i] > array[j]) { //need to compare the adjacent elements, then increase the number of inversions if the first element i is larger than j

				counter += 1; //adds value to the counter
			}
		}
	}
	return counter;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
	int * scratch = new int[length];
	long counter;
	counter = mergesort(array, &scratch[0], 0, length-1); //calls mergesort to get inversions quickly
	delete[] scratch;
	return counter; //counts the number of inversions in the array in theta(n lg n) time, returns here to counter
}

static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
	long counter = 0;
	int middle;
	if(low < high) {
		middle = (low + high)/2; //splits the array in half
		counter = mergesort(array, scratch, low, middle);
		counter += mergesort(array, scratch, middle+1, high);

		int X = low; //low subarray
		int Y = middle + 1; //middle subarray

		for (int k = low; k<= high; k++) {
			if(X <= middle && (Y > high || array[X] <= array[Y])) {
				scratch[k] = array[X];
				X++; //adds to low value
			} else {
				scratch[k] = array[Y];
				Y++; //adds to middle + 1
				counter += (middle - X) + 1;
			}
		}

		for(int k = low; k <= high; ++k) {
			array[k] = scratch[k];
		}
	}

	return counter;
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument

	if(argc > 2) {
		cerr << "Usage: " << argv[0] << " [slow]" << endl;
		return 1;
	}
	else if((argc == 2) && strcmp("slow", argv[1]) != 0) {
		cerr << "Error: Unrecognized option \'" << argv[1] << "\'.";
		return 1;
	}

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    // TODO: produce output

    int size = values.size(); //checking if there are values entered
    if(size == 0) {
    	cerr << "Error: Sequence of integers not received.";
    	return 1; //error
    }

    int *convertvector = &values[0]; //calculates the inversions slow
    if(argc == 2) {
    	cout << "Number of inversions: " << count_inversions_slow(convertvector, size) << endl;

    }

    else { //calculates the inversions fast
    	cout << "Number of inversions: " << count_inversions_fast(&values[0], size) << endl;
    }

    return 0;
}
