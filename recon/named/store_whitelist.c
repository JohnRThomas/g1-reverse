/* named: store_whitelist */
/* globals referenced:
//   0x00131000  FLASH_ADDR_APP_WHITELIST     
//   0x20007554  g_log_use_alt_sink           
//   0x2001a22c  g_app_whitelist_buffer       
*/
/* Reconstructed store_whitelist @ 0x35608  (parity: 300/300 trials, PROVEN) */
extern int flash_write_paged(unsigned int a0, unsigned int a1, unsigned int a2);
extern void revalidate_whitelist_json(void);
extern void FUN_00074844(unsigned int a0, unsigned int a1);
extern void DEBUG_PRINT(unsigned int a0, ...);
extern void debug_print(unsigned int a0, ...);

int store_whitelist(void)
{
    int iVar4;
    unsigned char cVar5 = 3;
    do {
        iVar4 = flash_write_paged(0x131000UL, 0x2001a22cUL, 0x15e2UL);
        if (iVar4 == 0) {
            revalidate_whitelist_json();
            break;
        }
        FUN_00074844(0xa4UL, 0UL);
        if (*(volatile int*)0x20007554UL == 0)
            DEBUG_PRINT(0xa896cUL);
        else
            debug_print(0);
        cVar5 = cVar5 - 1;
    } while (cVar5 != 0);
    if (*(volatile int*)0x20007554UL == 0)
        DEBUG_PRINT(0xa8994UL, 0xa8ab7UL, 0x24UL, iVar4);
    else
        debug_print(0xa8994UL, 0xa8ab7UL, 0x24UL, iVar4);
    return iVar4;
}

