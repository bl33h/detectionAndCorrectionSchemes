#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <cstring>

#define PORT 65432

// add a parity bit
std::string addParityBit(const std::string& data) {
    int count = std::count(data.begin(), data.end(), '1');
    return data + (count % 2 == 0 ? '0' : '1');
}

// main function
int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    std::string binaryString;

    // socket creation
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "!error creating socket\n";
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "!error invalid address/ address not supported\n";
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "!error connection failed\n";
        return -1;
    }

    // message without parity bit
    std::cout << "-> enter a binary message: ";
    std::cin >> binaryString;
    std::string messageWithParity = addParityBit(binaryString);

    // message with parity bit sent to receiver
    send(sock, messageWithParity.c_str(), messageWithParity.size(), 0);
    std::cout << "-> message sent: " << messageWithParity << std::endl;

    close(sock);
    return 0;
}