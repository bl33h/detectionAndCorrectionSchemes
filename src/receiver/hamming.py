# Copyright (C), 2024-2025, bl33h, Mendezg1
# FileName: hamming.py
# Author: Sara Echeverria, Ricardo Mendez
# Version: I
# Creation: 25/07/2024
# Last modification: 25/07/2024
        
def calculateParity(bits):
    count = sum(1 for bit in bits if bit == '1')
    return '1' if count % 2 != 0 else '0'

def hammingCheck(receivedMessage):
    data = receivedMessage[:-1]
    receivedParity = receivedMessage[-1]
    calculatedParity = calculateParity(data)
    
    if receivedParity != calculatedParity:
        return "!error detected: the message is discarded."
    else:
        chars = ''.join(chr(int(data[i:i+8], 2)) for i in range(0, len(data), 8))
        return f"✓message received correctly: {chars}"