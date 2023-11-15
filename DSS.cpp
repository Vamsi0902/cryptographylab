#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int euclidean_algorithm(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}


int extended_euclidean_algorithm(int a, int b) {
    int x0 = 1, x1 = 0, y0 = 0, y1 = 1;
    while (b != 0) {
        int q = a / b;
        int temp = b;
        b = a % b;
        a = temp;

        temp = x0 - q * x1;
        x0 = x1;
        x1 = temp;

        temp = y0 - q * y1;
        y0 = y1;
        y1 = temp;
    }
    return x0;
}


int modular_exponentiation(int base, int exponent, int modulus) {
    int result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}


int sign_message(int message, int private_key, int prime) {
    return modular_exponentiation(message, private_key, prime);
}


int verify_signature(int message, int signature, int public_key, int prime) {
    int message_hash = modular_exponentiation(signature, public_key, prime);
    return message_hash == message;
}

int main() {
   
    int prime = 17; 
    int generator = 3; 
    int private_key = 15;

    
    int public_key = modular_exponentiation(generator, private_key, prime);

   
    int message = 7; 

    int signature = sign_message(message, private_key, prime);

    
    int is_valid = verify_signature(message, signature, public_key, prime);

  
    printf("Public Key: %d\n", public_key);
    printf("Signature: %d\n", signature);
    printf("Verification Result: %s\n", is_valid ? "Valid" : "Invalid");

    return 0;
}
