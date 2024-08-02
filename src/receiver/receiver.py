import socket
from crc32 import CRC32
from hamming import hammingCheck

HOST = '127.0.0.1'  # localhost interface address
PORT = 65432        # listening port
POLY = "111100000000000000000000000000001"

def receive_data():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((HOST, PORT))

    # listen for incoming connections
    s.listen(1)
    print("listening for incoming connections...")

    while True:
        # accept a connection from a client
        conn, addr = s.accept()
        print("• connected to: ", addr)

        # receive the data from the client
        data = conn.recv(1024)
        data_str = data.decode('utf-8')

        scheme = input("-> enter the scheme used for error detection (1 for Hamming, 2 for CRC32): ")
        
        if scheme == "1":
            print("--- Using Hamming scheme ---")
            result = hammingCheck(data_str)
            print(result)
            
        elif scheme == "2":
            # calculate the CRC32 checksum of the decoded data
            flag, result = CRC32(data_str, POLY)

            # check if the checksum is correct
            if flag:
<<<<<<< HEAD
                print("✓checksum is correct.")
=======
                print("Checksum is correct.")
>>>>>>> eafec9cd779647d6d18d09a118540c9b8b15dbc7
                relevant_data = data_str[:len(data_str) - len(POLY)+1]

                chars = ''.join(chr(int(relevant_data[i:i+8], 2)) for i in range(0, len(relevant_data), 8))
                print("• original message:", chars)
                break
            else:
<<<<<<< HEAD
                print(f"!checksum is incorrect. chain: {result}")
=======
                print(f"Checksum is incorrect. Chain: {result}")
>>>>>>> eafec9cd779647d6d18d09a118540c9b8b15dbc7
                break
        else:
            print("!invalid scheme entered.")
        
<<<<<<< HEAD
=======
        # Close the connection
>>>>>>> eafec9cd779647d6d18d09a118540c9b8b15dbc7
        conn.close()

receive_data()