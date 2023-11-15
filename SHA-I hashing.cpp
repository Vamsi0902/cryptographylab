#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define SHA1_ROL(value, bits) (((value) << (bits)) | ((value) >> (32 - (bits))))


#define SHA1_BLOCK_SIZE 64
#define SHA1_DIGEST_SIZE 20

void sha1_pad(uint8_t *message, size_t length, uint64_t total_bits) {
    
    message[length++] = 0x80;

  
    while (length % SHA1_BLOCK_SIZE != 56) {
        if (length == SHA1_BLOCK_SIZE)
            break;
        message[length++] = 0x00;
    }

    
    for (int i = 0; i < 8; ++i) {
        message[length++] = (uint8_t)(total_bits >> ((7 - i) * 8));
    }
}


void sha1_hash(const uint8_t *message, size_t length, uint8_t hash[SHA1_DIGEST_SIZE]) {
    uint32_t h0, h1, h2, h3, h4;
    size_t new_length;
    uint8_t *padded_message;

    
    h0 = 0x67452301;
    h1 = 0xEFCDAB89;
    h2 = 0x98BADCFE;
    h3 = 0x10325476;
    h4 = 0xC3D2E1F0;

    uint64_t total_bits = length * 8;

    new_length = length + 1 + ((SHA1_BLOCK_SIZE - (length + 1) % SHA1_BLOCK_SIZE) % SHA1_BLOCK_SIZE) + 8;
    padded_message = (uint8_t *)malloc(new_length);
    if (padded_message == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    memcpy(padded_message, message, length);
    sha1_pad(padded_message, length, total_bits);

   
    for (size_t i = 0; i < new_length; i += SHA1_BLOCK_SIZE) {
        uint32_t *w = (uint32_t *)(padded_message + i);

        uint32_t a = h0, b = h1, c = h2, d = h3, e = h4, f, k, temp;

        for (size_t j = 0; j < 80; ++j) {
            if (j < 20) {
                f = (b & c) | ((~b) & d);
                k = 0x5A827999;
            } else if (j < 40) {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            } else if (j < 60) {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            } else {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }

            temp = SHA1_ROL(a, 5) + f + e + k + w[j];
            e = d;
            d = c;
            c = SHA1_ROL(b, 30);
            b = a;
            a = temp;
        }

        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
    }

    free(padded_message);


    hash[0] = (uint8_t)(h0 >> 24);
    hash[1] = (uint8_t)(h0 >> 16);
    hash[2] = (uint8_t)(h0 >> 8);
    hash[3] = (uint8_t)h0;
    hash[4] = (uint8_t)(h1 >> 24);
    hash[5] = (uint8_t)(h1 >> 16);
    hash[6] = (uint8_t)(h1 >> 8);
    hash[7] = (uint8_t)h1;
    hash[8] = (uint8_t)(h2 >> 24);
    hash[9] = (uint8_t)(h2 >> 16);
    hash[10] = (uint8_t)(h2 >> 8);
    hash[11] = (uint8_t)h2;
    hash[12] = (uint8_t)(h3 >> 24);
    hash[13] = (uint8_t)(h3 >> 16);
    hash[14] = (uint8_t)(h3 >> 8);
    hash[15] = (uint8_t)h3;
    hash[16] = (uint8_t)(h4 >> 24);
    hash[17] = (uint8_t)(h4 >> 16);
    hash[18] = (uint8_t)(h4 >> 8);
    hash[19] = (uint8_t)h4;
}

int main() {
   
    const char *message = "Hello, SHA-1!";

   
    uint8_t hash[SHA1_DIGEST_SIZE];
    sha1_hash((const uint8_t *)message, strlen(message), hash);


    printf("SHA-1 Hash: ");
    for (int i = 0; i < SHA1_DIGEST_SIZE; ++i) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    return 0;
}
