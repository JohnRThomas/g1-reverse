/* Reconstructed FUN_00084d36 @ 0x84d36  (parity: 300/300 trials, PROVEN) */

extern char *FUN_00063bcc(void);
extern void FUN_0004f770(void);
extern void FUN_00063c14(int a);
void FUN_00084d36(void) {
    char *p = FUN_00063bcc();
    *(volatile unsigned char*)(p + 8) = 0;
    FUN_0004f770();
    FUN_00063c14(5);
}

