#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00033c5c @ 0x00033c5c
 * public-name: msg_queue_init
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   msg_queue_debug_dump                     <= FUN_00033b0c @ 0x00033b0c
 *   debug_dump_message_slots_10_19           <= FUN_00033b4c @ 0x00033b4c
 *   msg_queue_init                           <= FUN_00033c5c @ 0x00033c5c
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   g_message_pool                           @ 0x20007dac
 *   g_msg_queue_busy                         @ 0x20018d8e
 *   g_message_pool_index                     @ 0x2001a22a
 *   g_message_table_slot_count               @ 0x2001a22b
 */
/* Reconstructed FUN_00033c5c @ 0x33c5c  (parity: 300/300 trials, PROVEN) */

extern int memset_bytes(int,int,int,int,int);
extern int get_device_info(void);
extern void msg_queue_debug_dump(void);
extern void debug_dump_message_slots_10_19(void);

void msg_queue_init(void)
{
    int iVar2;
    int iVar3 = 0;
    *(volatile unsigned char*)((unsigned long)&g_msg_queue_busy) /*=0x20018d8e*/ = 1;
    iVar2 = ((unsigned long)g_message_pool) /*=0x20007dac*/;
    do {
        iVar2 = memset_bytes(iVar2, 0, 0x1b4, iVar2, 0);
        iVar3 = iVar3 + 1;
        iVar2 = iVar2 + 0x1b4;
    } while (iVar3 != 0x14);
    *(volatile unsigned char*)((unsigned long)&g_message_table_slot_count) /*=0x2001a22b*/ = 10;
    *(volatile unsigned char*)((unsigned long)&g_message_pool_index) /*=0x2001a22a*/ = 0;
    iVar2 = get_device_info();
    *(volatile unsigned char*)(iVar2 + 0xdd) = 0;
    msg_queue_debug_dump();
    debug_dump_message_slots_10_19();
    *(volatile unsigned char*)((unsigned long)&g_msg_queue_busy) /*=0x20018d8e*/ = 0;
}
