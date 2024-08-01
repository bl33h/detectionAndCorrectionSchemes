#ifndef CRC32_H
#define CRC32_H

#include <string>

// Function declarations
std::string crc32(const std::string& data, const std::string& polynomial, const int data_len);
void XOR(std::string& data, const std::string& polynomial, const int pos);
int mostSignificantBitPosition(const std::string& data);

#endif // CRC32_H