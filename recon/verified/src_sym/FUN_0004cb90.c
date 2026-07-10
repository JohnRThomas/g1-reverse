/* Reconstructed ipc_service_open_instance @ 0x4cb90  (parity: 300/300 trials, PROVEN) */

typedef unsigned int (*fn_t)(int,unsigned int,unsigned int,unsigned int);
extern void FUN_0007e9ea(int a,int b,void *c,int d,int e,unsigned int f,unsigned int g,unsigned int h);

unsigned int ipc_service_open_instance(int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4)
{
    unsigned int uVar1;
    fn_t UNRECOVERED_JUMPTABLE;

    if (param_1 == 0) {
        FUN_0007e9ea(0x881d8,0x1040,0,2,0,param_2,param_3,param_4);
        uVar1 = 0xffffffea;
    } else if (*(int **)(param_1 + 8) == (int *)0) {
        FUN_0007e9ea(0x881d8,0x1040,0,2,param_1,param_2,param_3,param_4);
        uVar1 = 0xfffffffb;
    } else {
        /* Zephyr driver-vtable dispatch: obj->api (ptr at obj+8) -> op[0].
           Loads the first method pointer from the api struct and calls it. */
        UNRECOVERED_JUMPTABLE = (fn_t)(**(int **)(param_1 + 8));
        if (UNRECOVERED_JUMPTABLE != (fn_t)0) {
            uVar1 = (*UNRECOVERED_JUMPTABLE)(param_1,param_2,param_3,param_4);
            return uVar1;
        }
        uVar1 = 0;
    }
    return uVar1;
}

