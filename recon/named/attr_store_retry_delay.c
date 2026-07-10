/* named: attr_store_retry_delay */
/* globals referenced:
//   0x20007bc0  g_pt_nfc_link_cfg            
*/
/* Reconstructed attr_store_retry_delay @ 0x3016c  (parity: 300/300 trials, PROVEN) */

typedef void (*fn_t)(void);
void attr_store_retry_delay(void)
{
    unsigned int base = *(volatile unsigned int*)0x20007bc0UL;
    fn_t f = *(volatile fn_t*)(base + 0xc);
    f();
}

