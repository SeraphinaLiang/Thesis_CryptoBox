# API called by Solid server

import requests
import json
from tools import decrypt_sequence


# post secure request to the SOLID APP
def secure_request(identifier_plaintext):
    pk0 = get_pk0()
    with open("../file/encrypted_id/" + identifier_plaintext + ".txt", "r") as f:
        encrypted_id = f.readlines()
    res = requests.post(url="http://localhost:8080/secure",
                        json={"encryptedIdentifier": encrypted_id,
                              "pk0": pk0
                              })
    result = res.json()
    # print(result)
    with open("../decrypt_result/origin.txt", "w") as fp:
        for item in result:
            fp.write(item + "\n")
    fp.close()
    decrypt_sequence("../decrypt_result/origin.txt")
    decode_file()


# decode the binary file '../decrypt_result/result.txt', generate decode text "../decrypt_result/decode_result.txt"
def decode_file():
    with open("../decrypt_result/result.txt", "r") as bits:
        undecode = bits.readline()
        bits.close()
    undecode = undecode.replace('[', '')
    undecode = undecode.replace(']', '')
    undecode = undecode.replace(',', '')
    undecode = undecode.replace(' ', '')
    s = [undecode[i:i + 7] for i in range(0, len(undecode), 7)]
    full = []
    for st in s:
        k = st.zfill(8)
        full.append(k)
    decode_result = []
    for f in full:
        g = ('%x' % int(f, 2))
        c = chr(int("0x"+g, 0))
        decode_result.append(c)
    with open("../decrypt_result/decode_result.txt", "w") as res:
        for cc in decode_result:
            res.write(cc)
    res.close()


def get_pk0():
    with open("../key_setting/pk0.txt", "r") as pk:
        pk0 = pk.readline().strip()
    return pk0


'''-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~ USED BY CLIENT -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-'''

if __name__ == "__main__":
    ''' make request to the SOLID APP to perform secure request
        INPUT : the plaintext identifier of the target requesting resource
        OUTPUT: in "/decrypt_result/result.txt" the request resource
        
        before using: the identifier must be first encrypted using tools.py
                      which generates a 'encrypted_id/x...xxx.txt' file
    '''
    secure_request("00110011")

