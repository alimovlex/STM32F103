#include <stdint.h>
uint8_t bell[8]  = {0x4,0xe,0xe,0xe,0x1f,0x0,0x4};
uint8_t note[8]  = {0x2,0x3,0x2,0xe,0x1e,0xc,0x0};
uint8_t clock[8] = {0x0,0xe,0x15,0x17,0x11,0xe,0x0};
uint8_t heart[8] = {0x0,0xa,0x1f,0x1f,0xe,0x4,0x0};
uint8_t duck[8]  = {0x0,0xc,0x1d,0xf,0xf,0x6,0x0};
uint8_t check[8] = {0x0,0x1,0x3,0x16,0x1c,0x8,0x0};
uint8_t cross[8] = {0x0,0x1b,0xe,0x4,0xe,0x1b,0x0};
uint8_t retarrow[8] = {0x1,0x1,0x5,0x9,0x1f,0x8,0x4};

uint8_t habr1[8] = {0x0,0x0,0x2,0x3,0xd,0x7,0x7,0xf};
uint8_t habr2[8] = {0x0,0x1,0x7,0x1b,0x1e,0xf,0x1f, 0x1f};
uint8_t habr3[8] = {0x10,0x9,0x17,0x1c,0xc,0x1f,0xd, 0x1d};
uint8_t habr4[8] = {0x0,0x10,0x0,0x0,0x10,0x0,0x14,0x18};

uint8_t habr5[8] = {0x15,0xd,0xb,0xd,0x5,0x3,0x5, 0x6};
uint8_t habr6[8] = {0x1f,0x1f,0x1f,0x1f,0x1f,0x7,0x19, 0xe};
uint8_t habr7[8] = {0x1d,0x1d,0x1d,0x1a,0x1b, 0xd,0x19, 0x8};
uint8_t habr8[8] = {0x18,0x10,0x2,0x1c,0x1f,0x0,0x0,0x0};

uint8_t habr9[8] =  {0x1, 0x1,0x3, 0x3,0x1,0x0,0x0, 0x0};
uint8_t habr10[8] = {0x18,0x8,0x18,0x4,0x8,0x8,0x10,0x0};
uint8_t habr11[8] = {0x18,0x10,0x10,0x0,0x0,0x0,0x0, 0x0};

// Function declarations
// typedef __w64 unsigned int size_t
void displayKeyCodes(void);
char *itoa(int n, char *s, int b);
char *strrev(char *str);
