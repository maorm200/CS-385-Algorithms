/*
Moenika Chowdhury
October 19th, 2017
CS385
Water Jug Puzzle
I pledge my honor that I've abided by the Stevens Honor System.
 */

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

bool goalReached = 0;
int goal[2];
int capA, capB, capC;
string output;

// Struct to represent state of water in the jugs.
struct State {
private:
    int curA, curB, curC;
    vector<string> directions;

public:
    State(int a_, int b_, int c_, vector<string> adjacent){
    	curA = a_;
    	curB = b_;
    	curC = c_;
    	directions = adjacent;
    }

    string to_string() {
    	ostringstream oss;
    	oss << "(" << curA << ", " << curB << ", " << curC << ")";
    	return oss.str();
    }

    vector<string> set_direction() {
    	return directions;
    }

    int setA() {
    	return curA;
    }

    int setB() {
    	return curB;
    }

    int setC() {
    	return curC;
    }

    void print_directions() {
    	for(unsigned int i= 0; i<directions.size(); i++) {
    		cout << directions[i] << endl;
    	}
    }
};

    bool goal_reached(int a, int b) {
    	if ((a == goal[0]) && (b == goal[1])) {
    		return true;
    	} return false;
    }

    vector<string> make_directions(int a, int b, int c) {
    	vector<string> directions;
    	stringstream iss;
    	iss << "Initial state. (" << a << ", " << b << ", " << c << ")";
    	return directions;
    }

    string stringbuilder(int a, int b, int c) {
    	string newString;
    	stringstream iss;
    	iss << "(" <<a << ", " << b << ", " << c << ")";
    	newString = iss.str();
    	return newString;
    }

    queue<State> transfer;

void BreadthFirstSearch(int curA, int curB, int curC) {
	bool **visited = new bool*[capA + 1]; //checking if state has already been visited

	for(int i = 0; i<capA+1; i++) {
		visited[i] = new bool [capB + 1]; //creates 2D array
		fill(visited[i], visited[i] + capB+1, false); //fills the array with false, zeroes
	}

	//the current state of the search

	State states(curA, curB, curC, make_directions(curA, curB, curC));
	transfer.push(states);
	while(!transfer.empty()) {
		curA = transfer.front().setA();
		curB = transfer.front().setB();
		curC = transfer.front().setC();

		visited[curA][curB] = true; //marking the current state as visited

		if(goal_reached(curA, curB)) { //yes goal reached?
			transfer.front().print_directions(); //print how to get there
			goalReached = 1;
			break;
		}

		State initial = transfer.front();
		transfer.pop();

		//start with pouring jug C into jug A

		if(curA < capA) {
			int a = curA + curC; //pouring c into a
			int b = curB; //b stays the same

			if (a>capA) { //a can't be more than b
				a = capA;
			}

			int c = curC - (a-curA); //c-a

			if (b>capB) { //b can't be more than the capB
				b = capB;
			}

			stringstream iss;
			if((a-curA) > 1){
				iss << a-curA;
				output = "Pour " + iss.str() + " gallons from C to A. ";
			} else {
				iss<< a - curA;
				output = "Pour " + iss.str() + " gallons from C to A. ";
			}

			if(!visited[a][b]) { //was it visited?
				vector<string> totalPath = initial.set_direction(); //adds direction
				totalPath.push_back(output + stringbuilder(a, b, c));
				State CA(a, b, c, totalPath);
				transfer.push(CA);
			}
		}

		//jug B to jug A
		if(curA < capA) {
			if (curB !=0) {
				int c = curC;
				int a = curA + curB;

				if(a>capA) {
					a = capA;
				}

				int b = curB - (a-curA);
				if(b<0) {
					b = 0;
				}
				if (b>capB) {
					b = capB;
				}

				stringstream iss;
				if((curB - b) > 1) {
					iss << curB - b;
					output = "Pour " + iss.str() + " gallons from B to A. ";
				} else {
					iss << curB - b;
					output = "Pour " + iss.str() + " gallons from B to A. ";
				}

				if (!visited[a][b]) {
					vector<string> totalPath = initial.set_direction();
					totalPath.push_back(output + stringbuilder(a, b, c));
					State BA(a, b, c, totalPath);
					transfer.push(BA);
				}
			}
		}

		//jug C into B
		if (curB < capB) {
			int b = curB + curC;
			int a = curA;

			if (b > capB) {
				b = capB;
			}

			int c = curC - (b-curB);

			if(a > capA) {
				a = capA;
			}

			stringstream iss;
			if((b-curB) > 1) {
				iss << b-curB;
				output = "Pour " + iss.str() + " gallons from C to B. ";
			} else {
				iss << b-curB;
				output = "Pour " + iss.str() + " gallon from C to B. ";
			}

			if(!visited[a][b]) {
				vector<string> totalPath = initial.set_direction();
				totalPath.push_back(output + stringbuilder(a, b, c));
				State CB(a, b, c, totalPath);
				transfer.push(CB);
			}
		}

		//Jug a into jug b

		if(curB < capB) {
			if(curA != 0) {
				int c=curC;
				int a;
				int b = curA + curB;

				if(b>capB) {
					b = capB;
					a = curA - (b - curB);
				} else {
					a = 0;
				}
				if(a>capA) {
					a = capA;
				}

				stringstream iss;
				if((b-curB) > 1) {
					iss << b - curB;
					output = "Pour " + iss.str() + " gallons from A to B. ";
				} else {
					iss << b-curB;
					output = "Pour " + iss.str() + " gallon from A to B. ";
				}

				if (!visited[a][b]) {
					vector<string> totalPath = initial.set_direction();
					totalPath.push_back(output + stringbuilder(a, b, c));
					State AB(a, b, c, totalPath);
					transfer.push(AB);
				}
			}
		}

		//jug b to jug c
		if(curA + curB < capC) {
			if (curB != 0) {
				int c = curC + curB;

				if(c > capC) {
					c = capC;
				}

				int b = curC - c;
				int a = curA;

				if (b > capB) {
					b = capB;
				}

				if(b<0) {
					b = 0;
				}

				if (a>capA) {
					a = capA;
				}

				stringstream iss;
				if((curB - b) > 1) {
					iss << curB - b;
					output = "Pour " + iss.str() + " gallons from B to C. ";
				} else {
					iss << curB - b;
					output = "Pour " + iss.str() + " gallons from B to C. ";
				}

				if (!visited[a][b]) {
					vector<string> totalPath = initial.set_direction();
					totalPath.push_back(output + stringbuilder(a, b, c));
					State BC(a, b, c, totalPath);
					transfer.push(BC);
				}
			}
		}

		//jug A into C

		if((curA + curB) < capC) {
			if (curA != 0) {
				int c = curC + curA;

				if(c> capC) {
					c = capC;
				}

				int a = curA - (c - curC);
				if (a>capA) {
					a = capA;
				}

				if(a<0) {
					a = 0;
				}
				int b = curB;

				stringstream iss;
				if((curA - a) > 1) {
					iss << curA - a;
					output = "Pour " + iss.str() + " gallons from A to C. ";
				} else {
					iss << curA - a;
					output = "Pour " + iss.str() + " gallons from A to C. ";
				}

				if(!visited[a][b]) {
					vector<string> totalPath = initial.set_direction();
					totalPath.push_back(output + stringbuilder(a, b, c));
					State AC(a, b, c, totalPath);
					transfer.push(AC);
				}
			}
		}
	}

	if(!goalReached) {
		cout << "No solution." << endl;
	}

	// clean up the memory

	for(int i = 0; i<= capA; i++) {
		delete [] visited[i];
	}

	delete [] visited;
}

