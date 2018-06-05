# Encryption
An implementation of the Advanced Encryption Standard; a block cipher. 

## Advanced Encryption Standard (AES)
The AES is a block cipher that operates on sets of 128 bits. Each byte in the plaintext is put into a 4x4 matrix, which is transformed into the ciphertext.

The standard allows for three different key lengths: 128, 192, and 256 bit keys (which are referred to as AES-128, AES-192, and AES-256). 

For each of the three key lengths, the number of rounds to perform the encryption transformations varies:


|                      |    AES-128   |     AES-192    |    AES-256    |
|       :----:         |    :---:     |     :---:      |     :---:     |
| **Block Size**       |       4      |       4        |       4       |
| **Key Length**       |       4      |       6        |       8       |
| **Number of Rounds** |      10      |       12       |       14      |


Where the block size is given as the number of 4 byte words, key length is given as the number of 4 byte words that make up the key, and the number of rounds is the number of times the encryption algorithm is performed.
