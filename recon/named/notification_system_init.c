/* named: notification_system_init */
/* globals referenced:
//   0x20007dac  g_message_pool               
//   0x2001a22a  g_message_pool_index         
//   0x2001a22b  g_message_table_slot_count   
*/
/* Reconstructed notification_system_init @ 0x34944  (parity: 300/300 trials, PROVEN) */

extern int msg_content_decrement_timer(void);
extern void memset_bytes(int a, int b, int c);
extern void FUN_00035744(void);

void notification_system_init(void)
{
    *(volatile unsigned char *)0x2001a22bUL = 10;
    *(volatile unsigned char *)0x2001a22aUL = 0;
    *(volatile unsigned char *)0x2001a229UL = 0;
    int uVar1 = msg_content_decrement_timer();
    memset_bytes(0x20007dac, uVar1, 0x2210);
    FUN_00035744();
}

