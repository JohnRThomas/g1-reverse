/* Reconstructed FUN_00080798 @ 0x80798  (parity: 300/300 trials, PROVEN) */

extern void FUN_00050c24(unsigned int);
extern void FUN_00050bf0(unsigned int, void*);

void FUN_00080798(unsigned int param_1, unsigned int *param_2)
{
    struct { unsigned int f0; unsigned char reserved[4]; unsigned char f8; unsigned char pad2[3]; unsigned int fc; } local;
    unsigned short h8 = *(unsigned short*)((char*)param_2 + 8);
    unsigned short ha = *(unsigned short*)((char*)param_2 + 10);
    local.f0 = param_2[0];
    local.f8 = (unsigned char)((h8 & 0x1f) | (ha << 5));
    local.fc = ((param_2[0] & ~0x1fu) + (param_2[1] - 1)) & ~0x1fu;
    if (param_1 > 7) {
        FUN_00050c24(param_1);
        return;
    }
    FUN_00050bf0(param_1, &local);
}
