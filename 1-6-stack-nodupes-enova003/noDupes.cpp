#include "processInput.h"
#include <string>
#include <iostream>
#include <fstream>
#include <stack>
#include <algorithm>

using namespace std;

void noDuplicates(const string& input)
{
    bool isInStack[10]; // inInStack[i] == true iff digit is already on the stack
    int remainingInInput[10]; // how many occurrences of each digit remain unprocessed in the input?
    fill_n (isInStack, 10, false);
    fill_n (remainingInInput, 10, 0);
    
    // Count the number of times each digit occurs in the input
    for (char c: input) {
        int digit = c - '0';
        ++remainingInInput[digit];
    }

    stack<int> digitStack;

    // Process each character of the input
    for (char c: input) {
        int digit = c - '0';
        --remainingInInput[digit];
        processInputDigit (digit, digitStack, isInStack, remainingInInput);
    }

    // Print the answer
    print (cout, digitStack);
    cout << endl;

}

int main (int argc, char** argv)
{
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " number\n"
             << "  or   " << argv[0] << " filepath" << endl;
        return -1;
    }
    string input (argv[1]);

    if (input.find_first_not_of("0123456789") != string::npos)
    {
        // Input is not a number - assume it is a file name and
        // read the number from there
        ifstream in(input);
        in >> input;
        in.close();
    }
    noDuplicates(input);
}