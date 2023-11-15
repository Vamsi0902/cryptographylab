#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void createSubstitutionKey(char substitutionKey[ALPHABET_SIZE]) {
   
    const char* plaintextAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char* ciphertextAlphabet = "ZYXWVUTSRQPONMLKJIHGFEDCBA";

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        substitutionKey[i] = ciphertextAlphabet[i];
    }
}

void encryptText(const char* plaintext, char* ciphertext, const char substitutionKey[ALPHABET_SIZE]) {
    int length = strlen(plaintext);

    for (int i = 0; i < length; i++) {
        if (isalpha(plaintext[i])) {
            if (islower(plaintext[i])) {
                ciphertext[i] = tolower(substitutionKey[plaintext[i] - 'a']);
            } else {
                ciphertext[i] = substitutionKey[plaintext[i] - 'A'];
            }
        } else {
            ciphertext[i] = plaintext[i]; 
        }
    }
    ciphertext[length] = '\0';
}

int main() {
    char plaintext[100], ciphertext[100];
    char substitutionKey[ALPHABET_SIZE];

    createSubstitutionKey(substitutionKey);

    printf("Enter the plaintext: ");
    scanf(" %[^\n]s", plaintext);

    encryptText(plaintext, ciphertext, substitutionKey);

    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
