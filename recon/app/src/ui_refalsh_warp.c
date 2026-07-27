/* Reconstructed ui_refalsh_warp @ 0x48b5c.
 * Reachable code ends at 0x48e10; the following six words are its literal
 * pool, not executable instructions.  The reviewed executable extent is
 * therefore 692 bytes.
 * Bytes from 0x48e28 onward belong to separately reconstructed functions. */

extern int FUN_00032ee4(void);
extern int FUN_00036a18(int,int,int);
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern int FUN_0003603c(int,int,int);
extern int FUN_00036b3c(int,int,int);
extern int FUN_0003f410(int,int,int);
extern int FUN_0003fecc(int,int,int);
extern int FUN_0003af78(int,int,int);
extern int FUN_0003cb58(int,int,int);
extern int FUN_0003cf44(int,int,int);
extern int FUN_0003b824(int,int,int);
extern int FUN_00042d44(int,int,int);
extern int FUN_000430c0(int,int,int);
extern int FUN_0003bfe0(int,int,int);
extern int FUN_00046b80(int,int,int);

#define DBG1(ID) do { \
    int sink = *p_7554; \
    if (sink == 0) DEBUG_PRINT(0xef784, 0xf01eb, (ID), sink); \
    else FUN_00019c70(0xef784, 0xf01eb, (ID), sink); \
} while (0)
#define DBG2(ID) do { \
    int sink = *p_7554; \
    if (sink == 0) DEBUG_PRINT(0xef7a0, 0xf01eb, (ID), sink); \
    else FUN_00019c70(0xef7a0, 0xf01eb, (ID), sink); \
} while (0)
#define NORMAL(H,ID) do{ \
    if(*p_230c > 2) DBG1(ID); \
    r4 = H(param_1+0xb6c, param_3, param_4); \
    if(*p_230c > 2) DBG2(ID); \
    return r4; }while(0)

int ui_refalsh_warp(int param_1,int param_2,int param_3,int param_4){
    volatile int *p_a098=(volatile int*)0x2000a098;
    volatile int *p_230c=(volatile int*)0x2000230c;
    volatile int *p_7554=(volatile int*)0x20007554;
    int r4;
    if (FUN_00032ee4()==1){
        if (param_2==3) FUN_00036a18(param_1+0xb6c, param_3, param_4);
        return 0;
    }
    *p_a098 = param_2;
    switch(param_2){
    case 4:  return FUN_0003603c(param_1+0xb6c,param_3,param_4);
    case 5:  return FUN_00036b3c(param_1+0xb6c,param_3,param_4);
    case 10: return FUN_0003f410(param_1+0xb6c,param_3,param_4);
    case 11: return FUN_0003fecc(param_1+0xb6c,param_3,param_4);
    case 6:  NORMAL(FUN_0003af78, 6);
    case 7:  NORMAL(FUN_0003cb58, 7);
    case 9:  NORMAL(FUN_0003cf44, 9);
    case 12: NORMAL(FUN_0003b824, 12);
    case 14: NORMAL(FUN_00042d44, 14);
    case 15: NORMAL(FUN_000430c0, 15);
    case 16: NORMAL(FUN_0003bfe0, 16);
    case 17: NORMAL(FUN_00046b80, 17);
    default: {
        int id = param_2;
        if(*p_230c > 2) DBG1(id);
        int (*fp)(int,int,int) = *(int(**)(int,int,int))(param_1+0xb80);
        unsigned char b = *(volatile unsigned char*)(param_1+0xd5);
        r4 = fp(param_1+0xb6c, b, param_1+0xd4);
        if(*p_230c > 2) DBG2(id);
        return r4;
    }
    }
}
