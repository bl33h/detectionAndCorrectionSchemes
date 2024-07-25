/*---------------------------------------------------------------------------
Copyright (C), 2024-2025, bl33h, Mendezg1
@author Sara Echeverria, Ricardo Mendez
FileName: hamming.cpp
@version: I
Creation: 23/07/2024
Last modification: 25/07/2024
------------------------------------------------------------------------------*/

#include <iostream>
#include <string>

int main() {
    std::string binaryString;
    std::cout << "-> enter a binary message: ";
    std::cin >> binaryString;

    // count the number of 1s in the string
    int count = 0;
    for (char c : binaryString) {
        if (c == '1') {
            count++;
        }
    }

    // add a parity bit at the end
    if (count % 2 == 0) {

        // parity is already even, add 0
        binaryString += '0';
    } else {

        // make parity even, add 1
        binaryString += '1';
    }

    std::cout << "-> message with parity bit: " << binaryString << std::endl;

    return 0;
}