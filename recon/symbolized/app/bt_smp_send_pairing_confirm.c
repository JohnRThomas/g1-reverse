#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0005cdc4 @ 0x0005cdc4
 * public-name: bt_smp_send_pairing_confirm
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   bt_smp_send_pdu                          <= FUN_0005cb38 @ 0x0005cb38
 *   bt_smp_send_pairing_confirm              <= FUN_0005cdc4 @ 0x0005cdc4
 *   net_buf_unref                            <= FUN_0005f24c @ 0x0005f24c
 *   net_buf_simple_add                       <= FUN_0005f5d0 @ 0x0005f5d0
 *   atomic_clear_bit_1                       <= FUN_0008304c @ 0x0008304c
 *   smp_log_message                          <= FUN_00083074 @ 0x00083074
 *   smp_create_pdu                           <= FUN_000830b0 @ 0x000830b0
 *   bt_crypto_f4                             <= FUN_000835ea @ 0x000835ea
 * address symbols (name @ address):
 *   rodata_88180                             @ 0x00088180
 *   rodata_f4e7a                             @ 0x000f4e7a
 *   g_smp_local_public_key                   @ 0x2000af48
 */
/* Reconstructed FUN_0005cdc4 @ 0x5cdc4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef uint32_t u32; typedef uint8_t u8;
extern void bt_smp_send_pdu(int, unsigned int, unsigned int);
extern void net_buf_unref(int);
extern u32 net_buf_simple_add(int,int);
extern void atomic_clear_bit_1(volatile long*, int);
extern void smp_log_message(u32,int,void*);
extern int smp_create_pdu(int,int);
extern int bt_crypto_f4(u32,int,int,unsigned);
static inline u32 lsr(u32 v, u32 n){ n&=0xff; return n>=32?0:v>>n; }
unsigned int bt_smp_send_pairing_confirm(int param_1) {
    unsigned uVar3 = *(u8*)(param_1+8);
    if(uVar3 < 3){
        if(uVar3 != 0){
            uVar3 = (lsr(*(u32*)(param_1+0xd8), *(u8*)(param_1+0xdc)) & 1) | 0x80;
        }
    } else {
        if(uVar3 != 3){
            u32 local[3];
            local[0]=3; local[1]=((unsigned long)&rodata_f4e7a) /*=0xf4e7a*/; local[2]=uVar3;
            smp_log_message(((unsigned long)&rodata_88180) /*=0x88180*/, 0x1840, local);
            return 8;
        }
        uVar3 = 0;
    }
    int iVar1 = smp_create_pdu(param_1, 3);
    if(iVar1 != 0){
        (void)net_buf_simple_add(iVar1+0xc, 0x10);
        int iVar2 = bt_crypto_f4(*(volatile u32*)((unsigned long)&g_smp_local_public_key) /*=0x2000af48*/, param_1+0x57, param_1+0x27, uVar3);
        if(iVar2 == 0){
            bt_smp_send_pdu(param_1, iVar1, 0);
            atomic_clear_bit_1(param_1+4, 0);
            return 0;
        }
        net_buf_unref(iVar1);
    }
    return 8;
}
