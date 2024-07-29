import socket

HOST = '127.0.0.1'  # llocalhost interface address
PORT = 65432        # listening port

def calculateParity(bits):
    count = sum(1 for bit in bits if bit == '1')
    return '1' if count % 2 != 0 else '0'

def hammingCheck(receivedMessage):
    data = receivedMessage[:-1]
    receivedParity = receivedMessage[-1]
    calculatedParity = calculateParity(data)
    if receivedParity != calculatedParity:
        print("!error detected: the message is discarded.")
    else:
        print(f"✓message received correctly: {data}")

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    print("• listening on [{}:{}]".format(HOST, PORT))
    conn, addr = s.accept()
    with conn:
        print("• connected by: ", addr)
        while True:
            data = conn.recv(1024)
            if not data:
                break
            data_str = data.decode('utf-8')
            print("• data received: ", data_str)
            hammingCheck(data_str)
