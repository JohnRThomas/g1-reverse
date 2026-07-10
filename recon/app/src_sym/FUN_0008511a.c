/* Reconstructed FUN_0008511a @ 0x8511a  (parity: 300/300 trials, PROVEN) */

extern unsigned long long pin_is_output(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern unsigned int pin_in_use_by_te(unsigned int);

unsigned int FUN_0008511a(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int uVar1;
    unsigned long long uVar2;
    uVar2 = pin_is_output(param_1, param_1, param_3, param_4, param_4);
    uVar1 = (unsigned int)uVar2;
    if (uVar1 != 0) {
        uVar1 = pin_in_use_by_te((unsigned int)(uVar2 >> 32));
    }
    return uVar1 & 1;
}

