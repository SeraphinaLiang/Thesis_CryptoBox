# Tools
from connect_core import encrypt_sequence, decrypt_one_bit


# decrypt a file
# INPUT   a path e.g "../file/encrypted_id/00110011.txt","../decrypt_result/origin.txt"
# OUTPUT  the decrypted result of the input file, in "decrypt_result/result.txt"
def decrypt_sequence(filename):
    results = []
    with open(filename, "r") as f:
        lines = f.readlines()
    for line in lines:
        with open("../decrypt_text/cin.txt", "w") as cin:
            cin.write(line)
            result = decrypt_one_bit()
            results.append(result)
    with open("../decrypt_result/result.txt", "w") as r:
        r.write(str(results))
        #print(results)

    r.close()
    f.close()
    cin.close()


# encrypt the file content given the filename
'''assume the file only have one line for simplicity'''
# INPUT:  filename e.g "00110011.txt" , under dir '/file'
# OUTPUT:  generate "encrypted_file/00110011.txt", the encrypted bytes sequence of the file content
def encrypt_file(filename):
    with open("../file/" + filename, "r") as f:
        content = f.readline()
    bytes = ' '.join(format(x, 'b') for x in bytearray(content, 'utf-8'))
    encrypted_bytes = encrypt_sequence(bytes)
    with open("../file/encrypted_file/" + filename, "w") as file:
        file.writelines(encrypted_bytes)
        file.close()
    # print(str)
    # print(bytes)


# encrypt the file identifier given the filename and the length of identifier
# INPUT : filename e.g "10001000.txt" under dir /file, length of identifier e.g 8
# OUTPUT: generate "encrypted_id/10001000.txt", the encrypted identifier
def encrypt_identifier(filename, n):
    # print(filename[0:n])
    encrypted_bytes = encrypt_sequence(filename[0:n])
    with open("../file/encrypted_id/" + filename, "w") as file:
        file.writelines(encrypted_bytes)
        file.close()



'''-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~ USED BY CLIENT -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-
WARNING before using
1.  start and initialize the Core layer (refer to connect_core.py)
2.  the client file must be copy into the '/file' directory, the filename must be the plaintext identifier
3.  the client file must be in .txt format, and only have one line of string, and hopefully less than 5 characters
'''

if __name__ == "__main__":
    '''To encrypt file content
       INPUT : the plaintext identifier + ".txt"
    '''
    encrypt_file("10111100.txt")

    '''To encrypt file identifier
       INPUT : the plaintext identifier + ".txt", the length of the identifier
    '''
    encrypt_identifier("10111100.txt", 8)

    # decrypt_sequence("../decrypt_result/origin.txt")
    # decrypt_sequence("../file/encrypted_id/00110011.txt")
