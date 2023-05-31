from connect_core import start, reset_parameter
from service import secure_request
from tools import encrypt_file, encrypt_identifier

if __name__ == "__main__":

    print("CryptoBox start ...")
    print("menu\n"
          "1. start \n"
          "2. reset parameter\n"
          "3. send secure request \n"
          "4. encrypt identifier \n"
          "5. encrypt file\n"
          "6. quit\n")

    c = input("make your choice: ")

    while True:
        if c == "6":
            break

        if c == "1":
            start()

        if c == "2":
            para = input("parameter choice: ")
            reset_parameter(int(para))

        if c == "3":
            # secure_request("00110011")
            id = input("identifier: ")
            secure_request(id)

        if c == "4":
            # encrypt_identifier("10111100.txt", 8)
            id = input("identifier: ")
            length = input("length: ")
            encrypt_identifier(id + ".txt", int(length))

        if c == "5":
            # encrypt_file("10111100.txt")
            id = input("identifier: ")
            encrypt_file(id + ".txt")

        c = input("make your choice: ")

    print("CryptoBox end ...")
