/* Reconstructed check_device_readiness @ 0x167b4  (parity: 300/300 trials, PROVEN) */

extern int z_device_is_ready(unsigned int);
extern void DEBUG_PRINT(unsigned long, ...);
unsigned int check_device_readiness(void){
    unsigned int *puVar1 = (unsigned int*)0x00087bf0UL;
    int iVar2 = z_device_is_ready((unsigned int)puVar1);
    unsigned int uVar3;
    if(iVar2==0){
        DEBUG_PRINT(0x000a40ecUL, puVar1[0]);
        uVar3 = 0xffffffffU;
    } else {
        void (*fn)(unsigned int,unsigned int,unsigned int) = (void*)(*(unsigned int*)(puVar1[2] + 8));
        fn((unsigned int)puVar1, 0, 0x130000);
        DEBUG_PRINT(0x00099726UL);
        uVar3 = 0;
    }
    return uVar3;
}

