#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

unsigned long long int modulo(unsigned long long int a, unsigned long long int b, unsigned long long int c){
    unsigned long long int result = 1;
    a = a % c;
    while (b > 0){
        if (b % 2 == 1)
            result = (result * a) % c;
        b = b / 2;
        a = (a * a) % c;
    }
    return result;
}


int isPrime(int num){
    if (num <= 1)
        return 0;
    if (num <= 3)
        return 1;
    if (num % 2 == 0 || num % 3 == 0)
        return 0;
    for (int i = 5; i * i <= num; i = i + 6){
        if (num % i == 0 || num % (i + 2) == 0)
            return 0;
    }
    return 1;
}

int main() {
    int p, q;
    int e, d; 
    int n, phi;
    int message;

    printf("Enter two prime numbers: ");
    scanf("%d %d", &p, &q);

    if (!isPrime(p) || !isPrime(q)) {
        printf("Please enter prime numbers.\n");
        return 1;
    }

    n = p * q;
    phi = (p - 1) * (q - 1);

    
    for (e = 2; e < phi; e++) {
        if (gcd(e, phi) == 1)
            break;
    }

   
    for (d = 2; d < phi; d++) {
        if ((e * d) % phi == 1)
            break;
    }

    printf("Public key (e, n): (%d, %d)\nPrivate key (d, n): (%d, %d)\n", e, n, d, n);

    printf("Enter message to encrypt: ");
    scanf("%d", &message);

    
    unsigned long long int encrypted = modulo(message, e, n);
    printf("Encrypted message: %llu\n", encrypted);

    unsigned long long int decrypted = modulo(encrypted, d, n);
    printf("Decrypted message: %llu\n", decrypted);

    return 0;
}
