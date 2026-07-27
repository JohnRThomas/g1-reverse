/* Reconstructed register_ipc_service_context @ 0x25d40  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
unsigned int register_ipc_service_context(int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4){
    *(unsigned int*)(param_1+0x60) = 0x00025b79UL;
    *(unsigned int*)(param_1+0x64) = 0x00025ae9UL;
    *(volatile unsigned int*)0x20007a84UL = (unsigned int)param_1;
    if(*(volatile int*)0x2000230cUL > 1){
        unsigned int sink=*(volatile unsigned int*)0x20007554UL;
        if(sink==0){
            DEBUG_PRINT(0x0009af2eUL,0x0009f6c6UL,param_3,sink,param_4);
        } else {
            FUN_00019c70(0x0009af2eUL,0x0009f6c6UL,param_3,sink,param_4);
        }
    }
    return 0;
}
