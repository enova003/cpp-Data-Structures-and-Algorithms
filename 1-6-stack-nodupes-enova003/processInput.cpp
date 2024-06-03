#include "processInput.h"
using namespace std;

void processInputDigit (int digit, std::stack<int>& digitStack, 
    bool* digitIsInStack, const int* remainingDigitsInInput)
{
    if (!digitIsInStack[digit])
    {
        while (!digitStack.empty() && digitStack.top() > digit && 
                remainingDigitsInInput[digitStack.top()] > 0)
        {
            digitIsInStack[digitStack.top()] = false;
            digitStack.pop();
        }
        digitStack.push(digit);
        digitIsInStack[digit] = true;
    }
}

void print (std::ostream& out, std::stack<int>& digitStack)
{
    stack<int> tempStack;
    while (!digitStack.empty())
    {
        tempStack.push(digitStack.top());
        digitStack.pop();
    }

    while (!tempStack.empty())
    {
        out << tempStack.top();
        digitStack.push(tempStack.top());
        tempStack.pop();
    }
}