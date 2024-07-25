# Copyright (C), 2024-2025, bl33h, Mendezg1
# FileName: hamming.py
# Author: Sara Echeverria, Ricardo Mendez
# Version: I
# Creation: 25/07/2024
# Last modification: 25/07/2024

def calculateParity(bits):
    count = sum(1 for bit in bits if bit == '1')
    
    # even parity: if count is odd, parity is 1, otherwise it's 0
    return '1' if count % 2 != 0 else '0'

def hammingCheck():
    # request the message from the user
    receivedMessage = input("-> enter the message (frame + parity bit): ")
    
    # extract the frame and the received parity bit
    data = receivedMessage[:-1]
    receivedParity = receivedMessage[-1]
    
    # calculate the parity bit for the string
    calculatedParity = calculateParity(data)
    
    # check if the parity bits match
    if receivedParity != calculatedParity:
        print("!error detected: the message is discarded.")
    else:
        # display the message without the parity bit
        print(f"✓message received correctly: {data}")

hammingCheck()