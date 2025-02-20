#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "aes.h"

// Convert hex string to bytes
void hex_to_bytes(const char *hex, unsigned char *bytes, int len) {
    for (int i = 0; i < len; i++) {
        sscanf(hex + 2*i, "%2hhx", &bytes[i]);
    }
}

int main() {
    const char *server_time = "Wed Feb 12 12:28:28 2025";
    const char *encrypted_hex = "51FA08851D0BF81245D871581CC75ACB6E64306D5F34667433725F346C6C3F7D";

    // Parse server time
    struct tm tm = {0};
    strptime(server_time, "%c", &tm);
    time_t server_timestamp = mktime(&tm);

    // Set the same seed
    srand(server_timestamp);

    // Generate the same AES key
    unsigned char key[16];
    for (int i = 0; i < 16; i++) {
        key[i] = rand() % 256;
    }

    // Initialize AES context
    struct AES_ctx ctx;
    AES_init_ctx(&ctx, key);

    // Convert hex encrypted flag to bytes
    unsigned char encrypted[32] = {0};
    unsigned char decrypted[32] = {0};
    unsigned char block1[16] = {0};
    unsigned char block2[16] = {0};

    // Convert hex to bytes
    hex_to_bytes(encrypted_hex, encrypted, 32);

    // Split into blocks and decrypt separately
    memcpy(block1, encrypted, 16);
    memcpy(block2, encrypted + 16, 16);

    // Decrypt each block
    AES_ECB_decrypt(&ctx, block1);
    AES_ECB_decrypt(&ctx, block2);

    // Combine blocks
    memcpy(decrypted, block1, 16);
    memcpy(decrypted + 16, block2, 16);

    // Print both hex and ASCII for debugging
    printf("Decrypted blocks in hex:\n");
    for(int i = 0; i < 32; i++) {
        printf("%02x ", decrypted[i]);
        if(i == 15) printf("\n");
    }
    printf("\n\nDecrypted flag: %s\n", decrypted);
    //CS2107{n0t_s0_r4nd0m_4ft3r_4ll?}
    return 0;
}