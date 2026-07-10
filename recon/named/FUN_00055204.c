/* named: FUN_00055204 */
/* globals referenced:
//   0x20002000  g_ble_dev_state              
*/
/* Reconstructed FUN_00055204 @ 0x55204  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32; typedef uint8_t u8;
extern int id_find(char*);
extern unsigned FUN_00054d18(unsigned,char*);
extern int bt_addr_le_eq(char*,u32);
extern int FUN_00080fb4(int);
extern void FUN_0008104a(u32,int,void*);
unsigned FUN_00055204(char* param_1, int param_2){
    u32 local_18[2];
    if(param_1 != 0){
        int fa = bt_addr_le_eq(param_1, 0x000f2b3a);
        if(fa == 0){
            if(*param_1 != 1 || (param_1[6] & 0xc0) != 0xc0){
                local_18[0] = 2; local_18[1] = 0x000f3705;
                FUN_0008104a(0x00088150, 0x1040, local_18);
                return 0xffffffea;
            }
            int c = id_find(param_1);
            if(c >= 0) return 0xffffff88;
        }
    }
    if(param_2 != 0) return 0xffffffea;
    if(*(volatile char*)(0x20002000UL+7) == 1) return 0xfffffff4;
    int iVar3 = FUN_00080fb4(0x20002000+0xd4);
    if((int)(iVar3 << 0x1f) < 0 || (param_1 != 0 && bt_addr_le_eq(param_1, 0x000f2b3a) == 0)){
        u8 bVar1 = *(volatile u8*)(0x20002000UL+7);
        *(volatile u8*)(0x20002000UL+7) = bVar1 + 1;
        unsigned uVar4 = FUN_00054d18(bVar1, param_1);
        if(uVar4 != 0){
            *(volatile char*)(0x20002000UL+7) = *(volatile char*)(0x20002000UL+7) - 1;
            return uVar4;
        }
        return bVar1;
    }
    return 0xffffffea;
}

