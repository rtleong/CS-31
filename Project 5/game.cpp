#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 6262)
#include "utilities.h"
#include <iostream>
#include <cstring>
#include <cctype>
//using namespace std; //got some type of library error, so the online solution was just to specify std::

//const char WORDFILENAME[] = "C:/Users/rileo/OneDrive/Desktop/CS31/game/smallwords.txt";
const char WORDFILENAME[] = "C:/Users/rileo/OneDrive/Desktop/CS31/game/words.txt";
// Windows users:  Use / instead of \ for pathname separators.


int playOneRound(const char words[][MAXWORDLEN + 1], int nWords, int wordnum) { //wordnum is the random integer 
	if (nWords <= 0 || wordnum < 0 || wordnum >= nWords) {					  //eg. 2940
		return -1;															  // nWords is #of words in array
	}

	int gold = 0;	//defines gold and silvers outside of loops so they dont reset between rounds
	int silver = 0;
	int userAtt = 0; //user attempts
	const char replaceGold = '-';	//if gold is found, replace with non alphabet character
	char check[MAXWORDLEN + 1];		//the hidden word (copied words[wordnum] to improve readability)
	char inputWord[100];
	int counter = 0;	//variable to count total words in array and compare to nWords
	strcpy(check, words[wordnum]);	//gives the hidden word a easy to use variable name
	//std::cerr << check << '\n';
	//while (check < counter){
	for (;;) {	//always want to enter this for loop
		std::cout << "Probe word: ";
		std::cin.getline(inputWord, 100);
		//std::cin.get(inputWord, 100, '\n')
		bool dontReset = true;	//boolean that will determine if user word is in array
		if (strlen(inputWord) < MINWORDLEN || strlen(inputWord) > MAXWORDLEN) {	//if word is too long 
			std::cout << "Your probe word must be a word of 4 to 6 lower case letters." << '\n';
			continue;
		}
		/*for (int i = 0; i < nWords; i++) {
			if (!(islower(inputWord[i]))) {
				dontReset = false;
				std::cout << "Your probe word must be a word of 4 to 6 lower case letters." << '\n';
				counter++;
				break;
			}
		}*/
		for (int i = 0; inputWord[i] != '\0'; i++) {	//if there isn't all lower case alphabet characters
			if (!islower(inputWord[i])) {				//output the prompt
				dontReset = false;
				std::cout << "Your probe word must be a word of 4 to 6 lower case letters." << '\n';
				break;
			}
		}
		if (dontReset == false) {	//next iteration if we found anything BUT a lowercase letter in user input
			continue;
		}
		dontReset = false;	//assigns boolean to false. If boolean stays false it means the input word matches
		for (int i = 0; i < nWords; i++) { // no words in the filled array of words
			if (strcmp(words[i], inputWord) == 0) {	//if any word in the array matches user input, return true
				dontReset = true;
			}
		}
		for (int i = 0; i < nWords; i++) {
			if (strcmp(words[i], inputWord) == 0) {
				counter++;	//uses counter function to check if ALL words have been checked, if all have then 
				dontReset = true;//continue
			}
			if (dontReset == false) {
				std::cout << "I don't know that word." << '\n';
				break;	//enter next iteration (ask for probe word) if its not a valid input word
			}
		}
		if (dontReset == false) {//check if bool is false if it is continue to ask probe word again
			continue;
		}
		userAtt++;	//If none of these statements execute, word is VALID so add one to attempts

		if (strcmp(inputWord, check) == 0) {
			break;	//if the input word matches the hideden word break out of loop and end playOneRound function
		}
		gold = 0;	//sets gold count to 0 (acts as a reset between probe guesses as well)
		silver = 0;	//sets silver count to 0 (acts as a reset between probe guesses as well)
		char tempHidden[MAXWORDLEN + 1];//sets up array to copy constant array(s) into
		char tempInput[MAXWORDLEN + 1];//these are reset in every iteration of the function
		strcpy(tempHidden, check);
		strcpy(tempInput, inputWord); //copies array as workaround to the constant char array declared above

		for (int i = 0; tempHidden[i] != '\0' && tempInput[i] != '\0'; i++) {
			if (tempHidden[i] == tempInput[i]) {	//if the character of input word equals the hidden word
				counter++;
				tempHidden[i] = replaceGold;		//at corresponding positions of both arrays add one to gold
				tempInput[i] = replaceGold;
				gold++;
				}
			}																	
		for (int i = 0; tempInput[i] != '\0'; i++) {
			//if (replaceGold == tempInput[i])
			if (tempInput[i] != replaceGold) {	//if its already gold, don't count letter as silver
			//if (tempInput[i] < tempHidden[i] && tempInput[i] != replaceGold)
				for (int j = 0; tempHidden[j] != '\0'; j++) {
					if (tempHidden[j] != replaceGold && tempHidden[j] == tempInput[i]) {	//letter is in ANY pos
						counter++;
						tempHidden[j] = replaceGold;										//of hidden word
						tempInput[i] = replaceGold;	//replacing words with silver letters
						silver++;//add one to silver count for every char meeting conditions
					}
				}
			}
		}
		std::cout << "Golds: " << gold << ", Silvers: " << silver << '\n';	//output statements
	}
	return userAtt;	//return the attempts the user made to the function
}




