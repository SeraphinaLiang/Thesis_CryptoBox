# interact with crypto core on local machine

import gmpy2
import requests


# core running on http://localhost:3000
# solid app running on http://localhost:8080


def reset_parameter(n):
    res = requests.get("http://localhost:3000/reset" + str(n))
    if res.text == "0K":
        print("parameter reset success")


def start():
    res = requests.get("http://localhost:3000/init")
    if res.text == "0K":
        print("core initialized success")


def decrypt_one_bit():
    # the to be decrypt text need to put in cin.txt
    res = requests.get("http://localhost:3000/decrypt")
    if res.text == "1":
        return 1
    if res.text == "0":
        return 0
    # print(res.text)


# encrypt sequence '101011100...', return the encrypted sequence array
def encrypt_sequence(sequence):
    # length = len(identifier)
    encrypted_sequence = []

    for numero in sequence:
        if numero == '1':
            c = encrypt_one_bit_one()
            encrypted_sequence.append(c)
            encrypted_sequence.append("\n")
        elif numero == '0':
            c = encrypt_one_bit_zero()
            encrypted_sequence.append(c)
            encrypted_sequence.append("\n")

    return encrypted_sequence


def encrypt_one_bit_one():
    # c = gmpy2.mpz()
    res = requests.get("http://localhost:3000/encrypt1")
    # print(res.text)
    if res.text == "0K":
        with open("../ctext/one.txt", "r") as one:
            str = one.readline().strip()
            # c = gmpy2.mpz(str)
            # print(str)
    return str
    # return c


def encrypt_one_bit_zero():
    # c = gmpy2.mpz()
    res = requests.get("http://localhost:3000/encrypt0")
    # print(res.text)
    if res.text == "0K":
        with open("../ctext/zero.txt", "r") as zero:
            str = zero.readline().strip()
            # c = gmpy2.mpz(str)
            # print(str)
    # return c
    return str


'''-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~ USED BY CLIENT -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-
WARNING 
Every time the Core starts, either start() or reset_parameter(n) 
needed to be execute to initialize the Core layer 
'''

if __name__ == "__main__":
    ''' initialize the Core using stored keys and parameter
    '''
    start()

    ''' reset the parameter for the Core and generate new private/public key pair
        INPUT : 0 , 1 , 2 , 3
    '''
    # reset_parameter(0)
    #print(decrypt_one_bit())