int main(int argc, char * const argv[]) {

  	istringstream iss;

	// Case 1: No input arguments, print usage message.
	if (argc < 2) {
		cerr << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
		// error
		return 1;
	}

	// Case 2: Too many input arguments, print usage message.
	if (argc > 7) {
		cerr << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
		// error
		return 1;
	}

	int a_g, a_c, b_g, b_c, c_g, c_c;
	iss.str(argv[1]);
	// if invalid capacity for jug A.
	if(!(iss >> a_c) || a_c < 0) {
		cerr << "Error: Invalid capacity '" << argv[1] << "' for jug A." << endl;
		// error
		return 1;
	}

	iss.clear();

	iss.str(argv[4]);

	// if invalid goal for jug A.
	if(!(iss >> a_g) || a_g < 0) {
		cerr << "Error: Invalid goal '" << argv[4] << "' for jug A." << endl;
		// error
		return 1;
	}

	iss.clear();

	iss.str(argv[2]);
	// if invalid capacity for jug B.
	if(!(iss >> b_c) || b_c < 0) {
		cerr << "Error: Invalid capacity '" << argv[2] << "' for jug B." << endl;
		// error
		return 1;
	}

	iss.clear();


	iss.str(argv[5]);

	// if invalid goal for jug B.
	if(!(iss >> b_g) || b_g < 0) {
		cerr << "Error: Invalid goal '" << argv[5] << "' for jug B." << endl;
		// error
		return 1;
	}

	iss.clear();

	iss.str(argv[3]);
	// if invalid capacity for jug C.
	if(!(iss >> c_c) || c_c <= 0) {
		cerr << "Error: Invalid capacity '" << argv[3] << "' for jug C." << endl;
		// error
		return 1;
	}

	iss.clear();

	iss.str(argv[6]);

	// if invalid goal for jug C.
	if(!(iss >> c_g) || c_g < 0) {
		cerr << "Error: Invalid goal '" << argv[6] << "' for jug C." << endl;
		// error
		return 1;
	}

	iss.clear();


	iss.str(argv[4]);

	// if exceed cap jug A
	if (a_c < a_g ) {
		cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
		// error
		return 1;
	}

	iss.clear();

	iss.str(argv[5]);

	// if exceed cap jug B.
	if (b_c < b_g ) {
		cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
		// error
		return 1;
	}

	iss.clear();

	iss.str(argv[6]);

	// if exceed cap jug C.
	if ((c_c < c_g) ) {
		cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
		// error
		return 1;
	}

	if ((c_c) != (a_g + b_g + c_g) ) {
		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
		// error
		return 1;
	}

	iss.clear();

	// make array for goals
		for (int i = 4; i <= 6; i++) //loop through every goal
		{
			istringstream issN (argv[i]);
			int temp;
			issN >> temp;
			goal[i - 4] = temp; //put them in the first 3 positions in an array
		}

		//using the arguments as values

		istringstream issA(argv[1]);
		int temp;
		issA >> temp;
		capA = temp;
		istringstream issB(argv[2]);
		issB >> temp;
		capB = temp;
		istringstream issC(argv[3]);
		issC >> temp;
		capC = temp;

		BreadthFirstSearch(0, 0, capC); //calling the search function
}
