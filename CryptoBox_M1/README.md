# The Crypto Box M1 VERSION
##### A crypto tool implemented based on DGHV Homomorphic Encryption scheme
The system composes of 2 layers, the inner layer (the core layer) and the abstract layer (the service layer). 
The whole system running only on user's local machine for security reason. 
The private key never transmits on the internet and only stay at the user's local machine.

The Crypto Box is used together with an App https://github.com/SeraphinaLiang/thesis_app 

##### tips : the core layer only works on Mac M1, better using xcode

## the Core layer
###### the C code under /core directory
#### how to compile & run?
follow the set up in the xcode file, build & run 

#### basic requirements
`gnu 11`
`gmp 6.2.1_1`
`c++ 11`

#### the security parameter
1. the set up of the security parameter in `'secstg.c'` could be changed and can also be verified by function `para_valid(para)`

## the Service layer
###### the python code under /service directory
#### Set up (with detail explanation in code)
1. start the Core layer according to _how to run?_
2. go to the `connect_core.py` , run `start()` or `reset_parameter()`
3. encryption of file and identifier is provided by `tools.py`
4. to make private request to Solid App, go to `service.py`

#### system capacity limitations
1. assume that the experiment file only in `.txt` format
2. assume that the experiment file content only has one line of string
3. assume that the only string have less than 5 characters

#### running environment
1. preinstall `pip install gmpy2`  library reference https://gmpy2.readthedocs.io/en/latest/intro.html
2. run on Windows would be just fine, also linux

## The explanation of each directory:

#### /core (the Core Layer)
1. contains library code `facil.io` to make API interface in C, from https://github.com/boazsegev/facil.io
2. the `test.c` file provides implementation of DGHV algorithm
3. the `api.c` file provides APIs interface to be called by the Service Layer (Python layer)
4. a library: a DGHV public key version implementation from https://github.com/limengfei1187/DGHVlib, used by `test.c` file 

#### /ctext
1. to handle data transmission between the core layer (C) and the service layer (Python) when encrypting
2. `'one.txt'`: generated ciphertext of an encrypted one
3. `'zero.txt'`: generated ciphertext of an encrypted zero

#### /decrypt_result
1. `'origin.txt'` the text to be decrypted
2. `'result.txt'` the decrypt result of 1 (binary version)
3. `'decode_result.txt'` the decode result of 2 (utf-8)

#### /decrypt_text
1. to handle data transmission between the core layer (C) and the service layer (Python) when decrypting
2. `'cin.txt'` the ciphertext to be decrypted, generate one bit plaintext

#### /file
1. store the origin client's file
2. `/encrypted_id` : store the encrypted identifier of the origin client's file
3. `/encrypted_file` : store the encrypted content of the origin client's file

#### /key_setting
1. `'parameters'` the security parameters setting
2. `'pk0.txt'` the first array item of public key, use for evaluate function (add / multiple)
3. `'private_key.key'` the private key
4. `'public_key.key'` the public key

#### /service (the Service Layer)
1. the wrapper of the Core layer
2. `'connect_core.py'` provides functions connecting to the core layer
3. `'tools.py'` a tool library used by client to encrypt file and identifier
4. `'service.py'` use by client to send private request to the Solid app

