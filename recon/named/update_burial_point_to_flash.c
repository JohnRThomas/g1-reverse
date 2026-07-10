/* named: update_burial_point_to_flash */
/* globals referenced:
//   0x00135000  FLASH_ADDR_SETTINGS_RECORD   
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed update_burial_point_to_flash @ 0x23014  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int a, unsigned int b);
extern void debug_print(void);
extern int flash_settings_read(unsigned int a, void *b, unsigned int n);
extern int flash_settings_write_and_verify(unsigned int a, void *b, unsigned int n);
extern int memcmp(void *a, void *b, unsigned int n);
extern void memset_bytes(void *dst, int val, int n);

unsigned int update_burial_point_to_flash(char *param_1)
{
    unsigned char buf[196];
    int iVar2;
    unsigned int format_string;

    memset_bytes(buf, 0, 0xc0);
    if (1 < *(volatile int *)0x2000230cUL) {
        if (*(volatile int *)0x20007554UL == 0) {
            DEBUG_PRINT(0x9e655U, 0x9e789U);
        } else {
            debug_print();
        }
    }
    iVar2 = flash_settings_read(0x135000U, buf, 0xc0);
    if (iVar2 == 0) {
        char *p = param_1 + 0x10c6;
        iVar2 = memcmp(buf, p, 0xc0);
        if (iVar2 == 0) {
            return 0;
        }
        iVar2 = flash_settings_write_and_verify(0x135000U, p, 0xc0);
        if (iVar2 == 0) {
            return 0;
        }
        if (*(volatile int *)0x2000230cUL < 2) {
            return 0xffffffff;
        }
        iVar2 = *(volatile int *)0x20007554UL;
        format_string = 0x9e69cU;
    } else {
        if (*(volatile int *)0x2000230cUL < 2) {
            return 0xffffffff;
        }
        iVar2 = *(volatile int *)0x20007554UL;
        format_string = 0x9e67cU;
    }
    if (iVar2 == 0) {
        DEBUG_PRINT(format_string, 0x9e789U);
    } else {
        debug_print();
    }
    return 0xffffffff;
}

