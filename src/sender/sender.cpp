#include <iostream>
#include <string>
#include <cstring>
#include <bitset>
#include <sstream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <algorithm>
#include "crc32.h"

#pragma comment(lib, "ws2_32.lib") // Link with Winsock library

#define PORT 65432

std::string toBinaryASCII(const std::string &message) {
    std::ostringstream oss;
    for (char c : message) {
        oss << std::bitset<8>(c);
    }
    return oss.str();
}

std::string addParityBit(const std::string& data) {
    int count = std::count(data.begin(), data.end(), '1');
    return data + (count % 2 == 0 ? '0' : '1');
}

int main() {
    // Initialize Winsock
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        return 1;
    }

    // Create socket
    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd == INVALID_SOCKET) {
        std::cerr << "Failed to create socket: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Set up server address
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    if (connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Failed to connect to server: " << WSAGetLastError() << std::endl;
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    std::string scheme;
    std::cout << "Enter the scheme to use: \n 1. CRC32 \n 2. Hamming \n";
    std::cin >> scheme;
    

    std::string inputMessage;   
    std::cout << "Enter the message to send: \n";
    std::cin >> inputMessage;
    

    std::string asciiMessage = toBinaryASCII(inputMessage);

    std::string finalMessage;
    if(scheme == "1"){
        std::cout << "Using CRC32 scheme\n";
        // Calculate CRC32 checksum
        std::string polynomial = "111100000000000000000000000000001"; 
        std::string data = asciiMessage;
        data.append(polynomial.size() - 1, '0');
        std::string crc32Checksum = crc32(data, polynomial, inputMessage.size());
        finalMessage = asciiMessage + crc32Checksum;
    }
    else if(scheme == "2"){
        std::cout << "Using Hamming scheme\n";
        finalMessage = addParityBit(asciiMessage);
    }
    else{
        std::cout << "Invalid scheme\n";
        return 1;
    }

    
    if (send(sockfd, finalMessage.c_str(), finalMessage.length(), 0) == SOCKET_ERROR) {
        std::cerr << "Failed to send message: " << WSAGetLastError() << std::endl;
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }
    std::cout << "-> message sent: " << finalMessage << std::endl;

    // Close socket
    closesocket(sockfd);
    WSACleanup();

    return 0;
}