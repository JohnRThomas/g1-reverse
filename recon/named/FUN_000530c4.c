/* named: FUN_000530c4 */
/* globals referenced:
//   0x200020d4  g_bt_dev.ncmd_sem            [g_bt_dev (base 0x20002000) + 0xd4: semaphore gating outstanding HCI command credits, taken in bt_send/bt_hci_driver_close]
*/
/* Reconstructed FUN_000530c4 @ 0x530c4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32; typedef uint8_t u8;
extern int FUN_0004d944(u32,int,void*,int);
extern void FUN_000530b4(void);
extern void FUN_000548b8(void);
extern void bt_set_name_internal(u32);
extern int bt_setup_public_id_addr(void);
extern int FUN_000553f8(void);
int FUN_000530c4(void){
    volatile u32* puVar1 = (volatile u32*)0x200020d4UL;
    u32 r3 = *puVar1;
    if((r3 & 1) == 0) return 0;
    if(*(volatile u8*)(0x200020d4UL + 0x98) == 0){
        bt_set_name_internal(0x0009ac7c);
    }
    int iVar2;
    if(*(volatile u8*)(0x200020d4UL - 0xcd) == 0){
        iVar2 = bt_setup_public_id_addr();
        if(iVar2 != 0) goto RS;
        if(*(volatile u8*)(0x200020d4UL - 0xcd) == 0){
            iVar2 = FUN_000553f8();
            if(iVar2 != 0) goto RS;
        }
    }
    {
        u32 v = *puVar1;
        if((int)(v << 0x1d) >= 0) FUN_000548b8();
        u32 uVar3 = *puVar1;
        *puVar1 = uVar3 & 0xfffeffff;
        if((int)(uVar3 << 0xf) < 0) FUN_000530b4();
    }
    return 0;
RS: ;
    u32 local[2];
    local[0] = 2;
    local[1] = 0x000f2c8c;
    FUN_0004d944(0x00088178, 0x1040, local, 0);
    return iVar2;
}

