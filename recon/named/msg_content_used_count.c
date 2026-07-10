/* named: msg_content_used_count */
/* globals referenced:
//   0x20007dac  g_message_pool               
*/
/* Reconstructed msg_content_used_count @ 0x33cdc  (parity: 300/300 trials, PROVEN) */

unsigned int msg_content_used_count(void)
{
    unsigned int uVar1 = 0;
    unsigned int base = 0x20007dacUL;
    while (1) {
        if (*(volatile unsigned char*)(base + 0x10) == 0) {
            return uVar1 & 0xff;
        }
        uVar1 = uVar1 + 1;
        base = base + 0x1b4;
        if (uVar1 == 10) {
            break;
        }
    }
    return 10;
}

