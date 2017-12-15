/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Moenika Chowdhury
 * Date        : September 17th, 2017
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I've abided by the Stevens Honor System
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve { //main class. (template)

public:
    PrimesSieve(int limit) : is_prime_{new bool[limit + 1]}, limit_{limit} {
        sieve();
    }

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    inline int num_primes() const {
        return num_primes_;
    }

    void display_primes() const {
        // TODO: write code to display the primes in the format specified in the
        // requirements document.
    	//for formatting, need to display how many primes are found

    	cout << endl << "Number of primes found: " << num_primes_ << endl;
    	    	cout << "Primes up to " << limit_ << ":" << endl;

        // since the max amount of characters on a line is 80 we need to wrap them to the next line
    	// need a helper function to determine how many primes to print each row

    	const int max_prime_width = num_digits(max_prime_), primes_per_row = 80 / (max_prime_width + 1);


    	//if there is one line of prime numbers, print the following
    	if (num_primes_ <= primes_per_row) {
    		for (int n=0; n<=limit_; n++) {
    			if(is_prime_[n]) {
    				if(n!= max_prime_){ //if n doesn't equal the max prime then print
    					cout<<n<<" ";
    				}

    				else cout<<n<<endl;
    			}
    		}
    	}

    	//if there are more than one lines of primt, print the following
    	else {
    		for (int i=0, counter = 1; i<= limit_; i++) {
    			if(is_prime_[i] == true) {
    				if(counter != primes_per_row) {
    					if (i != max_prime_) {
    						cout<<setw(max_prime_width) <<i<<" ";
    						counter += 1;
    					}
    					else {
    						cout<<setw(max_prime_width) <<i;
    						counter ++;
    					}
    				} else {
    					cout <<setw(max_prime_width) <<i<<endl;
    					counter = 1;
    				}
    			}
    		}
    	}
    }

private:
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    int count_num_primes() const {
        // TODO: write code to count the number of primes found
    	// counting the number of primes found within its range/limit
    	int counter = 0;
    	for(int i=2; i <= limit_; i++) {
    		if(is_prime_[i]) {
    			counter++;
    		}
    	}

    	return counter;
    }

    int num_digits(int num) const {
        // TODO: write code to determine how many digits are in an integer
        // Hint: No strings are needed. Keep dividing by 10.
    	// counts how many digits are in the input num

    	int counter = 0;
    	while(num != 0) {
    		num /= 10;
    		counter++;
    	}
    	return counter;
    }

    void sieve() {
        // TODO: write sieve algorithm
    	// is_prime is an array of boolean values being indexed by integers 2-n
    	for(int i = 2; i<= limit_; i++) { //letting is_prime be an array of boolean values
    		is_prime_[i] = true; //indexed by integers 2 to n
    	}

    	for (int i = 2; i< sqrt(limit_); i++) { //following the pseudocode
    		if(is_prime_[i]) {

    			for(int j = pow(i, 2.0); j<= limit_; j += i) { //for all i such that is_prime[i] is true are prime numbers
    				is_prime_[j] = false;
    			}
    		}
    	}

    	num_primes_ = count_num_primes();

    	// need to find the biggest prime to break out of the loop

    	for(int y = limit_; y>=2; y--) {
    		if(is_prime_[y]) {
    			max_prime_ = y;
    			break;
    		}
    	}
    }
};

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.

    PrimesSieve s(limit);
    s.display_primes();
    return 0;
}
