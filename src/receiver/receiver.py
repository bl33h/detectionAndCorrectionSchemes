import socket
from crc32 import CRC32

HOST = '127.0.0.1'  # llocalhost interface address
PORT = 65432        # listening port
POLY = "111100000000000000000000000000001"
def receive_data():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    s.bind((HOST, PORT))

    # Listen for incoming connections
    s.listen(1)

    print("Listening for incoming connections...")

    while True:
        # Accept a connection from a client
        conn, addr = s.accept()
        print("Connected to", addr)

        # Receive the data from the client
        data = conn.recv(1024)
        data_str = data.decode('utf-8')

        scheme = input("Enter the scheme used for error detection (1 for Hamming, 2 for CRC32): ")
        
        if scheme == "1":
            #Hamming
            pass
        elif scheme == "2":
            
            # Calculate the CRC32 checksum of the decoded data
            flag, result = CRC32(data_str, POLY)

            # Check if the checksum is correct
            if flag:
                print("Checksum is correct.")
                relevant_data = data_str[:len(data_str) - len(POLY)+1]

                chars = ''.join(chr(int(relevant_data[i:i+8], 2)) for i in range(0, len(relevant_data), 8))
                print("Original message:", chars)
                break
            else:
                print(f"Checksum is incorrect. Chain: {result}")
                break
        else:
            print("Invalid scheme entered.")
        
        # Close the connection
        conn.close()

# Start receiving data
receive_data()