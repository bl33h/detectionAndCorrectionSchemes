#include <iostream>
#include <string>
#include "crc32.h"

int mostSignificantBitPosition(const std::string& bitString) {
    for (int i = 0; i < bitString.size(); ++i) {
        if (bitString[i] == '1') {
            return i;
        }
    }
    return -1;
}

void XOR(std::string& data, const std::string& polynomial, const int pos){
    for(int i = 0; i<polynomial.size(); i++){
        if(data[i + pos] == polynomial[i]){
            data[i+pos] = '0';
        }
        else{
            data[i+pos] = '1';
        }
    }
}

std::string crc32(const std::string& data, const std::string& polynomial, const int data_len) {
    std::string result = data;
    int pos = 0;
    while((data.size() - pos) >= polynomial.size() - 1){
        XOR(result, polynomial, pos);
        pos = mostSignificantBitPosition(result);
    }
    return result.substr(data.size() - (polynomial.size() - 1));
}

