#include <iostream>
#include <string>

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

int main() {
    std::string original_data = "11010"; 
    std::string polynomial = "111100000000000000000000000000001"; 
    int initial_pos = original_data.size() - 1;
    std::string data = original_data;
    data.append(polynomial.size() - 1, '0');
    

    std::string checksum = crc32(data, polynomial, initial_pos);
    std::string crc = original_data + checksum;
    std::cout << "CRC32: " << crc << std::endl;

    // Result = CRC32: 1101001000000000000000000000000010110
    return 0;
}
