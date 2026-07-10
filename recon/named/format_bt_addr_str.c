/* named: format_bt_addr_str */
/* Reconstructed format_bt_addr_str @ 0x18334  (parity: 300/300 trials, PROVEN) */
extern void strcpy(void* a, unsigned b);
extern void snprintk(void*, ...);
void format_bt_addr_str(unsigned char* param_1, void* param_2){
    unsigned char buf[12];
    switch(*param_1){
    case 0: strcpy(buf, 0x9a1c8); break;
    case 1: strcpy(buf, 0x9a1cf); break;
    case 2: strcpy(buf, 0x9a1d6); break;
    case 3: strcpy(buf, 0x9a1e0); break;
    default:
        snprintk(buf, 10, 0xf5071);
        break;
    }
    snprintk(param_2, 0x1e, 0x9a1ea, param_1[6], param_1[5], param_1[4],
                 param_1[3], param_1[2], param_1[1], buf);
}