int main()
{
	std::cout.setf(std::ios::fixed);	//adheering to spec (average must go to hundredths place)
	std::cout.precision(2);
	const int MAXWORDS = 10000;	//must be over 9000
	const int MAXWORDLEN = 6;	
	double allAttempts = 0;	//holds total attempts user made not including invaild inputs
	int minimum = 0;	//integers to hold minimum and maximum values
	int maximum = 0;

	char wordList[MAXWORDS][MAXWORDLEN+1];	
	int nmWords = getWords(wordList, MAXWORDS, WORDFILENAME);	//reads in arary

	if (nmWords < 1) {
		std::cout << "No words were loaded, so I can't play the game." << '\n';	//no words taken from text file
		return 0;													// end program
	}
	int rounds;	//holds value for how many rounds user wants to play
	if (nmWords >= 1 || nmWords <= MAXWORDS) {
		std::cout << "How many rounds do you want to play? ";
		std::cin >> rounds;	//ask how many rounds player wants to play
		std::cin.ignore(10000, '\n'); //gets rid of newline character
		if (rounds < 0) {
			std::cout << "The number of rounds must be positive." << '\n';	//if negative number entered, prompt for +
		}
		std::cout << '\n';
	}
	for (int i = 1; i <= rounds; i++){
		std::cout << "Round " << i << '\n'; //should give round 1, then 2, then 3, forever
		int random = randInt(0, nmWords - 1);
		std::cout << "The hidden word is " << strlen(wordList[random]) << " letters long." << '\n';
		int userAttempts = playOneRound(wordList, nmWords, random);	//putting return value of function into an int
		
		if (userAttempts == 1) {
			std::cout << "You got it in 1 try." << '\n';	//singular version of try for 1 attempt
		}
		else {
			std::cout << "You got it in " << userAttempts << " tries." << '\n';	//pluralizes try into tries
		}

		allAttempts += userAttempts;	//Add a users attempt to a total running # of atts (No reset btwn rwnds)
		if (i == 1) {
			maximum = userAttempts;	//if only played one round, max and min are just for one round
			minimum = userAttempts;
		}
		else {
		/*bool maxOp = false;
		if (userAttempts > maximum) {
			maxOp = true;
		}
		if (maxOp == true) {
			maximum = UserAttempts;
		}*/
			if (userAttempts > maximum) {
				maximum = userAttempts;
			}
			if (userAttempts < minimum) { //If playing multiple rounds, minimum and maximum must look at all 
				minimum = userAttempts;	  //rounds played. Keep checking max and min if a value fits it
			}
		}
		std::cout << "Average: " << allAttempts / i << ", minimum: " << minimum << ", maximum: " << maximum << '\n';
		std::cout << '\n';	//output '\n' after every round. does after end game as well
	}
}


//playOneRound(wordList, 2, 1);	//sample test call


	/*if (nWords == 2)
	{
		cout << "getWords successfully found the file and read its two words." << '\n';
		cout << "You're ready to start working on Project 5." << '\n';
	}
	else if (nWords == -1)
		cout << "The path to your file of words is probably incorrect" << '\n';
	else
		cout << "getWords found the file, but loaded " << nWords << " words instead of 2" << '\n';*/