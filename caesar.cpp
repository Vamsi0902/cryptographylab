#include <stdio.h>
#include <string.h>
void encryptCaesarCipher(char message[], int key) {
    int i;
    char ch;
    for (i = 0; message[i] != '\0'; ++i) {
        ch = message[i];
        if (ch >= 'a' && ch <= 'z') {
            ch = (char)(((ch - 'a' + key) % 26) + 'a');
        } else if (ch >= 'A' && ch <= 'Z') {
            ch = (char)(((ch - 'A' + key) % 26) + 'A');
        }
        message[i] = ch;
    }
}
void decryptCaesarCipher(char message[], int key) 
{
    encryptCaesarCipher(message, 26 - key);
}
int main() 
{
    char message[100];
    int key;
    printf("Enter a message: ");
    fgets(message, sizeof(message), stdin);
    printf("Enter the key (an integer between 1 and 25): ");
    scanf("%d", &key);
    if (key < 1 || key > 25) {
        printf("Invalid key. Please use a key between 1 and 25.\n");
        return 1;
    }
    encryptCaesarCipher(message, key);
    printf("Encrypted message: %s\n", message);
    decryptCaesarCipher(message, key);
    printf("Decrypted message: %s\n", message);
    return 0;
}
