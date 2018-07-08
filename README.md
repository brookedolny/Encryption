# Encryption
A library of my own implementations of various forms of encryption.

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


## Block Cipher Mode of Operation

Because block ciphers only encrypt `N` bits, a mode of operation is required to encrypt a file. Even with a mode of operation, a block cipher can still only encrypt a multiple of `N` bits.
If the size of a file is not a multiple of `N` bits, then padding is added to make the file a multiple of `N` bits. 

### Electronic Codebook (ECB)

ECB is a mode of operation that takes each group of 128 bits and encrypts them with the same key.
Although each block will be encrypted, because of the nature of the AES, identical plaintext blocks, encrypted with the same key, will produce the same ciphertext. 
This causes obvious problems, as it becomes difficult to hide data patterns in a file, as demonstrated by the following images:

![alt text](/AES/out/tux.bmp "Plaintext Image") 
![alt text](/AES/out/encrypted_ecb.bmp "ECB Image")
![alt text](/AES/out/encrypted_cbc.bmp "CBC Image")

The first image is the original plaintext image. 
The second image is the plaintext image encrypted with the AES, but using the ECB mode of encryption. 
The third image is the plaintext image encrypted with the AES, but using another, more secure, mode of operation. 
Note that the CBC image hides data patterns significantly better than teh ECB image, and appears pseudorandom.

### Cipher Block Chaining (CBC)

Cipher Block Chaining (CBC) is a mode of operation that encrypts the plaintext XORed with the previous ciphertext.

The first block is XORed with an inital block, known as the Initalization Vector (IV).
Using the wrong IV upon decryption will result in the incorrect plaintext output, but all remaining blocks will remain correct. 
This is because encryption uses the previous _ciphertext_ XORed with the plaintext, not the previous plaintext. 

Using a predetermined initalization vector can be bothersome, as you are required to know both the IV **and** the key in order to decrypt the file.

Thus, we can circumvent the need for an IV by appending a random "garbage" block to the beginning of the message, and discarding it upon decryption.
Since decrypting the message only depends on the previous ciphertext, and the "garbage" block is not part of the plaintext, one can obtain the original plaintext without communicating an initalization vector!
