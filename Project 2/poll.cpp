#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

//*************************************
//  isValidUppercaseStateCode
//*************************************

// Return true if the argument is a two-uppercase-letter state code, or
// false otherwise.

bool isValidUppercaseStateCode(string stateCode)
{
    const string codes =    //given code 
        "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
        "LA.ME.MA.MD.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
        "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2 &&
        stateCode.find('.') == string::npos &&  // no '.' in stateCode
        codes.find(stateCode) != string::npos);  // match found
}

string turnUpperCase(string pollData)   //turns all alphabet characters in string uppercase
{
    string newupper = "";
    for (int i = 0; i != pollData.size(); ++i)
    {
        newupper += toupper(pollData.at(i));    //used to make isValidPollString easier (only check for uppercase)
    }
    return newupper;
}

bool isValidPollString(string pollData)
{
    int pos = 0;    //sets position in pollData to 0
    pollData = turnUpperCase(pollData);
    if (!isValidUppercaseStateCode(pollData.substr(pos, 2))) {
        return false; //returns false if base case (first two letters) are not a state code 
    }
    pos = 2;
    while (pos < pollData.length()) {   //starting to increment through string after verifying state code
        int threeCheck = 0; 
        if (pos == pollData.length() - 1) { //while loop reaches end of 2 letter state forecast
            return true;
        }
        for (int i = 0; i < 3; i++) {   //checks to see if 3 integers are in a row
            if (pos < pollData.length()) {

                if (isdigit(pollData[pos])) { //checks if pollData[pos] is an digit, and increments pos and threeCheck
                    pos++;
                    threeCheck++;
                }
            }
            else
                break;
        }
        if (threeCheck > 2) //if three integers in a row it is not a valid poll data string
            return false;
        if (pollData[pos] == ',') { //end/beginning of state forecast
            if (isValidUppercaseStateCode(pollData.substr(++pos, 2))) { //checks state code 
                pos += 2;                                               //(first 2 elements of state forecast)
                continue;
            }
        }
        if (!isdigit(pollData[pos]) && !isalpha(pollData[pos])) {   //if its not a digit/alpha following statecode
            return false;                                           //return false
        }
        if (pos >= 2) {
            for (int j = 0; j < 3; j++) {   //checks to see if 3 alphabet characters are in a row
                if (pos < pollData.length()) {
                    if (isalpha(pollData[pos]) && isalpha(pollData[pos - 1]) && isalpha(pollData[pos - 2])) { 
                        return false; //checks if pollData[pos] is an digit, and increments pos and threeCheck
                    }
                }
            }
        }
        if (isdigit(pollData[pos]) || isalpha(pollData[pos])) { //  keep checking if digit or alpha
            pos++;
            continue;
        }
        else { //if element is any other character, return false;
            return false;
        }
    }
    return true; //return true if is valid poll string
}

int countSeats(string pollData, char party, int& seatCount) {
    if (!isValidPollString(pollData)) {
        return 1;
    }
    if (!isalpha(party)) {
        return 2;
    }
    int votes = 0;
    for (int i = 0; i < pollData.length(); i++) { //loop through pollData
        if (i > 0) {
            if ((tolower(pollData[i]) == tolower(party)) && (isdigit(pollData[i - 1]))) { // would check if is digit outside of index
                int partyIndex = i;
                int voteLength = 0;
                while (isdigit(pollData[--partyIndex])) {
                    voteLength++; //length of vote count instance
                }
                votes += (stoi(pollData.substr(i - voteLength, voteLength))); //adding votes for each party instance
            }
            else {
                continue;
            }
        }
    }
    seatCount = votes; //set seatcount to votes
    return 0;
}



int main()
{
    assert(isValidPollString("CT5D,NY9R16D1I,VT,ne3r00D"));
    assert(isValidPollString("CT5D"));
    assert(isValidPollString("CA,ca"));
    assert(isValidPollString("MI"));
    assert(isValidPollString("NY10R22D1I,VT1R,NJ19D5R4D,Mi6R"));
    assert(!isValidPollString("KS4R, NV3D1R"));
    assert(!isValidPollString("CT5+D,NY9R16D1I,VT,ne3r00D"));
    assert(!isValidPollString("cT555D,NY9R16D1I,VT,ne3r00D"));
    assert(!isValidPollString("cT5D,NY999R1D1I,VT,ne3r00D"));
    assert(!isValidPollString("cT5D,NY9R6D1I,VT,ne3r100D"));
    assert(!isValidPollString("cT5D,NYc9R6D1I,VT,ne3r100D"));
    assert(!isValidPollString("ZT5D,NY9R16D1I,VT,ne3r00D"));
    assert(!isValidPollString(" "));
    assert(!isValidPollString("KS 4R"));
    assert(!isValidPollString("2d"));
    assert(!isValidPollString(",cT52D,NY19R6D13I,VT,ne32r10078888D"));

    int seats;
    seats = -999;
    assert(countSeats("CT5D,NY9R9D1I,VT,ne3r00D", 'd', seats) == 0 && seats == 14);
    seats = -999;
    assert(countSeats("CT5D,NY9R16D1I,VT,ne3r00D", 'k', seats) == 0 && seats == 0);
    seats = -999;
    assert(countSeats("CT5D,NY9R16D1I,VT,ne3r00D", '+', seats) == 2 && seats == -999);
    seats = -999;
    assert(countSeats("CT05D,NY9R16D1I,VT,ne3r10D", 'd', seats) == 0 && seats == 31);
    seats = -999;
    assert(countSeats("CT05D,NY9R10D1I,VT,ne3r20D", 'd', seats) == 0 && seats == 35);
    seats = -999;
    assert(countSeats("OR01D", 'd', seats) == 0 && seats == 1);
    seats = -999;
    assert(countSeats("OR10D", 'd', seats) == 0 && seats == 10);
    seats = -999;
    assert(countSeats(" ", 'd', seats) == 1 && seats == -999);
    seats = -999;
    assert(countSeats(" ", '+', seats) == 1 && seats == -999);
    seats = -999;
    assert(countSeats("CA", 'c', seats) == 0 && seats == 0);
    seats = 0;
    assert(countSeats("CT511D,NY9R16D1I,VT,ne3r00D", 'd', seats) == 1 && seats == -0);
    seats = -999;
    assert(countSeats("CT5D,NY9R176D1I,VT,ne3r00D", '+', seats) == 1 && seats == -999);
    seats = -100;
    assert(countSeats("CT5D,NY9R76D1I,VT,ne223r00D", ',', seats) == 1 && seats == -100);
    seats = -999;
    seats = 3;
    assert(countSeats("/CT5D,NY9R76D1I,VT,ne27r10D", '-', seats) == 1 && seats == 3);
    seats = -999;
    assert(countSeats("w", 'W', seats) == 1 && seats == -999);

    cerr << "AYYYEEE";
}