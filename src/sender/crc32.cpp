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
    for(int i = 0; i<32; i++){
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
    while((data.size() - pos) >= 32){
        XOR(result, polynomial, pos);
        pos = mostSignificantBitPosition(result);
    }
    return result.substr(data_len, 32);
}

int main() {
    std::string original_data = "11011"; 
    int initial_pos = original_data.size() - 1;
    std::string data = original_data.append(32,'0');
    std::string polynomial = "10000010011000001000111001011000"; 

    std::string checksum = crc32(data, polynomial, initial_pos);
    std::string crc = original_data + checksum;
    std::cout << "CRC32: " << crc << std::endl;

    return 0;
    
}
