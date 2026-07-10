/* Reconstructed opt3007_chip_deinit @ 0x2e8b4  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
extern void debug_print(void);
void opt3007_chip_deinit(unsigned int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4){
    unsigned int v = *(volatile unsigned int*)0x20007b6cUL /* device_info_t+0x1170 (unmapped region) */;
    if(v != 0){
        param_3 = 0;
        *(volatile unsigned int*)(v + 0x10) = 0;
    }
    if(*(volatile int*)0x2000230cUL > 2){
        if(*(volatile unsigned int*)0x20007554UL /* device_info.is_debug @+0xb58 */==0){
            DEBUG_PRINT(0x000a3cb9UL,0x000a3cdaUL,param_3,0,param_4);
        } else {
            debug_print();
        }
    }
    *(volatile unsigned char*)0x20018da1UL = 0;
}

