#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MATRIX_SIZE 2


int calculateInverse(int matrix[MATRIX_SIZE][MATRIX_SIZE], int inverse[MATRIX_SIZE][MATRIX_SIZE]) {
   
    int det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];

    if (det == 0) {
        return 0; 
    }

    
    inverse[0][0] = matrix[1][1];
    inverse[0][1] = -matrix[0][1];
    inverse[1][0] = -matrix[1][0];
    inverse[1][1] = matrix[0][0];

    
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            inverse[i][j] = inverse[i][j] / det;
        }
    }

    return 1;
}


void encrypt(int matrix[MATRIX_SIZE][MATRIX_SIZE], char* plaintext, char* ciphertext) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i += 2) {
        int p[MATRIX_SIZE], c[MATRIX_SIZE];
        
        
        for (int j = 0; j < MATRIX_SIZE; j++) {
            p[j] = plaintext[i + j] - 'A';
        }

      
        for (int j = 0; j < MATRIX_SIZE; j++) {
            c[j] = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                c[j] += matrix[j][k] * p[k];
            }
            c[j] = c[j] % 26;
        }

        
        for (int j = 0; j < MATRIX_SIZE; j++) {
            ciphertext[i + j] = 'A' + c[j];
        }
    }
}

int main() {
    int key[MATRIX_SIZE][MATRIX_SIZE] = {{3, 3}, {2, 5}}; 
    char plaintext[100];
    char ciphertext[100];

    printf("Enter the plaintext (uppercase letters only): ");
    scanf("%s", plaintext);

    int inverse[MATRIX_SIZE][MATRIX_SIZE];

    if (calculateInverse(key, inverse)) {
        encrypt(key, plaintext, ciphertext);

        printf("Ciphertext: %s\n", ciphertext);
    } else {
        printf("Key matrix is not invertible. Choose a different key.\n");
    }

    return 0;
}

