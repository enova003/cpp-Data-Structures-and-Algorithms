#ifndef PROCESSINPUT_H
#define PROCESSINPUT_H

#include <stack>
#include <iostream>

/**
 * @brief Process a digit of input.
 * 
 * Process a single digit of input in the search for the smallest
 * number that can be formed by removing duplicates.
 * 
 * @param digit the input digit, a number in the range 0..9
 * @param digitStack  a stack of digits representign the best number found so far,
 *                    with the most significant digit of the number on the bottom
 *                    of the stack.
 * @param digitIsInStack an array indicating which digits are on the stack. 
 *                       Will be updated by this function.
 * @param remainingDigitsInInput  a count of the number of times each
 *                                digit occurs in the remaining output.
 */
void processInputDigit (int digit, std::stack<int>& digitStack,
    bool* digitIsInStack, const int* remainingDigitsInInput);

/**
 * @brief Print the number on the stack to out.
 * 
 * @param out the stream to which to print.
 * @param digitStack a stack of digits, most significant on the bottom.
 */
void print (std::ostream& out, std::stack<int>& digitStack);


#endif


