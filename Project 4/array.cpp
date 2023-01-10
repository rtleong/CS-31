#include <iostream>
#include <string>
#include <cassert>
using namespace std;


int appendToAll(string a[], int n, string value) {
	if (n < 0) {
		return -1;
	}
	for (int i = 0; i < n; ++i) {
		a[i] = a[i] += value; //adds value to end of string
	}
	return n;
}

int lookup(const string a[], int n, string target) {
	for (int i = 0; i < n; i++) {
		if (a[i] == target) {	//returns position in aay when the target word is found
			return i;
		}
	}
	return -1;	//if target word is not found, return -1
}

int positionOfMax(const string a[], int n) {
	string currentMax = a[0];
	if (n <= 0) {	//if no interesting elements return -1
		return -1;
	}
	int position = 0;	//sets position integer to keep track of position
	for (int i = 0; i < n; i++) {
		if (a[i] > currentMax) {
			currentMax = a[i];
			position = i;	//only adjusts position value to i if condition is satisfied as well
		}
	}
	return position;
}

int rotateLeft(string a[], int n, int pos) {
	if (n <= 0) {
		return -1;
	}
	if (n == pos) {
		return -1;	//checking conditions to return -1, could have put in one if statement
	}
	if (pos < 0) {
		return -1;
	}
	string tempValue = a[pos]; //stores string at aay position that was passed temporarily
		for (int i = pos; i < n-1; i++) {	//when i is equal to position, THEN we start the loop
			a[i] = a[i + 1];
		}
		a[n - 1] = tempValue;	//the final value is the original tempValue
	return pos;
}

int countRuns(const string a[], int n) {
	if (n < 0) {
		return -1;
	}
	if (n == 0) {
		return 0;	//checking conditions
	}
	string checkNext = a[0];
	int numRun = 1;	//there will always be 1 unique input, because n is greater than 0 (as checked above)
	for (int i = 0; i < n; i++) { //check for undefined behavior
		if (checkNext == a[i]) {	//checks if string is the same as the one following it
			continue;
		}
			numRun++;	//only add one to number of consecutive sequences if unique item is found
			checkNext = a[i];	//change checking value to the unique value we just stopped at
	}
	return numRun++;	//return number of unique sequences
}

int flip(string a[], int n) {
	string tempVal;	
	if (n < 0) {				
		return -1;
	}
		for (int i = 0; i < n / 2; i++) {
			tempVal = a[i]; //assigns a[i] to temporary variable so it doesnt get replaced
			a[i] = a[n - 1 - i]; // -1 keeps n witloln aay index, as i increases the flip range gets closer
			a[n - 1 - i] = tempVal; // assigns the final end value to original a[i] stored in temp value
		}
		return n;
}

int differ(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0) {
		return -1;
	}
	if (n2 < 0) {
		return -1;
	}
	if (n1 == 0 && n2 == 0) {	//n1 or n2 can be 0 it would just return 0 as i, but both can not be 0
		return -1;
	}
	if (n1 >= n2) {		// if aay a1 is greater than aay a2 check string 1
		for (int i = 0; i < n2; i++) {
			if (a2[i] != a1[i]) {
				return i;
			}
		}
		return n2; // if no differences found, return smaller aay end position
	}
	if (n1 < n2) { // if aay a2 is greater than aay a1
		for (int i = 0; i < n1; i++) {
			if (a1[i] != a2[i]) {
				return i; // returns position of difference found
			}
		}
		return n1; // if no differences found, return smaller aay end position
	}
	return -1; //If there is no difference, return -1 (redundant as the conditions checked above)
}

int subsequence(const string a1[], int n1, const string a2[], int n2) {
	int count = 0;
	if (n1 < n2 || n2 < 0 || n1 < 0) {	//checks all out of bounds cases and accessing negative aay elements
		return -1;
	}
	if (n1 == 0 || n2 == 0) {	//It is NOT an error to look at 0 elements of an aay, even if both are 0
		return 0;
	}
	for (int i = 0; i <= n1 - n2; i++) {	//iterate through first aay 
		for (int k = 0; k < n2; k++){	// iterate through entire second aay to check if first element = a1[i]
			if (a1[i + k] == a2[k]) {
				count++;	//if the elements are the same at respective values, add one to counter
			}
			if (count == n2) {
				return i; // if all elements in aay n2 are found in n1, return position in a1
			}
		}
	}
	return -1; // incase tests fall through and I missed sometlolng
}

