#include <stdio.h>
#include <stdint.h>


int initial_permutation[] = { 58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
                              62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
                              57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
                              61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7 };


int final_permutation[] = { 40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
                            38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
                            36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
                            34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25 };


int expand_permutation[] = { 32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11,
                             12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21,
                             22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1 };

int sbox[8][4][16] = {  };


int PC1[] = {  };


int PC2[] = { };


int left_shifts[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

void initialPermutation(uint64_t *data) {
    uint64_t newData = 0;
    for (int i = 0; i < 64; ++i) {
        newData <<= 1;
        newData |= ((*data >> (64 - initial_permutation[i])) & 1);
    }
    *data = newData;
}

void finalPermutation(uint64_t *data) {
    uint64_t newData = 0;
    for (int i = 0; i < 64; ++i) {
        newData <<= 1;
        newData |= ((*data >> (64 - final_permutation[i])) & 1);
    }
    *data = newData;
}

void expand(uint32_t *right, uint64_t *expanded) {
    uint64_t rightData = *right;
    uint64_t newData = 0;
    for (int i = 0; i < 48; ++i) {
        newData <<= 1;
        newData |= ((rightData >> (32 - expand_permutation[i])) & 1);
    }
    *expanded = newData;
}

void DES(uint64_t *data, uint64_t *key, int encrypt) {
   
}

int main() {
    uint64_t plaintext = 0x0123456789ABCDEF; 
    uint64_t key = 0x133457799BBCDFF1;       

    printf("Plaintext: 0x%016llX\n", plaintext);
    printf("Key:      0x%016llX\n", key);

    initialPermutation(&plaintext);
    initialPermutation(&key);

    printf("After initial permutation:\n");
    printf("Plaintext: 0x%016llX\n", plaintext);
    printf("Key:      0x%016llX\n", key);

   
    DES(&plaintext, &key, 1);

    printf("After encryption:\n");
    printf("Ciphertext: 0x%016llX\n", plaintext);

   
    DES(&plaintext, &key, 0);

    finalPermutation(&plaintext);

    printf("After final permutation (decrypted):\n");
    printf("Plaintext: 0x%016llX\n", plaintext);

    return 0;
}
