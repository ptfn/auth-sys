#ifndef _TOTPLIB_H_
#define _TOTPLIB_H_

/* Libraries */
#include <openssl/sha.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

/* Macros */
#define INTERVAL 30
#define DIGITS   6
#define T0       0

#define IPAD     0x36
#define OPAD     0x5c

/* Struct Keys */
typedef struct
{
    uint8_t *key;
    size_t  len;
} keys_t;

#endif

