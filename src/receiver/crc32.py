def XOR(data, poly, pos):
    data_list = list(data)
    for x in range(len(poly)):
        if data_list[pos + x] == poly[x]:
            data_list[pos + x] = '0'
        else:
            data_list[pos+x] = '1'
    return ''.join(data_list)
    
def mostSignificantBit(data):
    for x in range(len(data)):
        if data[x] == '1':
            return x
    else:
        return -1
        
def CRC32(data, poly):
    pos = 0
    while ((len(data) - pos) >= len(poly)):
        data = XOR(data, poly, pos)
        pos = mostSignificantBit(data)
        if pos == -1: break
    checksum = data[-(len(poly)-1):]
    f = checksum.find('1')
    return f == -1, data
    

if __name__ == "__main__"   :
    received = "1101001000000000000000000000000010110"
    poly = "111100000000000000000000000000001"
    flag, result = CRC32(received, poly)
    if not flag:
        print(f"Se encontró un error. La cadena resultante es: {result}")
    else: 
        print(f"Mensaje recibido correctamente. Cadena resultante: {result}")
    