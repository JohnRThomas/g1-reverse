/* named: msg_count_dec */
/* globals referenced:
//   0x20007554  g_log_use_alt_sink           
//   0x20007dac  g_message_pool               
//   0x2001a22a  g_message_pool_index         
*/
/* Reconstructed msg_count_dec @ 0x34274  (parity: 300/300 trials, PROVEN) */
extern int get_device_info(void);
extern void clear_timeout_message(int);
extern void DEBUG_PRINT(unsigned,int);
extern void debug_print(void);
extern unsigned char msg_content_recalc_unread(void);
unsigned char msg_count_dec(void){
    int iVar3 = get_device_info();
    unsigned char bVar1 = *(unsigned char*)(iVar3 + 0xdd);
    if (bVar1 != 0){
        int r5 = bVar1 - 1;
        int r3 = r5 * 0x1b4 + 0x20007dac;
        if (*(int*)(r3 + 4) != 0){
            clear_timeout_message(1);
            unsigned char cVar4;
            if (r5 == 0) cVar4 = 0;
            else cVar4 = (unsigned char)(bVar1 - 2);
            *(volatile unsigned char*)0x2001a22aUL = cVar4;
            if (*(volatile int*)0x20007554UL == 0){
                DEBUG_PRINT(0xa8017, r5);
            } else {
                debug_print();
            }
            iVar3 = get_device_info();
            unsigned char uVar2 = msg_content_recalc_unread();
            *(unsigned char*)(iVar3 + 0xdd) = uVar2;
        }
    }
    iVar3 = get_device_info();
    return *(unsigned char*)(iVar3 + 0xdd);
}

