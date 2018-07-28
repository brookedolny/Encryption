#ifndef SHA_FUNCTIONS_H
#define SHA_FUNCTIONS_H

#define rotateLeft(x, n, w) (((x) << (n)) | ((x) >> ((w) - (n))))
#define rotateRight(x, n, w) (((x) >> (n)) | ((x) << ((w) - (n))))
#define choose(x, y, z) (((x) & (y)) ^ (!(x) & (z)))
#define parity(x, y, z) ((x) ^ (y) ^ (z))
#define majority(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

#endif