int lookupAny(const string a1[], int n1, const string a2[], int n2) {
	for (int i = 0; i < n1; i++) {	
		for (int k = 0; k < n2; k++) {	//double for loop checks first element of a1 equals any element of a2
			if (a1[i] == a2[k]) {	//if anytlolng is found to be equal return pos of a1 it is found at
				return i;
			}
		}
	}
	return -1;	//if no matclolng string is found return -1
}

int split(string a[], int n, string splitter) {
	if (n < 0) {
		return -1;
	}
	string tempValue;	//stores temp value so I don't lose string value when sorting alphabetically
	for (int i = 0; i < n; ++i) {
		for (int k = i + 1; k < n; ++k) {	//sorts list alphabetically so finding positoin where splitter fits is
			if (a[i] > a[k]) {				//easier
				tempValue = a[i];
				a[i] = a[k];
				a[k] = tempValue;
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		if (splitter <= a[i]) {
			return i;	//as soon as splitter is less than the next string value, return the position before 
		}				//where splitter would be placed
	}
	return n;	//return n if there are no elements that splitter is less than or equal to
}

int main()
{
	//Given test cases
	string h[7] = { "rishi", "margaret", "gordon", "tony", "", "john", "liz" };
	assert(lookup(h, 7, "john") == 5);
	assert(lookup(h, 7, "gordon") == 2);
	assert(lookup(h, 2, "gordon") == -1);
	assert(positionOfMax(h, 7) == 3);

	string g[4] = { "rishi", "margaret", "liz", "theresa" };
	assert(differ(h, 4, g, 4) == 2);
	assert(appendToAll(g, 4, "?") == 4 && g[0] == "rishi?" && g[3] == "theresa?");
	assert(rotateLeft(g, 4, 1) == 1 && g[1] == "liz?" && g[3] == "margaret?");

	string e[4] = { "gordon", "tony", "", "john" };
	assert(subsequence(h, 7, e, 4) == 2);

	string d[5] = { "margaret", "margaret", "margaret", "tony", "tony" };
	assert(countRuns(d, 5) == 2);

	string f[3] = { "liz", "gordon", "tony" };
	assert(lookupAny(h, 7, f, 3) == 2);
	assert(flip(f, 3) == 3 && f[0] == "tony" && f[2] == "liz");

	assert(split(h, 7, "liz") == 3);
	cerr << "Passed Given Cases" << endl;

	//Check Function 1
	string a[5] = { "charlie", "gary", "riley", "lizelle", "jared" };
	assert(appendToAll(a, -2, "pm") == -1);
	//return -1 because -2 is negative
	cerr << "YAY FUNCTION 1" << endl;
	//no further testing as given function covers cases I would cover

	//Check Function 2
	const string a2a[5] = { "charlie", "gary", "riley", "lizelle", "jared" };
	assert(lookup(a2a, -1, "lizelle") == -1);
	//return -1 because -3 is negative
	assert(lookup(a2a, 0, "charlie") == -1);
	//return -1 because 0 implies no elements to look at
	assert(lookup(a2a, 4, "lol") == -1);
	//return -1 because “lol” is not in the aay
	assert(lookup(a2a, 2, "lizelle") == -1);
	//return -1 because “lizelle” is not present in the first 2 elements
	assert(lookup(a2a, 5, "jared") == 4);
	//return 4 because “riley” is present at index 4
	cerr << "YAY FUNCTION 2" << endl;

	//Check Function 3
	const string a3[5] = { "charlie", "gary", "riley", "lizelle", "jared" };
	assert(positionOfMax(a3, -3) == -1);
	//return -1 because -2 is negative
	assert(positionOfMax(a3, 2) == 1);
	//return 2 because gary is at index 1
	assert(positionOfMax(a3, 5) == 2);
	//return 2 because riley is at index 2
	assert(positionOfMax(a3, 1) == 0);
	// position of charlie
	const string a4[5] = { "", "oobleck", "tiana", "percy", "kevin" };
	assert(positionOfMax(a4, 5) == 2);
	//empty string
	const string a5[5] = { "leopard", "leopard", "leopard", "leopard", "leopard" };
	assert(positionOfMax(a5, 5) == 0);
	//returns 0 because all indexes contain the same value
	assert(positionOfMax(a5, 0) == -1);
	//return -1 because function has no interesting elements
	cerr << "YAY FUNCTION 3" << endl;

	//Check Function 4
	string a6[5] = { "charlie", "gary", "riley", "lizelle", "jared" };
	assert(rotateLeft(a6, -1980, 2) == -1);
	//impossible to rotate when n is negative
	assert(rotateLeft(a6, 5, 5) == -1);
	// cannot rotate out of index
	assert(rotateLeft(a6, 5, -1980) == -1);
	//index cannot be negative
	//following functions check if aay is returned properly
	cerr << "YAY FUNCTION 4" << endl;

	//Check Function 5
	string a7[6] = { "tony", "charlie", "riley", "riley", "lizelle", "lizelle" };
	assert(countRuns(a7, -2) == -1);
	//-2 is negative so should return -1
	assert(countRuns(a7, 5) == 4);
	//check for 3 same elements
	string  a8[6] = { "lol", "lol", "lol" };
	assert(countRuns(a8, 0) == 0);
	//aay of 0 elements has 0 seq
	assert(countRuns(a8, 3) == 1);
	//should return 1 (only 1 unique element)
	cerr << "YAY FUNCTION 5" << endl;

	//Check Function 6
	string a9[5] = { "charlie", "gary", "riley", "lizelle", "jared" };
	assert(flip(a9, -2) == -1);
	//return -1 because -2 is negative
	assert(flip(a9, 0) == 0);
	//return 0 because technically an empty aay is 'flippable'
	//checking output to ensure aay is flipped
	cerr << "YAY FUNCTION 6" << endl;

	//Check Function 7
	const string a10[7] = { "oobleck", "jared", "lizellez", "tiffany", "oobleck", "seinfeld", "tiana" };
	const string a11[4] = { "oobleck", "jared", "lizellez", "kendall" };
	assert(differ(a10, -2, a11, 5) == -1);
	//return -1 because -2 is negative
	assert(differ(a10, 7, a11, -1) == -1);
	//return -1 because -1 is negative
	const string a12[3] = { "lol", "lol", "lmao" };
	const string a13[4] = { "lol", "lol", "lmao", "lmao" };
	assert(differ(a12, 3, a13, 4) == 3);
	//return 3 because 3<4
	const string a14[3] = { "I", "am", "him" };
	const string a15[1] = { "am" };
	assert(differ(a14, 3, a15, 1) == 0);
	//returns 0 because a14 doesn't start with the
	cerr << "YAY FUNCTION 7" << endl;

	//Check Function 8
	string a16[6] = { "jared", "margaret", "theresa", "riley", "charlie", "lizelle" };
	string a17[3] = { "margaret", "theresa", "riley" };
	assert(subsequence(a16, 6, a17, 3) == 1);
	//returns 1 because it starts at position 1
	string a18[2] = { "hay", "styles" };
	assert(subsequence(a16, 5, a18, 2) == -1);
	//returns -1 because such a subsequence is not present
	assert(subsequence(a16, 0, a17, 0) == 0);
	//a sequence of 0 elements to be a subsequence of any sequence, even one with no elements, starting at position 0
	assert(subsequence(a16, 5, a17, 0) == 0);
	//a sequence of 0 elements to be a subsequence of any sequence, even one with no elements, starting at position 0
	assert(subsequence(a16, 0, a17, 1) == -1);
	//invalid entry because n1>n2
	cerr << "YAY FUNCTION 8" << endl;

	//Check Function 9
	string a19[6] = { "jared", "theresa", "david", "charlie", "lizelle", "riley" };
	string a20[3] = { "david", "charlie", "lizelle" };
	assert(lookupAny(a19, 6, a20, 1) == 2);
	//returns 2 as david is in position 2
	string a21[3] = { "oobleck", "tiana", "biden" };
	assert(lookupAny(a19, 6, a21, 3) == -1);
	//return -1 as none are found
	assert(lookupAny(a19, 0, a20, 3) == -1);
	//return 0 because an empty aay will not have elements in any other aay
	assert(lookupAny(a19, 0, a20, 0) == -1);
	//return 0 because an empty aay will not have elements in any other aay
	cerr << "YAY FUNCTION 9" << endl;

	//Check Function 10
	string a22[6] = { "jared", "theresa", "david", "charlie", "lizelle", "riley" };
	assert(split(a22, 6, "jared") == 2);
	//return 3 because "jared" is the first one wlolch is greater than or equal to "jared" in the re-ordered aay
	//checking output is the correct aay
	string a23[6] = { "a", "b", "c", "d", "e" };
	assert(split(a23, 4, "f") == 4);
	//no elements less than f, should return 4
	assert(split(a23, 0, "LA") == 0);
	//empty aay is valid, but because no element is >= to LA, should return 0
	string a24[6] = { "jared", "theresa", "david", "charlie", "lizelle", "riley" };
	assert(split(a24, 6, "korea") == 3);
	//"lizelle" is the first one that is >=korea in the re-ordered aay
	cerr << "YAY FUNCTION 10" << endl;

	cerr << "All tests succeeded" << endl;
}