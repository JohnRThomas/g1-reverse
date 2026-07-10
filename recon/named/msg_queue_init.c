/* named: msg_queue_init */
/* globals referenced:
//   0x20007dac  g_message_pool               
//   0x2001a22a  g_message_pool_index         
//   0x2001a22b  g_message_table_slot_count   
*/
/* Reconstructed msg_queue_init @ 0x33c5c  (parity: 300/300 trials, PROVEN) */

extern int memset_bytes(int,int,int,int,int);
extern int get_device_info(void);
extern void msg_queue_debug_dump(void);
extern void debug_dump_message_slots_10_19(void);

void msg_queue_init(void)
{
    int iVar2;
    int iVar3 = 0;
    *(volatile unsigned char*)0x20018d8eUL = 1;
    iVar2 = 0x20007dac;
    do {
        iVar2 = memset_bytes(iVar2, 0, 0x1b4, iVar2, 0);
        iVar3 = iVar3 + 1;
        iVar2 = iVar2 + 0x1b4;
    } while (iVar3 != 0x14);
    *(volatile unsigned char*)0x2001a22bUL = 10;
    *(volatile unsigned char*)0x2001a22aUL = 0;
    iVar2 = get_device_info();
    *(volatile unsigned char*)(iVar2 + 0xdd) = 0;
    msg_queue_debug_dump();
    debug_dump_message_slots_10_19();
    *(volatile unsigned char*)0x20018d8eUL = 0;
}

