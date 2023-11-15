#include <stdio.h>
#include <string.h>

void prepareKeyTable(char key[], char keyTable[5][5]) {
    int k, i, j;
    char tempKey[26] = {0};
    
    k = 0;
    for (i = 0; i < strlen(key); i++) {
        if (key[i] != ' ' && !tempKey[key[i] - 65]) {
            tempKey[key[i] - 65] = 1;
            keyTable[k / 5][k % 5] = key[i];
            k++;
        }
    }
    
    for (i = 0; i < 26; i++) {
        if (!tempKey[i]) {
            keyTable[k / 5][k % 5] = i + 65;
            k++;
        }
    }
}

void findPosition(char keyTable[5][5], char letter, int* row, int* col) {
    if (letter == 'J')
        letter = 'I';

    for (*row = 0; *row < 5; (*row)++) {
        for (*col = 0; *col < 5; (*col)++) {
            if (keyTable[*row][*col] == letter) {
                return;
            }
        }
    }
}

void encrypt(char keyTable[5][5], char plaintext[], char ciphertext[]) {
    int len = strlen(plaintext);
    int p1, p2, c1, c2;
    int row1, col1, row2, col2;
    int k = 0;

    for (int i = 0; i < len; i += 2) {
        p1 = plaintext[i];
        p2 = (i + 1 < len) ? plaintext[i + 1] : 'X';

        findPosition(keyTable, p1, &row1, &col1);
        findPosition(keyTable, p2, &row2, &col2);

        if (row1 == row2) {
            c1 = keyTable[row1][(col1 + 1) % 5];
            c2 = keyTable[row2][(col2 + 1) % 5];
        } else if (col1 == col2) {
            c1 = keyTable[(row1 + 1) % 5][col1];
            c2 = keyTable[(row2 + 1) % 5][col2];
        } else {
            c1 = keyTable[row1][col2];
            c2 = keyTable[row2][col1];
        }

        ciphertext[k++] = c1;
        ciphertext[k++] = c2;
    }
    ciphertext[k] = '\0';
}

int main() {
    char key[26], plaintext[100], ciphertext[100];
    char keyTable[5][5];
    
    printf("Enter the key (uppercase letters only, no spaces, 'J' is replaced by 'I'): ");
    scanf("%s", key);
    printf("Enter the plaintext (uppercase letters only, no spaces): ");
    scanf("%s", plaintext);
    
    prepareKeyTable(key, keyTable);
    encrypt(keyTable, plaintext, ciphertext);
    
    printf("Ciphertext: %s\n", ciphertext);
    
    return 0;
}
