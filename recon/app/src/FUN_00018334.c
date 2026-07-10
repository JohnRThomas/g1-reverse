/* Reconstructed FUN_00018334 @ 0x18334  (parity: 300/300 trials, PROVEN) */
extern void FUN_00086fee(void* a, unsigned b);
extern void FUN_0007ddbe(void*, ...);
void FUN_00018334(unsigned char* param_1, void* param_2){
    unsigned char buf[12];
    switch(*param_1){
    case 0: FUN_00086fee(buf, 0x9a1c8); break;
    case 1: FUN_00086fee(buf, 0x9a1cf); break;
    case 2: FUN_00086fee(buf, 0x9a1d6); break;
    case 3: FUN_00086fee(buf, 0x9a1e0); break;
    default:
        FUN_0007ddbe(buf, 10, 0xf5071);
        break;
    }
    FUN_0007ddbe(param_2, 0x1e, 0x9a1ea, param_1[6], param_1[5], param_1[4],
                 param_1[3], param_1[2], param_1[1], buf);
}

