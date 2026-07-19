/* readable reconstruction; identity: FUN_0005a128 @ 0x0005a128
 * public-name: sc_save
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   find_sc_cfg_59bcc                        <= FUN_00059bcc @ 0x00059bcc
 *   log_gatt_sc_store_failure                <= FUN_0005a0e8 @ 0x0005a0e8
 *   sc_save                                  <= FUN_0005a128 @ 0x0005a128
 *   bt_addr_le_is_bonded                     <= FUN_00080f92 @ 0x00080f92
 *   bt_addr_le_copy_828da                    <= FUN_000828da @ 0x000828da
 *   log_msg_create_3arg                      <= FUN_00082a42 @ 0x00082a42
 * address symbols (name @ address):
 *   rodata_88128                             @ 0x00088128
 *   rodata_f2b3a                             @ 0x000f2b3a
 *   rodata_f47f3                             @ 0x000f47f3
 */
/* Reconstructed FUN_0005a128 @ 0x5a128  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void* find_sc_cfg_59bcc(int,int);
extern void bt_addr_le_copy_828da(void*,unsigned);
extern void log_msg_create_3arg(int,int,void*);
extern int bt_addr_le_is_bonded(int,void*);
extern void log_gatt_sc_store_failure(void *entry);

void sc_save(unsigned char param_1, unsigned param_2, unsigned param_3, unsigned param_4){
    unsigned char *puVar1 = (unsigned char*)find_sc_cfg_59bcc(param_1,param_2);
    volatile int loc[4];
    if (puVar1 == 0){
        puVar1 = (unsigned char*)find_sc_cfg_59bcc(0, 0x000f2b3a);
        if (puVar1 == 0){
            loc[0]=2; loc[1]=0x000f47f3;
            log_msg_create_3arg(0x00088128, 0x1040, (void*)&loc[0]);
            return;
        }
        *puVar1 = param_1;
        bt_addr_le_copy_828da(puVar1+1, param_2);
    }
    unsigned a = *(unsigned short*)(puVar1+8);
    unsigned uVar3 = *(unsigned short*)(puVar1+0xa);
    if (a != 0){
        if (param_3 < a) goto L19c;
        goto L196;
    }
    if (uVar3 != 0) goto L196;
    *(unsigned short*)(puVar1+8) = (unsigned short)param_3;
  L176:
    *(unsigned short*)(puVar1+0xa) = (unsigned short)param_4;
  L178:
    {
        int iVar2 = bt_addr_le_is_bonded(*puVar1, puVar1+1);
        if (iVar2 == 0) return;
        log_gatt_sc_store_failure(puVar1);
        return;
    }
  L196:
    if (param_4 > uVar3) goto L176;
    return;
  L19c:
    *(unsigned short*)(puVar1+8) = (unsigned short)param_3;
    if (param_4 <= uVar3) goto L178;
    goto L176;
}
