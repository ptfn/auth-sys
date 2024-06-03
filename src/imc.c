#include <openssl/sha.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h> // sleep
#include <string.h>
#include <stdio.h> // out
#include <time.h>
#include <math.h>

#define INTERVAL 30
#define DIGITS   6
#define T0       0

#define IPAD     0x36
#define OPAD     0x5c

void from(uint64_t t, uint8_t *bytes)
{
    for (uint8_t i = 0; i < 8; i++)
        bytes[i] = t >> 8 * i;
}

void sha1(uint8_t *dest, uint8_t *src, size_t len)
{
    SHA_CTX ctx;
    SHA1_Init(&ctx);
    SHA1_Update(&ctx, src, len);
    SHA1_Final(dest, &ctx);
}

void copy(uint8_t *dest, uint8_t *src, uint8_t start, uint8_t end)
{
    for (uint8_t i = start; i < end; i++)
        dest[i] = src[i-start];
}

uint32_t totp(uint8_t *key, size_t keylen)
{
    uint64_t t = (uint64_t)floor(difftime(time(NULL), T0) / INTERVAL), offset; 
    uint32_t bin_code, code;
    uint8_t K0[64], ipad[64], opad[64],
            tipad[72], topad[84], tempt[8], 
            hipad[SHA_DIGEST_LENGTH], hopad[SHA_DIGEST_LENGTH];

    memset(K0, 0, 64);
    memcpy(K0, key, keylen >= 64 ? 64 : keylen);

    for (size_t i = 0; i < 64; i++) {
        ipad[i] = K0[i] ^ IPAD;
        opad[i] = K0[i] ^ OPAD;
    }

    copy(tipad, ipad, 0, 64);
    from(t, tempt);
    copy(tipad, tempt, 64, 72);
    sha1(hipad, tipad, 72);

    copy(topad, opad, 0, 64);
    copy(topad, hipad, 64, 84);
    sha1(hopad, topad, 84);

    offset = hopad[19] & 0x0f;
    bin_code = (hopad[offset] & 0x7f) << 24 
           | (hopad[offset+1] & 0xff) << 16
           | (hopad[offset+2] & 0xff) <<  8
           | (hopad[offset+3] & 0xff);

    code = bin_code % (uint32_t)pow(10, DIGITS);

    return code;
}

bool access_check(uint8_t *key, size_t keylen, uint32_t code)
{
    uint32_t passgen = totp(key, keylen);
    return passgen == code;
}

int main()
{
    uint32_t code = 507327;
    uint8_t key[] = "Hello";

    printf("%u\n", totp(key, 5));
    printf("%d\n", access_check(key, 5, code));
    return 0;
}
