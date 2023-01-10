#include <iostream>
#include <string>
using namespace std;

int main()
{
	/*This section of code outputs the prompts for
	the user, and collects the tax payers name, taxable income, 
	occupation, and number of children*/
	cout << "Name: ";
	string payerName;														
	getline(cin, payerName);

	cout << "Taxable Income: ";
	double taxIncome;
	cin >> taxIncome;
	cin.ignore(10000, '\n');

	cout << "Occupation: ";
	string payerJob;
	getline(cin, payerJob);

	cout << "Number of children: ";
	int numChild;
	cin >> numChild;
	cout << "---" << endl;

	/* assigns tax rates and tax brackets to variables
	and assigns the caluclations for taxes to reult variables*/
	double rateLow = 0.04;
	double taxBrack1 = 55000;
	double taxBrack2 = 125000;
	double childReduct = numChild * 200;

	double result1 = taxIncome * rateLow - childReduct;
	double result2 = ((taxIncome - 55000) * 0.07) + 2200 - childReduct;
	double result3 = ((taxIncome - 125000) * 0.093) + 7100;
	double specialTax = ((taxIncome - 55000) * 0.05) + 2200 - childReduct;

	cout.setf(ios::fixed);
	cout.precision(2);

	/* first tests for any errors, and the output depends on the first detected error
	then tests to see if tax is below 0, if it is then the output just states
	taxes owed are $0. If all conditions are satisfied, then the results are calculated*/
	if (payerName == "")
		cout << "You must enter a name" << endl;
	else if (taxIncome < 0)
		cout << "The taxable income must not be negative" << endl;				// if empty string, is it okay if code doesnt move on?
	else if (payerJob == "")
		cout << "You must enter an occupation" << endl;
	else if (numChild < 0)
		cout << "The number of children must not be negative" << endl;
	else if (result1 <= 0)												 //|| result2 <= 0 || result3 <= 0) (maybe add back)
		cout << payerName << " would pay $0" << endl;
	else if (taxIncome >= 0 && taxIncome <= taxBrack1)
		cout << payerName << " would pay $" << result1 << endl;
	else if (taxIncome > taxBrack1 && taxIncome <= taxBrack2 && payerJob == "nurse" || payerJob == "teacher")
		cout << payerName << " would pay $" << specialTax << endl;
	else if (taxIncome > taxBrack1 && taxIncome <= taxBrack2)											// confused, one nurse/teacher doesnt work        
		cout << payerName << " would pay $" << result2 << endl;											// if put after, and vice versa
	else if (taxIncome > 125000)
		cout << payerName << " would pay $" << result3 << endl;
}                                                                              