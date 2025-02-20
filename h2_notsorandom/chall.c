#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "aes.h"

void setup() {
  setbuf(stdin, 0);
  setbuf(stdout, 0);
}

int main() {
    setup();

    // Display time to user
    time_t raw;
    time(&raw);
    printf("Server connected.\n");
    printf("%s\n", asctime(localtime(&raw)));

    // Set seed as time
    srand(time(NULL));
    // Generate AES-128 key
    unsigned char buf[16];
    int i;
    for (i = 0; i < sizeof(buf); i++) {
        buf[i] = rand() % 256;
    }
    // Read flag from file
    FILE *f = fopen("flag.txt", "r");
    if (NULL == f) {
        printf("File can't be opened \n");
        return EXIT_FAILURE;
    }
    char ch;
    char flag[32];
    int idx = 0;
    while ((ch = fgetc(f)) != EOF) {
        sprintf(flag+idx, "%c", ch);
        idx++;
    }

    // Encrypt flag
    struct AES_ctx* ctx = malloc(sizeof(struct AES_ctx));
    AES_init_ctx(ctx, buf);
    char flag_encrypted[32];
    strcpy(flag_encrypted, flag);
    AES_ECB_encrypt(ctx, flag_encrypted);

    // Print encrypted flag
    char input[33];
    printf("Ha! You will never guess the flag!\n");
    printf("rand() might not be cryptographically secure, but surely it's secure enough if I use time as a seed!\n");
    printf("You're free to try anyway, though.\n");
    printf("Here's the encrypted flag in hexadecimal: ");
    for (int i = 0; i < 32; i++) {
        printf("%02X", (unsigned char)flag_encrypted[i]);
    }
    printf("\n");
    printf("You can tell me your guess, and I'll let you know if it's correct:\n");

    read(STDIN_FILENO, input, 33);
    fflush(stdin);

    // Check user input against actual flag
    if (!strncmp(input, flag, 32)) {
        printf("No way, how did you get my flag!?\n");
        printf("I guess rand() wasn't secure afterall...\n");
    } else {
        printf("Wrong!!\n");
    }
}